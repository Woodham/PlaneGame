################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/BSP.cpp \
../src/Environment.cpp \
../src/GameObject.cpp \
../src/MD2.cpp \
../src/Main.cpp \
../src/PCX.cpp \
../src/Point.cpp \
../src/Projectile.cpp \
../src/Vector.cpp 

OBJS += \
./src/BSP.o \
./src/Environment.o \
./src/GameObject.o \
./src/MD2.o \
./src/Main.o \
./src/PCX.o \
./src/Point.o \
./src/Projectile.o \
./src/Vector.o 

CPP_DEPS += \
./src/BSP.d \
./src/Environment.d \
./src/GameObject.d \
./src/MD2.d \
./src/Main.d \
./src/PCX.d \
./src/Point.d \
./src/Projectile.d \
./src/Vector.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


