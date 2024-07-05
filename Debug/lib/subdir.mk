################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lib/LED_Matrix.cpp \
../lib/WS2812.cpp \
../lib/task.cpp 

OBJS += \
./lib/LED_Matrix.o \
./lib/WS2812.o \
./lib/task.o 

CPP_DEPS += \
./lib/LED_Matrix.d \
./lib/WS2812.d \
./lib/task.d 


# Each subdirectory must supply rules for building sources it contributes
lib/%.o lib/%.su lib/%.cyclo: ../lib/%.cpp lib/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m0plus -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G030xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I../lib -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-lib

clean-lib:
	-$(RM) ./lib/LED_Matrix.cyclo ./lib/LED_Matrix.d ./lib/LED_Matrix.o ./lib/LED_Matrix.su ./lib/WS2812.cyclo ./lib/WS2812.d ./lib/WS2812.o ./lib/WS2812.su ./lib/task.cyclo ./lib/task.d ./lib/task.o ./lib/task.su

.PHONY: clean-lib

