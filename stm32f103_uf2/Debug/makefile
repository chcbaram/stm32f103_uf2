################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include App/src/tinyuf2/src/subdir.mk
-include App/src/tinyuf2/ports/stm32f1/subdir.mk
-include App/src/tinyuf2/lib/tinyusb/src/portable/st/synopsys/subdir.mk
-include App/src/tinyuf2/lib/tinyusb/src/portable/st/stm32_fsdev/subdir.mk
-include App/src/tinyuf2/lib/tinyusb/src/host/subdir.mk
-include App/src/tinyuf2/lib/tinyusb/src/device/subdir.mk
-include App/src/tinyuf2/lib/tinyusb/src/common/subdir.mk
-include App/src/tinyuf2/lib/tinyusb/src/class/video/subdir.mk
-include App/src/tinyuf2/lib/tinyusb/src/class/vendor/subdir.mk
-include App/src/tinyuf2/lib/tinyusb/src/class/usbtmc/subdir.mk
-include App/src/tinyuf2/lib/tinyusb/src/class/net/subdir.mk
-include App/src/tinyuf2/lib/tinyusb/src/class/msc/subdir.mk
-include App/src/tinyuf2/lib/tinyusb/src/class/midi/subdir.mk
-include App/src/tinyuf2/lib/tinyusb/src/class/hid/subdir.mk
-include App/src/tinyuf2/lib/tinyusb/src/class/dfu/subdir.mk
-include App/src/tinyuf2/lib/tinyusb/src/class/cdc/subdir.mk
-include App/src/tinyuf2/lib/tinyusb/src/class/bth/subdir.mk
-include App/src/tinyuf2/lib/tinyusb/src/class/audio/subdir.mk
-include App/src/tinyuf2/lib/tinyusb/src/subdir.mk
-include App/src/subdir.mk
-include App/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := stm32f103_uf2
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
stm32f103_uf2.elf \

MAP_FILES += \
stm32f103_uf2.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
stm32f103_uf2.list \


# All Target
all: main-build

# Main-build Target
main-build: stm32f103_uf2.elf secondary-outputs

# Tool invocations
stm32f103_uf2.elf stm32f103_uf2.map: $(OBJS) $(USER_OBJS) D:\git\stm32f103_uf2\stm32f103_uf2\STM32F103C8TX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "stm32f103_uf2.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\git\stm32f103_uf2\stm32f103_uf2\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="stm32f103_uf2.map" -Wl,--gc-sections -nostartfiles -nodefaultlibs -nostdlib -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

stm32f103_uf2.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "stm32f103_uf2.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) default.size.stdout stm32f103_uf2.elf stm32f103_uf2.list stm32f103_uf2.map
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
