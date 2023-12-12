#include "matrix_ti_mul.h"
#include <utils/x_hls_utils.h>


using namespace hls;


void read_inputs(
	UINT_VALUE input[2 *MAT_DIM * MAT_DIM],
	mat_a_t mat_a[MAT_DIM][MAT_DIM],
	mat_b_t mat_b[MAT_DIM][MAT_DIM])
{
	// stream in first matrix
	read_a1: for(int i=0; i< MAT_DIM; i++){
		read_a2: for(int j=0; j< MAT_DIM; j++){
			union {	unsigned int ival; float oval; } converter;
			converter.ival = input[i * MAT_DIM + j];
			mat_a[i][j] = converter.oval;
			//mat_a[i][j] = aValue.data;
		}
	}

	// stream in second matrix
	read_b1: for(int i=0; i< MAT_DIM; i++){
		read_b2: for(int j=0; j< MAT_DIM; j++){
			union {	unsigned int ival; float oval; } converter;
			converter.ival = input[MAT_DIM * MAT_DIM + i * MAT_DIM + j];
			mat_b[i][j] = converter.oval;
			//mat_b[i][j] = aValue.data;
		}
	}
}



void write_outputs(
	result_t mat_res[MAT_DIM][MAT_DIM],
	UINT_VALUE output[MAT_DIM * MAT_DIM])
{
	// stream out result matrix
	write_res1: for(int i = 0; i < MAT_DIM; i++){
		write_res2: for(int j = 0; j < MAT_DIM; j++){
#pragma HLS PIPELINE
			union {	unsigned int oval; float ival; } converter;
			converter.ival = mat_res[i][j];
			output[i * MAT_DIM + j] = converter.oval;
		}
	}
}


void inversion_matrix(mat_a_t A[MAT_DIM][MAT_DIM]) {
	mat_a_t Ainverse[MAT_DIM][MAT_DIM] ;

    A:for (int i = 0; i < MAT_DIM; i++) {
        B:for (int j = 0; j < MAT_DIM; j++) {
            Ainverse[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }
    C:for (int colonne = MAT_DIM - 1; colonne >= 0; colonne--) {
        D:for (int ligne = colonne - 1; ligne >= 0; ligne--) {
            double factor = -A[ligne][colonne] / A[colonne][colonne];
           E: for (int k = 0; k < MAT_DIM; k++) {
                A[ligne][k] += factor * A[colonne][k];
                Ainverse[ligne][k] += factor * Ainverse[colonne][k];
            }
        }
    }
    F:for (int i = 0; i < MAT_DIM; i++) {
        mat_a_t divisor = A[i][i];
        G:for (int j = 0; j < MAT_DIM; j++) {
            A[i][j] /= divisor;
            Ainverse[i][j] /= divisor;
        }
    }

   H: for (int i = 0; i < MAT_DIM; i++) {
            I:for (int j = 0; j < MAT_DIM; j++) {
                A[i][j] = Ainverse[i][j];
            }
        }


}





void transMatrix(mat_b_t mat_b[MAT_DIM][MAT_DIM]) {
    mat_b_t temp;
    int i, j;

    transMatrix_label0:for (i = 0; i < MAT_DIM-1; i++) {
    	transMatrix_label1: for (int j = i + 1; j < MAT_DIM; j++) {
    	             temp = mat_b[i][j];
    	             mat_b[i][j] = mat_b[j][i];
    	             mat_b[j][i] = temp;
    }
  }
}






void matrixmul(
      mat_a_t a[MAT_DIM][MAT_DIM],
      mat_b_t b[MAT_DIM][MAT_DIM],
      result_t res[MAT_DIM][MAT_DIM])
{
// partition with half dimension since BRAM has two ports
int const FACTOR = MAT_DIM/2;

  result_t accum;
  // Iterate over the rows of the A matrix
  Row: for(int i = 0; i < MAT_DIM; i++) {
    // Iterate over the columns of the B matrix

    Col: for(int j = 0; j < MAT_DIM; j++) {
      // Do the inner product of a row of A and col of B
      accum = 0;
      Prod: for(int k = 0; k < MAT_DIM; k++) {
        accum += reg(a[i][k] * b[k][j]);
        res[i][j] = accum; //if (k == (MAT_B_ROWS-1)) res[i][j] = accum;
      }

    }
  }
}





void matrixmul_accel_core (UINT_VALUE input[2 *MAT_DIM * MAT_DIM],UINT_VALUE output[MAT_DIM * MAT_DIM])
{
	mat_a_t mat_a[MAT_DIM][MAT_DIM];
	mat_b_t mat_b[MAT_DIM][MAT_DIM];
    result_t mat_res[MAT_DIM][MAT_DIM];
    int i, j;

   read_inputs(input, mat_a, mat_b);
   inversion_matrix(mat_a);
   transMatrix(mat_b);

	// do Matrix multiplication
	matrixmul(mat_a, mat_b, mat_res);

	write_outputs(mat_res, output);
}


