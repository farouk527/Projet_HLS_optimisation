################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
H:/Bureau/PROJET_HLS_versionf/matrix_ti_mul_test.cpp 

OBJS += \
./testbench/matrix_ti_mul_test.o 

CPP_DEPS += \
./testbench/matrix_ti_mul_test.d 


# Each subdirectory must supply rules for building sources it contributes
testbench/matrix_ti_mul_test.o: H:/Bureau/PROJET_HLS_versionf/matrix_ti_mul_test.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -IC:/Logiciels/xilinx/Vitis/2020.1/win64/tools/systemc/include -IC:/Logiciels/xilinx/Vitis/2020.1/win64/tools/auto_cc/include -IC:/Logiciels/xilinx/Vitis/2020.1/include/etc -IC:/Logiciels/xilinx/Vitis/2020.1/include -IH:/Bureau/PROJET_HLS_versionf -IC:/Logiciels/xilinx/Vitis/2020.1/include/ap_sysc -O0 -g3 -Wall -Wno-unknown-pragmas -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"testbench/matrix_ti_mul_test.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


