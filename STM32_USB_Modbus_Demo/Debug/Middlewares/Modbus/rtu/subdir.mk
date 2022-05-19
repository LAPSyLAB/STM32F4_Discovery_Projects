################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Modbus/rtu/mbcrc.c \
../Middlewares/Modbus/rtu/mbrtu.c \
../Middlewares/Modbus/rtu/mbrtu_m.c 

OBJS += \
./Middlewares/Modbus/rtu/mbcrc.o \
./Middlewares/Modbus/rtu/mbrtu.o \
./Middlewares/Modbus/rtu/mbrtu_m.o 

C_DEPS += \
./Middlewares/Modbus/rtu/mbcrc.d \
./Middlewares/Modbus/rtu/mbrtu.d \
./Middlewares/Modbus/rtu/mbrtu_m.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Modbus/rtu/%.o: ../Middlewares/Modbus/rtu/%.c Middlewares/Modbus/rtu/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"../Middlewares/Modbus/functions" -I"../Middlewares/Modbus/include" -I"../Middlewares/Modbus/port" -I"../Middlewares/Modbus/rtu" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Modbus-2f-rtu

clean-Middlewares-2f-Modbus-2f-rtu:
	-$(RM) ./Middlewares/Modbus/rtu/mbcrc.d ./Middlewares/Modbus/rtu/mbcrc.o ./Middlewares/Modbus/rtu/mbrtu.d ./Middlewares/Modbus/rtu/mbrtu.o ./Middlewares/Modbus/rtu/mbrtu_m.d ./Middlewares/Modbus/rtu/mbrtu_m.o

.PHONY: clean-Middlewares-2f-Modbus-2f-rtu

