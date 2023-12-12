############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2020 Xilinx, Inc. All Rights Reserved.
############################################################
open_project PROJET_HLS_zynq
set_top matrixmul_accel_core
add_files matrix_ti_mul.h
add_files matrix_ti_mul.cpp
add_files -tb matrix_ti_mul_test.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution1" -flow_target vivado
set_part {xc7z020-clg484-1}
create_clock -period 10 -name default
source "./PROJET_HLS_zynq/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
