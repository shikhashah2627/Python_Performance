#include<stdlib.h>
#include<iostream>
#include<ctime>
#include <omp.h>

using namespace std;

double matrix_creation(int rows, int columns, double **matrix) {
    srand((unsigned)time(0));
    for (int i = 0; i < rows; i ++) {
        for (int j = 0; j < columns; j++) {
            matrix[i][j] = rand()%10;
            //cout << "(" << i << "," << j << ")" << matrix[i][j] << endl;
        }
    }
    return matrix[rows][columns];
}
int main(int argc, char *argv[]) {

int K,L,M,thread_num;

K = atoi(argv[1]);
L = atoi(argv[2]);
M = atoi(argv[3]);
thread_num = atoi(argv[4]);

// initializing matrix 
double **A = new double*[L];
double **B = new double*[M];
double **C = new double*[M];

// pointer initialization.
for(int i = 0; i<= L; i++) {
    A[i] = new double[K];
}
for(int i = 0; i<= M; i++) {
    B[i] = new double[L];
}
for(int i = 0; i<= M; i++) {
    C[i] = new double[K];
}

C[K][M] = {0.0};

matrix_creation(K,L,A);
matrix_creation(L,M,B);

double x;
#pragma omp parallel for num_threads(thread_num) collapse(2)
    for (int i=0; i < K; i++) {
        for(int j=0; j < M; j++) {
            C[i][j] = 0;
            for(int k=0; k < L; k++) {
                //double x = A[i][k] * B[k][j];
                x = A[i][k] * B[k][j];
                //C[i][j] += (int)x%100;
                C[i][j] += x;
               // cout << i << "," << j << C[i][j];
            }
        }
    }

    // for(int i=0; i<K; i++) {
    //     for (int j=0;j<M;j++) {
    //         cout << i << "," << j << C[i][j] << "\n";
    //     }
    // }
}
   