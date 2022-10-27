################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Decawave/example/ex_02d_rx_sniff/rx_sniff.c 

OBJS += \
./Drivers/Decawave/example/ex_02d_rx_sniff/rx_sniff.o 

C_DEPS += \
./Drivers/Decawave/example/ex_02d_rx_sniff/rx_sniff.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Decawave/example/ex_02d_rx_sniff/%.o Drivers/Decawave/example/ex_02d_rx_sniff/%.su: ../Drivers/Decawave/example/ex_02d_rx_sniff/%.c Drivers/Decawave/example/ex_02d_rx_sniff/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=c11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Platform -I../Platform/deca -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Drivers/Decawave/DW3XXX_driver_6p0/Inc -I../Drivers/Decawave/example -I../Drivers/Decawave/example/examples_info -I../Drivers/Decawave/example/shared_data -I"../Drivers/Decawave/example/MAC_802_15_4" -I"../Drivers/Decawave/example/MAC_802_15_8" -O0 -ffunction-sections -Wall -Wextra -pedantic -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Decawave-2f-example-2f-ex_02d_rx_sniff

clean-Drivers-2f-Decawave-2f-example-2f-ex_02d_rx_sniff:
	-$(RM) ./Drivers/Decawave/example/ex_02d_rx_sniff/rx_sniff.d ./Drivers/Decawave/example/ex_02d_rx_sniff/rx_sniff.o ./Drivers/Decawave/example/ex_02d_rx_sniff/rx_sniff.su

.PHONY: clean-Drivers-2f-Decawave-2f-example-2f-ex_02d_rx_sniff

