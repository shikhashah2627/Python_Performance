#include<stdlib.h>
#include<iostream>
#include<math.h>
//#include<comp.h>

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

int main(int argc, char *argv[]) {
    if (argc == 1) {
        cerr << "Usage " << argv[0] << "start end divisions \n";
        exit(1);
    }

    double start,end;
    int divisions;
    start = atof(argv[1]);
    end = atof(argv[2]);
    divisions = atoi(argv[3]);

    double finalRes = integrate(start, end, divisions, testf);

    cout << finalRes << endl;
    return 0;
}