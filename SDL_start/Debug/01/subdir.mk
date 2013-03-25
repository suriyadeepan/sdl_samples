################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../01/sdl_image_load.cpp 

OBJS += \
./01/sdl_image_load.o 

CPP_DEPS += \
./01/sdl_image_load.d 


# Each subdirectory must supply rules for building sources it contributes
01/%.o: ../01/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


