#include<iostream>
#include<stdlib.h>
#include<math.h>
#include"omp.h"

using namespace std;

double testf(double x) {
    return x*x+2*sin(x);
}

double integrate(double st, double en, int div, double (*f)(double) ) {
    double localRes = 0;
    double step = (en - st) / div;
    double x = st;
    localRes = f(st) + f(en);
    localRes  /= 2;
    for (int i = 1; i < div; i++) {
        x += step;
        localRes += f(x);
    }
    localRes += step;
    return localRes;
}

int main(int argc, char **argv) {
    if (argc == 1) {
        cerr << "Usage " << argv[0] << "start end divisions \n";
        exit(1);
    }

    double start,end;
    int divisions;
    start = atof(argv[1]);
    end = atof(argv[2]);
    divisions = atoi(argv[3]);

    int N = omp_get_max_threads(); // get the number of threads for parallel region.
    divisions = (divisions / N) * N;
    double step = ( end - start ) / divisions;
    double finalRes = 0;
    
#pragma omp parallel 
{
    int localDiv = divisions / N;
    int ID = omp_get_thread_num();
    double localStart = start + ID * localDiv * step;
    double localEnd = localStart + localDiv * step;
    finalRes += integrate(localStart,localEnd,localDiv,testf);
}

    cout << finalRes << endl;
    //cout << "Hello from thread " << omp_get_thread_num () << endl;

    return 0;
}    