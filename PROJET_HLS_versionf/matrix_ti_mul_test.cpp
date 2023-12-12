//*****************************************************************************
// A simple testbench to simulate
// matrix multiplication of floating points and the AXI-Stream core.
//
// by G.Sutter for teaching purposes
// Revision History:
//  - march 2014, for Vivado HLS 2013.3
//
//*****************************************************************************
#include <iostream>
#include "matrix_ti_mul.h"

void gen_matrix_b(mat_b_t b[MAT_DIM][MAT_DIM]);
void gen_matrix_a(mat_a_t a[MAT_DIM][MAT_DIM]);

void gen_sw_matmult(mat_a_t a[MAT_DIM][MAT_DIM], mat_b_t b[MAT_DIM][MAT_DIM],result_t sw_res[MAT_DIM][MAT_DIM]);
void check_matmult_result( result_t hw_res[MAT_DIM][MAT_DIM], result_t sw_res[MAT_DIM][MAT_DIM], int &err_cnt);

using namespace std;

void inversion_matrixfloat(float A[MAT_DIM][MAT_DIM]) {
	float Ainverse[MAT_DIM][MAT_DIM] ;

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




/*
float sign(float in){return (in < 0 ? -1 : 1);}

void compute_matmult_mean_err(
    result_t hw_res[MAT_DIM][MAT_DIM],
    float *mean_err)
{
	float accum;
	float sw_res[MAT_DIM][MAT_DIM];
	float tmp;

	for(int i = 0; i < MAT_DIM; i++) {
			for(int j = 0; j < MAT_DIM; j++) {
				union {	unsigned int ival; float oval; } converter;
				converter.ival = output[i * MAT_DIM + j];
				hw_result[i][j] = converter.oval;
			  //hw_result[i][j] = aValue.data ;
			}
		}

			tmp = (float)sw_res[i][j] - (float)hw_res[i][j];
			*mean_err += sign(tmp) * tmp;
	   }
	}
	*mean_err = *mean_err / (MAT_DIM * MAT_DIM);
}
*/

//----------------------------------------------------
// Test the streaming interface.
int test_matrix_mul_core()
{
   mat_a_t in_mat_a[MAT_DIM][MAT_DIM];
   mat_b_t in_mat_b[MAT_DIM][MAT_DIM];
   result_t hw_result[MAT_DIM][MAT_DIM], sw_result[MAT_DIM][MAT_DIM];
   gen_matrix_b(in_mat_b);
   gen_matrix_a(in_mat_a);

   UINT_VALUE input[2 * MAT_DIM * MAT_DIM];
   UINT_VALUE output[MAT_DIM * MAT_DIM];

   int i, j, err_cnt = 0;

   float mean_err = 0;





   for(i = 0; i < MAT_DIM; i++) {
   		for(j = 0; j < MAT_DIM; j++) {
   			union {	unsigned int oval; float ival; } converter;
   			converter.ival = in_mat_a[i][j];
   			input[i * MAT_DIM + j] = converter.oval;
   		}
   	}

   	for(i = 0; i < MAT_DIM; i++) {
   		for(j = 0; j < MAT_DIM; j++) {
   			union {	unsigned int oval; float ival; } converter;
   			converter.ival = in_mat_b[i][j];
   			input[MAT_DIM * MAT_DIM + i * MAT_DIM + j] = converter.oval;
   		}
   	}

   	   transMatrix(in_mat_b);
   	   inversion_matrix(in_mat_a);


   gen_sw_matmult(in_mat_a, in_mat_b, sw_result);



   //convert matrix in input stream


   // Run the Vivado-HLS matrix multiply block
   matrixmul_accel_core(input, output);

   //convert  output stream in matrix
	for(i = 0; i < MAT_DIM; i++) {
		for(j = 0; j < MAT_DIM; j++) {
			union {	unsigned int ival; float oval; } converter;
			converter.ival = output[i * MAT_DIM + j];
			hw_result[i][j] = converter.oval;
		  //hw_result[i][j] = aValue.data ;
		}
	}

   cout << "Result by HW" << endl;
   check_matmult_result(hw_result, sw_result, err_cnt);

   //compute_matmult_mean_err(hw_result, &mean_err);

   cout << "Mean error between float and fixed point: " << mean_err << endl;

   if (err_cnt)
      cout << "ERROR: " << err_cnt << " mismatches detected!" << endl;
   else
      cout << "Test passed. No errors" << endl;

   return err_cnt;
}

//----------------------------------------------------
void gen_matrix_b(mat_b_t b[MAT_DIM][MAT_DIM])
{

	for(int i = 0; i < MAT_DIM; i++) {
		  for(int j = 0; j < MAT_DIM; j++) {
		  b[i][j] = (float)(i * j) / (MAT_DIM * MAT_DIM);
	   }
	}
}


//----------------------------------------------------

void gen_matrix_a(mat_a_t a[MAT_DIM][MAT_DIM]) {
	/*for (int i =0 ; i<MAT_DIM;i++) {
		for (int j=0 ;j<MAT_DIM;j++) {
			if (j>=i) a[i][j]=1+j+i;
			else a[i][j]=0;
		}
	}*/
	for(int i = 0; i < MAT_DIM; i++) {
			  for(int j = 0; j < MAT_DIM; j++) {
				  if (i>j) {
					  a[i][j] = float(i+j) / (2*MAT_DIM);
				  }
				  else if (i==j) a[i][j]=1+ (float)(i * j) / (MAT_DIM * MAT_DIM);
				  else a[i][j]=0;
		   }

		}

}

//----------------------------------------------------
void gen_sw_matmult(
    mat_a_t a[MAT_DIM][MAT_DIM],
    mat_b_t b[MAT_DIM][MAT_DIM],
    result_t sw_res[MAT_DIM][MAT_DIM])
{

	// Generate the expected result
	// Iterate over the rows of the A matrix
	for(int i = 0; i < MAT_DIM; i++) {
	   // Iterate over the columns of the B matrix
		  for(int j = 0; j < MAT_DIM; j++) {
		  sw_res[i][j] = 0;
		  // Do the inner product of a row of A and col of B
		  for(int k = 0; k < MAT_DIM; k++) {
			 sw_res[i][j] += a[i][k] * b[k][j];
		  }
	   }
	}
}
//----------------------------------------------------
void check_matmult_result(
    result_t hw_res[MAT_DIM][MAT_DIM],
    result_t sw_res[MAT_DIM][MAT_DIM],
    int &err_cnt)
{
// Print result matrix
cout << "{" << endl;
for (int i = 0; i < MAT_DIM; i++) {
   cout << "{";
   for (int j = 0; j < MAT_DIM; j++) {
      cout << hw_res[i][j];
      // Check HW result against SW
      if (hw_res[i][j] != sw_res[i][j]) {
         err_cnt++;
         cout << "*";
      }
      if (j == MAT_DIM - 1)
         cout << "}" << endl;
      else
         cout << ",";
   }
}
cout << "}" << endl;
}

//----------------------------------------------------
int main(int argc, char **argv)
{
	int err_cnt;

	//err_cnt = test_matrix_mul();
    err_cnt = test_matrix_mul_core();

	return err_cnt;
}


