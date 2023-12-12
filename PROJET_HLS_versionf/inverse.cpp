#include <iostream>

const int N = 4;  
const int MAT_DIM=N;


void transMatrix(int mat_b[MAT_DIM][MAT_DIM]) {
    int temp;
    int i, j;

    for (i = 0; i < MAT_DIM-1; i++) {
    	for (int j =i + 1; j < MAT_DIM; j++) {
    	             temp = mat_b[i][j];
    	             mat_b[i][j] = mat_b[j][i];
    	             mat_b[j][i] = temp;
    }
  }
}

void inversion_matrix(double A[N][N], double Ainverse[N][N]) {

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            Ainverse[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }
    for (int colonne = N - 1; colonne >= 0; colonne--) {
        for (int ligne = colonne - 1; ligne >= 0; ligne--) {
            double factor = -A[ligne][colonne] / A[colonne][colonne];
            for (int k = 0; k < N; k++) {
                A[ligne][k] += factor * A[colonne][k];
                Ainverse[ligne][k] += factor * Ainverse[colonne][k];
            }
        }
    }
    for (int i = 0; i < N; i++) {
        double divisor = A[i][i];
        for (int j = 0; j < N; j++) {
            A[i][j] /= divisor;
            Ainverse[i][j] /= divisor;
        }
    }
}

int main() {
    // Exemple d'utilisation avec une matrice triangulaire supérieure
    double A[N][N] = {{1, 2, 3,4},
                      {0, 5, 6,7},
                      {0, 0, 8,9},
                      {0, 0, 0,10}};

    double Ainverse[N][N];

    // Inverser la matrice
    inversion_matrix(A, Ainverse);

    // Afficher la matrice inversée (pour le débogage)
    std::cout << "Matrice inversée :" << std::endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << Ainverse[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

