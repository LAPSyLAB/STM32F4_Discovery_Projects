################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Modbus/port/portcritical.c \
../Middlewares/Modbus/port/portevent.c \
../Middlewares/Modbus/port/portevent_m.c \
../Middlewares/Modbus/port/portserial.c \
../Middlewares/Modbus/port/portserial_m.c \
../Middlewares/Modbus/port/porttimer.c \
../Middlewares/Modbus/port/porttimer_m.c 

OBJS += \
./Middlewares/Modbus/port/portcritical.o \
./Middlewares/Modbus/port/portevent.o \
./Middlewares/Modbus/port/portevent_m.o \
./Middlewares/Modbus/port/portserial.o \
./Middlewares/Modbus/port/portserial_m.o \
./Middlewares/Modbus/port/porttimer.o \
./Middlewares/Modbus/port/porttimer_m.o 

C_DEPS += \
./Middlewares/Modbus/port/portcritical.d \
./Middlewares/Modbus/port/portevent.d \
./Middlewares/Modbus/port/portevent_m.d \
./Middlewares/Modbus/port/portserial.d \
./Middlewares/Modbus/port/portserial_m.d \
./Middlewares/Modbus/port/porttimer.d \
./Middlewares/Modbus/port/porttimer_m.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Modbus/port/%.o: ../Middlewares/Modbus/port/%.c Middlewares/Modbus/port/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"../Middlewares/Modbus/functions" -I"../Middlewares/Modbus/include" -I"../Middlewares/Modbus/port" -I"../Middlewares/Modbus/rtu" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

