################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include emlib/subdir.mk
-include CMSIS/EFM32GG/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: gyak2.axf

# Tool invocations
gyak2.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -T "gyak2.ld" -Xlinker --gc-sections -Xlinker -Map="gyak2.map" --specs=nano.specs -o gyak2.axf "./CMSIS/EFM32GG/startup_gcc_efm32gg.o" "./CMSIS/EFM32GG/system_efm32gg.o" "./emlib/em_system.o" "./src/main.o" -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: gyak2.hex'
	arm-none-eabi-objcopy -O ihex "gyak2.axf" "gyak2.hex"
	@echo ' '

	@echo 'Building bin file: gyak2.bin'
	arm-none-eabi-objcopy -O binary "gyak2.axf" "gyak2.bin"
	@echo ' '

	@echo 'Building s37 file: gyak2.s37'
	arm-none-eabi-objcopy -O srec "gyak2.axf" "gyak2.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "gyak2.axf"
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) gyak2.axf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
