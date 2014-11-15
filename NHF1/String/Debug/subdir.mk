################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/media/Dropbox/Dropbox/Peti/BME/5_felev/C++11/NHF1/string.cpp \
/media/Dropbox/Dropbox/Peti/BME/5_felev/C++11/NHF1/test.cpp 

OBJS += \
./string.o \
./test.o 

CPP_DEPS += \
./string.d \
./test.d 


# Each subdirectory must supply rules for building sources it contributes
string.o: /media/Dropbox/Dropbox/Peti/BME/5_felev/C++11/NHF1/string.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	clang++ -O0 -g3 -pedantic -Wall -Wextra -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

test.o: /media/Dropbox/Dropbox/Peti/BME/5_felev/C++11/NHF1/test.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	clang++ -O0 -g3 -pedantic -Wall -Wextra -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


