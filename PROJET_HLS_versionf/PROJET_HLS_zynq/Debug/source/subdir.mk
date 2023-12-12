################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
H:/Bureau/PROJET_HLS_versionf/matrix_ti_mul.cpp 

OBJS += \
./source/matrix_ti_mul.o 

CPP_DEPS += \
./source/matrix_ti_mul.d 


# Each subdirectory must supply rules for building sources it contributes
source/matrix_ti_mul.o: H:/Bureau/PROJET_HLS_versionf/matrix_ti_mul.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DAESL_TB -D__llvm__ -D__llvm__ -IC:/Logiciels/xilinx/Vitis/2020.1/win64/tools/systemc/include -IC:/Logiciels/xilinx/Vitis/2020.1/win64/tools/auto_cc/include -IC:/Logiciels/xilinx/Vitis/2020.1/include/etc -IC:/Logiciels/xilinx/Vitis/2020.1/include -IH:/Bureau/PROJET_HLS_versionf -IC:/Logiciels/xilinx/Vitis/2020.1/include/ap_sysc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


