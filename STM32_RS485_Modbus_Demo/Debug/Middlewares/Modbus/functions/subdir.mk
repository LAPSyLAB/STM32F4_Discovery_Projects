################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Modbus/functions/mbfunccoils.c \
../Middlewares/Modbus/functions/mbfunccoils_m.c \
../Middlewares/Modbus/functions/mbfuncdiag.c \
../Middlewares/Modbus/functions/mbfuncdisc.c \
../Middlewares/Modbus/functions/mbfuncdisc_m.c \
../Middlewares/Modbus/functions/mbfuncholding.c \
../Middlewares/Modbus/functions/mbfuncholding_m.c \
../Middlewares/Modbus/functions/mbfuncinput.c \
../Middlewares/Modbus/functions/mbfuncinput_m.c \
../Middlewares/Modbus/functions/mbfuncother.c \
../Middlewares/Modbus/functions/mbutils.c 

OBJS += \
./Middlewares/Modbus/functions/mbfunccoils.o \
./Middlewares/Modbus/functions/mbfunccoils_m.o \
./Middlewares/Modbus/functions/mbfuncdiag.o \
./Middlewares/Modbus/functions/mbfuncdisc.o \
./Middlewares/Modbus/functions/mbfuncdisc_m.o \
./Middlewares/Modbus/functions/mbfuncholding.o \
./Middlewares/Modbus/functions/mbfuncholding_m.o \
./Middlewares/Modbus/functions/mbfuncinput.o \
./Middlewares/Modbus/functions/mbfuncinput_m.o \
./Middlewares/Modbus/functions/mbfuncother.o \
./Middlewares/Modbus/functions/mbutils.o 

C_DEPS += \
./Middlewares/Modbus/functions/mbfunccoils.d \
./Middlewares/Modbus/functions/mbfunccoils_m.d \
./Middlewares/Modbus/functions/mbfuncdiag.d \
./Middlewares/Modbus/functions/mbfuncdisc.d \
./Middlewares/Modbus/functions/mbfuncdisc_m.d \
./Middlewares/Modbus/functions/mbfuncholding.d \
./Middlewares/Modbus/functions/mbfuncholding_m.d \
./Middlewares/Modbus/functions/mbfuncinput.d \
./Middlewares/Modbus/functions/mbfuncinput_m.d \
./Middlewares/Modbus/functions/mbfuncother.d \
./Middlewares/Modbus/functions/mbutils.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Modbus/functions/%.o Middlewares/Modbus/functions/%.su: ../Middlewares/Modbus/functions/%.c Middlewares/Modbus/functions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"../Middlewares/Modbus/functions" -I"../Middlewares/Modbus/include" -I"../Middlewares/Modbus/port" -I"../Middlewares/Modbus/rtu" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Modbus-2f-functions

clean-Middlewares-2f-Modbus-2f-functions:
	-$(RM) ./Middlewares/Modbus/functions/mbfunccoils.d ./Middlewares/Modbus/functions/mbfunccoils.o ./Middlewares/Modbus/functions/mbfunccoils.su ./Middlewares/Modbus/functions/mbfunccoils_m.d ./Middlewares/Modbus/functions/mbfunccoils_m.o ./Middlewares/Modbus/functions/mbfunccoils_m.su ./Middlewares/Modbus/functions/mbfuncdiag.d ./Middlewares/Modbus/functions/mbfuncdiag.o ./Middlewares/Modbus/functions/mbfuncdiag.su ./Middlewares/Modbus/functions/mbfuncdisc.d ./Middlewares/Modbus/functions/mbfuncdisc.o ./Middlewares/Modbus/functions/mbfuncdisc.su ./Middlewares/Modbus/functions/mbfuncdisc_m.d ./Middlewares/Modbus/functions/mbfuncdisc_m.o ./Middlewares/Modbus/functions/mbfuncdisc_m.su ./Middlewares/Modbus/functions/mbfuncholding.d ./Middlewares/Modbus/functions/mbfuncholding.o ./Middlewares/Modbus/functions/mbfuncholding.su ./Middlewares/Modbus/functions/mbfuncholding_m.d ./Middlewares/Modbus/functions/mbfuncholding_m.o ./Middlewares/Modbus/functions/mbfuncholding_m.su ./Middlewares/Modbus/functions/mbfuncinput.d ./Middlewares/Modbus/functions/mbfuncinput.o ./Middlewares/Modbus/functions/mbfuncinput.su ./Middlewares/Modbus/functions/mbfuncinput_m.d ./Middlewares/Modbus/functions/mbfuncinput_m.o ./Middlewares/Modbus/functions/mbfuncinput_m.su ./Middlewares/Modbus/functions/mbfuncother.d ./Middlewares/Modbus/functions/mbfuncother.o ./Middlewares/Modbus/functions/mbfuncother.su ./Middlewares/Modbus/functions/mbutils.d ./Middlewares/Modbus/functions/mbutils.o ./Middlewares/Modbus/functions/mbutils.su

.PHONY: clean-Middlewares-2f-Modbus-2f-functions

