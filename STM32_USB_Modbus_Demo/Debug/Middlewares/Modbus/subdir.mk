################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Modbus/mb.c \
../Middlewares/Modbus/mb_m.c 

OBJS += \
./Middlewares/Modbus/mb.o \
./Middlewares/Modbus/mb_m.o 

C_DEPS += \
./Middlewares/Modbus/mb.d \
./Middlewares/Modbus/mb_m.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Modbus/%.o Middlewares/Modbus/%.su Middlewares/Modbus/%.cyclo: ../Middlewares/Modbus/%.c Middlewares/Modbus/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"../Middlewares/Modbus/functions" -I"../Middlewares/Modbus/include" -I"../Middlewares/Modbus/port" -I"../Middlewares/Modbus/rtu" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Modbus

clean-Middlewares-2f-Modbus:
	-$(RM) ./Middlewares/Modbus/mb.cyclo ./Middlewares/Modbus/mb.d ./Middlewares/Modbus/mb.o ./Middlewares/Modbus/mb.su ./Middlewares/Modbus/mb_m.cyclo ./Middlewares/Modbus/mb_m.d ./Middlewares/Modbus/mb_m.o ./Middlewares/Modbus/mb_m.su

.PHONY: clean-Middlewares-2f-Modbus

