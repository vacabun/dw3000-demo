################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include USB_DEVICE/Target/subdir.mk
-include USB_DEVICE/App/subdir.mk
-include Platform/deca/subdir.mk
-include Platform/subdir.mk
-include Middlewares/ST/STM32_USB_Device_Library/Core/Src/subdir.mk
-include Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Drivers/Decawave/example/shared_data/subdir.mk
-include Drivers/Decawave/example/examples_info/subdir.mk
-include Drivers/Decawave/example/ex_20_simple_aes/subdir.mk
-include Drivers/Decawave/example/ex_19_tx_power_adjustment/subdir.mk
-include Drivers/Decawave/example/ex_18_timer/subdir.mk
-include Drivers/Decawave/example/ex_17_bw_cal/subdir.mk
-include Drivers/Decawave/example/ex_16_pll_cal/subdir.mk
-include Drivers/Decawave/example/ex_15_le_pend/subdir.mk
-include Drivers/Decawave/example/ex_14_otp_write/subdir.mk
-include Drivers/Decawave/example/ex_13a_gpio/subdir.mk
-include Drivers/Decawave/example/ex_11a_spi_crc/subdir.mk
-include Drivers/Decawave/example/ex_07b_ack_data_rx/subdir.mk
-include Drivers/Decawave/example/ex_07a_ack_data_tx/subdir.mk
-include Drivers/Decawave/example/ex_06f_AES_ss_twr_responder/subdir.mk
-include Drivers/Decawave/example/ex_06e_AES_ss_twr_initiator/subdir.mk
-include Drivers/Decawave/example/ex_06b_ss_twr_responder/subdir.mk
-include Drivers/Decawave/example/ex_06a_ss_twr_initiator/subdir.mk
-include Drivers/Decawave/example/ex_05d_ds_twr_resp_sts_sdc/subdir.mk
-include Drivers/Decawave/example/ex_05c_ds_twr_init_sts_sdc/subdir.mk
-include Drivers/Decawave/example/ex_05b_ds_twr_resp/subdir.mk
-include Drivers/Decawave/example/ex_05a_ds_twr_init/subdir.mk
-include Drivers/Decawave/example/ex_04b_cont_frame/subdir.mk
-include Drivers/Decawave/example/ex_04a_cont_wave/subdir.mk
-include Drivers/Decawave/example/ex_03d_tx_wait_resp_interrupts/subdir.mk
-include Drivers/Decawave/example/ex_03b_rx_send_resp/subdir.mk
-include Drivers/Decawave/example/ex_03a_tx_wait_resp/subdir.mk
-include Drivers/Decawave/example/ex_02i_simple_rx_aes/subdir.mk
-include Drivers/Decawave/example/ex_02h_simple_rx_pdoa/subdir.mk
-include Drivers/Decawave/example/ex_02g_simple_rx_sts_sdc/subdir.mk
-include Drivers/Decawave/example/ex_02f_rx_with_crystal_trim/subdir.mk
-include Drivers/Decawave/example/ex_02e_rx_dbl_buff/subdir.mk
-include Drivers/Decawave/example/ex_02d_rx_sniff/subdir.mk
-include Drivers/Decawave/example/ex_02c_rx_diagnostics/subdir.mk
-include Drivers/Decawave/example/ex_02a_simple_rx/subdir.mk
-include Drivers/Decawave/example/ex_01i_simple_tx_aes/subdir.mk
-include Drivers/Decawave/example/ex_01h_simple_tx_pdoa/subdir.mk
-include Drivers/Decawave/example/ex_01g_simple_tx_sts_sdc/subdir.mk
-include Drivers/Decawave/example/ex_01e_tx_with_cca/subdir.mk
-include Drivers/Decawave/example/ex_01d_tx_timed_sleep/subdir.mk
-include Drivers/Decawave/example/ex_01c_tx_sleep_auto/subdir.mk
-include Drivers/Decawave/example/ex_01b_tx_sleep/subdir.mk
-include Drivers/Decawave/example/ex_01a_simple_tx/subdir.mk
-include Drivers/Decawave/example/ex_00a_reading_dev_id/subdir.mk
-include Drivers/Decawave/example/MAC_802_15_8/subdir.mk
-include Drivers/Decawave/example/MAC_802_15_4/subdir.mk
-include Drivers/Decawave/example/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
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


BUILD_ARTIFACT_NAME := UWB-UAV-LABEL
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
UWB-UAV-LABEL.elf \

MAP_FILES += \
UWB-UAV-LABEL.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
UWB-UAV-LABEL.list \


# All Target
all: main-build

# Main-build Target
main-build: UWB-UAV-LABEL.elf secondary-outputs

# Tool invocations
UWB-UAV-LABEL.elf UWB-UAV-LABEL.map: $(OBJS) $(USER_OBJS) C:\Users\maguo\Desktop\UWB-UAV\code\UWB-UAV-LABEL-STM32CubeIDE\STM32F401CCUX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "UWB-UAV-LABEL.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\maguo\Desktop\UWB-UAV\code\UWB-UAV-LABEL-STM32CubeIDE\STM32F401CCUX_FLASH.ld" -Wl,-Map="UWB-UAV-LABEL.map" -Wl,--gc-sections -static -L../Drivers/Decawave/DW3XXX_driver_6p0/lib -ldwt_uwb_driver-m4-hfp-6.0.7 -Wl,--no-whole-archive  -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -u _printf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

UWB-UAV-LABEL.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "UWB-UAV-LABEL.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) UWB-UAV-LABEL.elf UWB-UAV-LABEL.list UWB-UAV-LABEL.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
