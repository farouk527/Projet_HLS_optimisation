#ifndef __MATRIXTIMUL_H__
#define __MATRIXTIMUL_H__

#include <cmath>
#include <ap_axi_sdata.h>
#include <hls_stream.h>
#include <ap_fixed.h>

using namespace std;

typedef ap_uint<32> UINT_VALUE;
typedef ap_axiu<32,4,5,5> AXI_VALUE;
#define MAT_DIM 32

typedef float mat_a_t;
typedef float mat_b_t;
typedef float result_t;


void matrixmul( mat_a_t a[MAT_DIM][MAT_DIM],mat_b_t b[MAT_DIM][MAT_DIM],result_t res[MAT_DIM][MAT_DIM]);

void matrixmul_accel_core (UINT_VALUE input[2 * MAT_DIM * MAT_DIM],UINT_VALUE output[MAT_DIM * MAT_DIM]);

void inversion_matrix(mat_a_t a[MAT_DIM][MAT_DIM]);
void transMatrix(mat_b_t b[MAT_DIM][MAT_DIM]);

void invMatrix(mat_a_t  a[MAT_DIM][MAT_DIM] ,mat_a_t  inv[MAT_DIM][MAT_DIM]);


#endif
