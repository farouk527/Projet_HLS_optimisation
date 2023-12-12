############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2020 Xilinx, Inc. All Rights Reserved.
############################################################
set_directive_inline -off "matrixmul"
set_directive_top -name matrixmul_accel_core "matrixmul_accel_core"
set_directive_pipeline "read_inputs/read_a2"
set_directive_pipeline "read_inputs/read_b2"
set_directive_pipeline "transMatrix/transMatrix_label1"
set_directive_array_partition -type complete -dim 0 "transMatrix" mat_b
