################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/src/button.c \
../App/src/led.c \
../App/src/tinyuf2.c \
../App/src/utils.c 

OBJS += \
./App/src/button.o \
./App/src/led.o \
./App/src/tinyuf2.o \
./App/src/utils.o 

C_DEPS += \
./App/src/button.d \
./App/src/led.d \
./App/src/tinyuf2.d \
./App/src/utils.d 


# Each subdirectory must supply rules for building sources it contributes
App/src/%.o App/src/%.su: ../App/src/%.c App/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/git/stm32f103_uf2/stm32f103_uf2/App" -I"D:/git/stm32f103_uf2/stm32f103_uf2/App/include" -I"D:/git/stm32f103_uf2/stm32f103_uf2/App/src/tinyuf2/src" -I"D:/git/stm32f103_uf2/stm32f103_uf2/App/src/tinyuf2/lib/tinyusb/src" -I"D:/git/stm32f103_uf2/stm32f103_uf2/App/src/tinyuf2/ports/stm32f1" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-App-2f-src

clean-App-2f-src:
	-$(RM) ./App/src/button.d ./App/src/button.o ./App/src/button.su ./App/src/led.d ./App/src/led.o ./App/src/led.su ./App/src/tinyuf2.d ./App/src/tinyuf2.o ./App/src/tinyuf2.su ./App/src/utils.d ./App/src/utils.o ./App/src/utils.su

.PHONY: clean-App-2f-src

