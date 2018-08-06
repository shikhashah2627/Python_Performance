#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <cstdint>


int size, num_threads;
double **A, **B, **C;

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


/**
 * Thread routine.
 * Each thread works on a portion of the 'matrix1'.
 * The start and end of the portion depend on the 'arg' which
 * is the ID assigned to threads sequentially. 
 */
void * worker( void* arg )
{
    int i, j, k, portion_size, row_start, row_end;
    double sum;
    cout << "inside worker" << endl;
    int tid = *(int*)arg; // get the thread ID assigned sequentially.
    portion_size = size / num_threads;
    cout << size << endl;
    row_start = tid * portion_size;
    cout << row_start << endl;
    row_end = (tid+1) * portion_size;
    cout << row_end << endl;

    for (i = row_start; i < row_end; ++i) { // hold row index of 'matrix1'
        for (j = 0; j < size; ++j) { // hold column index of 'matrix2'
            sum = 0; // hold value of a cell
            /* one pass to sum the multiplications of corresponding cells
            in the row vector and column vector. */
            for (k = 0; k < size; ++k) { 
                sum += A[ i ][ k ] * B[ k ][ j ];
            }
            C[i][j] = sum;
            cout<<"matrix values" << endl;
            cout << C[i][j]<<endl;
        }
    }
}

int main(int argc, char *argv[]) {

int K,L,M;

int i;
double sum = 0;
struct timeval tstart, tend;
double exectime;

K = atoi(argv[1]);
L = atoi(argv[2]);
M = atoi(argv[3]);
num_threads = atoi(argv[4]);

pthread_t  threads[num_threads];

// initializing matrix 
A = new double*[L];
B = new double*[M];
C = new double*[M];

// pointer initialization.
for(int i = 0; i< L; i++) {
    A[i] = new double[K];
}
for(int i = 0; i < M; i++) {
    B[i] = new double[L];
}
for(int i = 0; i< M; i++) {
    C[i] = new double[K];
}

C[K][M] = {0.0};

matrix_creation(K,L,A);
matrix_creation(L,M,B);

size = K;

if ( size % num_threads != 0 ) {
    cout << "error";
    return -1;
}

//threads = (pthread_t *) malloc( num_threads * sizeof(pthread_t) );

//gettimeofday( &tstart, NULL );
int *tid,  x;
tid = &x;
for ( i = 0; i < num_threads; ++i ) { 
    //tid = &i;  
    *tid = i;
    cout << "finally calling output"<<endl;
    pthread_create( &threads[i], NULL, worker, (void *)tid );
}

for ( i = 0; i < num_threads; ++i ) {
pthread_join( threads[i], NULL );
}
gettimeofday( &tend, NULL );

exectime = (tend.tv_sec - tstart.tv_sec) * 1000.0; // sec to ms
exectime += (tend.tv_usec - tstart.tv_usec) / 1000.0; // us to ms   

//printf( "Number of MPI ranks: 0\tNumber of threads: %d\tExecution time:%.3lf sec\n",
        //num_threads, exectime/1000.0);

return 0;
}
