/*
 * ap.c
 *
 *  Created on: Feb 16, 2023
 *      Author: baram
 */


#include "ap.h"


extern int tinyuf2(void);



void apInit(void)
{
//  __HAL_RCC_GPIOD_CLK_ENABLE();
//  __HAL_RCC_GPIOA_CLK_ENABLE();
//
//
//  GPIO_InitTypeDef GPIO_InitStruct = {0};
//
//  GPIO_InitStruct.Pin = GPIO_PIN_12;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
//
//  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);


  ledInit();
  buttonInit();
}

void apMain(void)
{
  tinyuf2();
}

