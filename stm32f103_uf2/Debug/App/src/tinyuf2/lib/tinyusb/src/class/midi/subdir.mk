################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/src/tinyuf2/lib/tinyusb/src/class/midi/midi_device.c 

OBJS += \
./App/src/tinyuf2/lib/tinyusb/src/class/midi/midi_device.o 

C_DEPS += \
./App/src/tinyuf2/lib/tinyusb/src/class/midi/midi_device.d 


# Each subdirectory must supply rules for building sources it contributes
App/src/tinyuf2/lib/tinyusb/src/class/midi/%.o App/src/tinyuf2/lib/tinyusb/src/class/midi/%.su: ../App/src/tinyuf2/lib/tinyusb/src/class/midi/%.c App/src/tinyuf2/lib/tinyusb/src/class/midi/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/git/stm32f103_uf2/stm32f103_uf2/App" -I"D:/git/stm32f103_uf2/stm32f103_uf2/App/include" -I"D:/git/stm32f103_uf2/stm32f103_uf2/App/src/tinyuf2/src" -I"D:/git/stm32f103_uf2/stm32f103_uf2/App/src/tinyuf2/lib/tinyusb/src" -I"D:/git/stm32f103_uf2/stm32f103_uf2/App/src/tinyuf2/ports/stm32f1" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-App-2f-src-2f-tinyuf2-2f-lib-2f-tinyusb-2f-src-2f-class-2f-midi

clean-App-2f-src-2f-tinyuf2-2f-lib-2f-tinyusb-2f-src-2f-class-2f-midi:
	-$(RM) ./App/src/tinyuf2/lib/tinyusb/src/class/midi/midi_device.d ./App/src/tinyuf2/lib/tinyusb/src/class/midi/midi_device.o ./App/src/tinyuf2/lib/tinyusb/src/class/midi/midi_device.su

.PHONY: clean-App-2f-src-2f-tinyuf2-2f-lib-2f-tinyusb-2f-src-2f-class-2f-midi

