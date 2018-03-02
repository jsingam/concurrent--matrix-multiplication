#include <iostream>
#include <cstdlib>
#include <omp.h>

using namespace std;

int DIMENTION; //Dimension of the matrix

double ** populate();
void multiply(double **A, double **B, double **CC);
double random(double lower_bound, double upper_bound);
int main(int argc, const char * argv[]) {

    double **A;
    double **B;
    double **C;

    // get the matrix dimension as a command line argument
    if (argc == 2) {
        DIMENTION = atoi(argv[1]);
    } else {
        cout << " Please enter the dimention. instructions are given in the readme file.";
	exit(0);
    }

    A = populate();
    B = populate();
    C = populate();

    multiply(A, B, C);

    return 0;
}

/**
 * populate a matrix of dimension DIMxDIM with random values
 */
double ** populate() {
    double **D = new double*[DIMENTION];
    D = new double*[DIMENTION];

    srand(time(NULL));
    for (int i = 0; i < DIMENTION; i++) {
        D[i] = new double[DIMENTION];
        for (int j = 0; j < DIMENTION; j++) {
            D[i][j] = random(1,1000);

        }
    }
    return D;
}


void multiply(double **A, double **B, double **C) {
    double start, finish, elapsed;

    start = omp_get_wtime();
	
	#pragma omp parallel for // this will run parallel for loop
    for (int i = 0; i < DIMENTION; i++) {
        for (int j = 0; j < DIMENTION; j++) {
			double value = 0;
            for (int k = 0; k < DIMENTION; k++) {
                value += A[i][k] * B[k][j];
            }
            C[i][j] = value;
        }
    }

    finish = omp_get_wtime();

    elapsed = finish - start;

    cout << elapsed;
    cout << "\n";

    // free the memory after calculation
    for (int i = 0; i < DIMENTION; i++) {
        delete [] A[i];
        delete [] B[i];
        delete [] C[i];
    }
    delete []A;
    delete []B;
    delete []C;
}

/**
 * calculate a random value in the given range
 */
double random(double lower_bound, double upper_bound){
	double value;
	value = (double)rand() / RAND_MAX;
	return lower_bound + value*(upper_bound - lower_bound);
}

