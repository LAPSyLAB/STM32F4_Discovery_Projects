################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
C:/Users/rozman/OneDrive\ -\ Univerza\ v\ Ljubljani/Delovni/Workspaces/CubeIDE/STM32F4_Discovery_Projects/Audio_playback_and_record/SW4STM32/startup_stm32f407xx.s 

OBJS += \
./Application/SW4STM32/startup_stm32f407xx.o 

S_DEPS += \
./Application/SW4STM32/startup_stm32f407xx.d 


# Each subdirectory must supply rules for building sources it contributes
Application/SW4STM32/startup_stm32f407xx.o: C:/Users/rozman/OneDrive\ -\ Univerza\ v\ Ljubljani/Delovni/Workspaces/CubeIDE/STM32F4_Discovery_Projects/Audio_playback_and_record/SW4STM32/startup_stm32f407xx.s Application/SW4STM32/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -c -x assembler-with-cpp -MMD -MP -MF"Application/SW4STM32/startup_stm32f407xx.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

