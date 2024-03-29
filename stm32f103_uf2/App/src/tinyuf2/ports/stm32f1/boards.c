/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Ha Thach for Adafruit Industries
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "board_api.h"
#include "tusb.h"
#include "led.h"


//--------------------------------------------------------------------+
// MACRO TYPEDEF CONSTANT ENUM DECLARATION
//--------------------------------------------------------------------+

#define STM32_UUID    ((volatile uint32_t *) UID_BASE)

static void board_usb_reset(uint32_t delay_ms);

static bool is_usb = false;



void board_init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};


  // disable systick
  board_timer_stop();

  // Enable All GPIOs clocks
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  // USB Pins
  // Configure USB DM and DP pins.
  GPIO_InitStruct.Pin = GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
}

void board_dfu_init(void)
{
  board_usb_reset(200);

  // USB Clock enable
  __HAL_RCC_USB_CLK_ENABLE();

  is_usb = true;
}

void board_usb_reset(uint32_t delay_ms)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  // USB Pins
  // Configure USB DM and DP pins.
  GPIO_InitStruct.Pin = GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
  delay(delay_ms);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);

  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void board_reset(void)
{
  NVIC_SystemReset();
}

void board_dfu_complete(void)
{
  NVIC_SystemReset();
}

bool board_app_valid(void)
{
  volatile uint32_t const * app_vector = (volatile uint32_t const*) BOARD_FLASH_APP_START;
  uint32_t sp = app_vector[0];
  uint32_t app_entry = app_vector[1];

  TUF2_LOG1_HEX(sp);
  TUF2_LOG1_HEX(app_entry);

  // 1st word is stack pointer (must be in SRAM region)
  if ((sp & 0xff000003) != 0x20000000) return false;

  // 2nd word is App entry point (reset)
  if (app_entry < BOARD_FLASH_APP_START || app_entry > BOARD_FLASH_APP_START + BOARD_FLASH_SIZE) {
    return false;
  }

  return true;
}

void board_app_jump(void)
{
  volatile uint32_t const * app_vector = (volatile uint32_t const*) BOARD_FLASH_APP_START;
  uint32_t sp = app_vector[0];
  uint32_t app_entry = app_vector[1];

#ifdef BUTTON_PIN
  HAL_GPIO_DeInit(BUTTON_PORT, BUTTON_PIN);
#endif

#ifdef LED_PIN
  HAL_GPIO_DeInit(LED_PORT, LED_PIN);
#endif

#if NEOPIXEL_NUMBER
  HAL_GPIO_DeInit(NEOPIXEL_PORT, NEOPIXEL_PIN);
#endif

#if defined(UART_DEV) && CFG_TUSB_DEBUG
  HAL_UART_DeInit(&UartHandle);
  HAL_GPIO_DeInit(UART_GPIO_PORT, UART_TX_PIN | UART_RX_PIN);
  UART_CLOCK_DISABLE();
#endif


  __HAL_RCC_GPIOA_CLK_DISABLE();
  __HAL_RCC_GPIOB_CLK_DISABLE();
  __HAL_RCC_GPIOC_CLK_DISABLE();

  HAL_RCC_DeInit();

  SysTick->CTRL = 0;
  SysTick->LOAD = 0;
  SysTick->VAL = 0;

  // Disable all Interrupts
  NVIC->ICER[0] = 0xFFFFFFFF;
  NVIC->ICER[1] = 0xFFFFFFFF;
  NVIC->ICER[2] = 0xFFFFFFFF;
  NVIC->ICER[3] = 0xFFFFFFFF;

  /* switch exception handlers to the application */
  SCB->VTOR = (uint32_t) BOARD_FLASH_APP_START;

  // Set stack pointer
  __set_MSP(sp);
  __set_PSP(sp);

  // Jump to Application Entry
  asm("bx %0" ::"r"(app_entry));
}

uint8_t board_usb_get_serial(uint8_t serial_id[16])
{
  uint8_t const len = 12;
  uint32_t* serial_id32 = (uint32_t*) (uintptr_t) serial_id;

  serial_id32[0] = STM32_UUID[0];
  serial_id32[1] = STM32_UUID[1];
  serial_id32[2] = STM32_UUID[2];

  return len;
}

//--------------------------------------------------------------------+
// LED pattern
//--------------------------------------------------------------------+

void board_led_write(uint32_t state)
{
  if (state > 255/2)
    ledOn(_DEF_CH1);
  else
    ledOff(_DEF_CH1);
}

#if NEOPIXEL_NUMBER
#define MAGIC_800_INT   900000  // ~1.11 us -> 1.2  field
#define MAGIC_800_T0H  2800000  // ~0.36 us -> 0.44 field
#define MAGIC_800_T1H  1350000  // ~0.74 us -> 0.84 field

static inline uint8_t apply_percentage(uint8_t brightness)
{
  return (uint8_t) ((brightness*NEOPIXEL_BRIGHTNESS) >> 8);
}

void board_rgb_write(uint8_t const rgb[]) {
  // assumes 800_000Hz frequency
  // Theoretical values here are 800_000 -> 1.25us, 2500000->0.4us,
  // 1250000->0.8us
  uint32_t const sys_freq = HAL_RCC_GetSysClockFreq();
  uint32_t const interval = sys_freq / MAGIC_800_INT;
  uint32_t const t0 = sys_freq / MAGIC_800_T0H;
  uint32_t const t1 = sys_freq / MAGIC_800_T1H;

  // neopixel color order is GRB
  uint8_t const colors[3] = {apply_percentage(rgb[1]), apply_percentage(rgb[0]),
                             apply_percentage(rgb[2])};

  __disable_irq();
  uint32_t start;
  uint32_t cyc;

  // Enable DWT in debug core. Useable when interrupts disabled, as opposed to
  // Systick->VAL
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
  DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
  DWT->CYCCNT = 0;

  for (uint32_t i = 0; i < NEOPIXEL_NUMBER; i++) {
    uint8_t const *color_pointer = colors;
    uint8_t const *const color_pointer_end = color_pointer + 3;
    uint8_t color = *color_pointer++;
    uint8_t color_mask = 0x80;

    while (true) {
      cyc = (color & color_mask) ? t1 : t0;
      start = DWT->CYCCNT;

      HAL_GPIO_WritePin(NEOPIXEL_PORT, NEOPIXEL_PIN, 1);
      while ((DWT->CYCCNT - start) < cyc)
        ;

      HAL_GPIO_WritePin(NEOPIXEL_PORT, NEOPIXEL_PIN, 0);
      while ((DWT->CYCCNT - start) < interval)
        ;

      if (!(color_mask >>= 1)) {
        if (color_pointer >= color_pointer_end) {
          break;
        }
        color = *color_pointer++;
        color_mask = 0x80;
      }
    }
  }

  __enable_irq();
}

#else

void board_rgb_write(uint8_t const rgb[])
{
  (void) rgb;
}

#endif

//--------------------------------------------------------------------+
// Timer
//--------------------------------------------------------------------+
static uint32_t timer_max = 1;
static uint32_t timer_cnt = 0;


void board_timer_start(uint32_t ms)
{
  //SysTick_Config( (SystemCoreClock/1000) * ms );
  timer_max = ms;
}

void board_timer_stop(void)
{
  //SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
  timer_max = 0;
}

void board_timer_tick(void)
{
  timer_cnt++;

  if (timer_max > 0 && timer_cnt >= timer_max)
  {
    timer_cnt = 0;
    board_timer_handler();
  }
}

int board_uart_write(void const * buf, int len)
{
#if defined(UART_DEV) && CFG_TUSB_DEBUG
  HAL_UART_Transmit(&UartHandle, (uint8_t*) buf, len, 0xffff);
  return len;
#else
  (void) buf; (void) len;
  return 0;
#endif
}

//--------------------------------------------------------------------+
// Forward USB interrupt events to TinyUSB IRQ Handler
//--------------------------------------------------------------------+
void USB_HP_IRQHandler(void)
{
  tud_int_handler(0);
}

void USB_LP_IRQHandler(void)
{
  tud_int_handler(0);
}

void USBWakeUp_IRQHandler(void)
{
  tud_int_handler(0);
}

// Required by __libc_init_array in startup code if we are compiling using
// -nostdlib/-nostartfiles.
void _init(void)
{

}
