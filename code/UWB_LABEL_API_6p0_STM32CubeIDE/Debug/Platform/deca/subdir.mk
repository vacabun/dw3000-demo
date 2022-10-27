################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Platform/deca/deca_mutex.c \
../Platform/deca/deca_probe_interface.c \
../Platform/deca/deca_sleep.c \
../Platform/deca/deca_spi.c \
../Platform/deca/port.c 

OBJS += \
./Platform/deca/deca_mutex.o \
./Platform/deca/deca_probe_interface.o \
./Platform/deca/deca_sleep.o \
./Platform/deca/deca_spi.o \
./Platform/deca/port.o 

C_DEPS += \
./Platform/deca/deca_mutex.d \
./Platform/deca/deca_probe_interface.d \
./Platform/deca/deca_sleep.d \
./Platform/deca/deca_spi.d \
./Platform/deca/port.d 


# Each subdirectory must supply rules for building sources it contributes
Platform/deca/%.o Platform/deca/%.su: ../Platform/deca/%.c Platform/deca/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=c11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Platform -I../Platform/deca -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Drivers/Decawave/DW3XXX_driver_6p0/Inc -I../Drivers/Decawave/example -I../Drivers/Decawave/example/examples_info -I../Drivers/Decawave/example/shared_data -I"../Drivers/Decawave/example/MAC_802_15_4" -I"../Drivers/Decawave/example/MAC_802_15_8" -O0 -ffunction-sections -Wall -Wextra -pedantic -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Platform-2f-deca

clean-Platform-2f-deca:
	-$(RM) ./Platform/deca/deca_mutex.d ./Platform/deca/deca_mutex.o ./Platform/deca/deca_mutex.su ./Platform/deca/deca_probe_interface.d ./Platform/deca/deca_probe_interface.o ./Platform/deca/deca_probe_interface.su ./Platform/deca/deca_sleep.d ./Platform/deca/deca_sleep.o ./Platform/deca/deca_sleep.su ./Platform/deca/deca_spi.d ./Platform/deca/deca_spi.o ./Platform/deca/deca_spi.su ./Platform/deca/port.d ./Platform/deca/port.o ./Platform/deca/port.su

.PHONY: clean-Platform-2f-deca
