################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/src/tinyuf2/src/ghostfat.c \
../App/src/tinyuf2/src/images.c \
../App/src/tinyuf2/src/msc.c \
../App/src/tinyuf2/src/screen.c \
../App/src/tinyuf2/src/usb_descriptors.c 

OBJS += \
./App/src/tinyuf2/src/ghostfat.o \
./App/src/tinyuf2/src/images.o \
./App/src/tinyuf2/src/msc.o \
./App/src/tinyuf2/src/screen.o \
./App/src/tinyuf2/src/usb_descriptors.o 

C_DEPS += \
./App/src/tinyuf2/src/ghostfat.d \
./App/src/tinyuf2/src/images.d \
./App/src/tinyuf2/src/msc.d \
./App/src/tinyuf2/src/screen.d \
./App/src/tinyuf2/src/usb_descriptors.d 


# Each subdirectory must supply rules for building sources it contributes
App/src/tinyuf2/src/%.o App/src/tinyuf2/src/%.su: ../App/src/tinyuf2/src/%.c App/src/tinyuf2/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/git/stm32f103_uf2/stm32f103_uf2/App" -I"D:/git/stm32f103_uf2/stm32f103_uf2/App/include" -I"D:/git/stm32f103_uf2/stm32f103_uf2/App/src/tinyuf2/src" -I"D:/git/stm32f103_uf2/stm32f103_uf2/App/src/tinyuf2/lib/tinyusb/src" -I"D:/git/stm32f103_uf2/stm32f103_uf2/App/src/tinyuf2/ports/stm32f1" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-App-2f-src-2f-tinyuf2-2f-src

clean-App-2f-src-2f-tinyuf2-2f-src:
	-$(RM) ./App/src/tinyuf2/src/ghostfat.d ./App/src/tinyuf2/src/ghostfat.o ./App/src/tinyuf2/src/ghostfat.su ./App/src/tinyuf2/src/images.d ./App/src/tinyuf2/src/images.o ./App/src/tinyuf2/src/images.su ./App/src/tinyuf2/src/msc.d ./App/src/tinyuf2/src/msc.o ./App/src/tinyuf2/src/msc.su ./App/src/tinyuf2/src/screen.d ./App/src/tinyuf2/src/screen.o ./App/src/tinyuf2/src/screen.su ./App/src/tinyuf2/src/usb_descriptors.d ./App/src/tinyuf2/src/usb_descriptors.o ./App/src/tinyuf2/src/usb_descriptors.su

.PHONY: clean-App-2f-src-2f-tinyuf2-2f-src

