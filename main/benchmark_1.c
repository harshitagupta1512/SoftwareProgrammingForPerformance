#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "time.h"
#include <sys/time.h>
#include <stdlib.h>
#include "helper.h"
#include "cblas.h"
#include "helper.c"

#define DEFAULT_VECTOR_LENGTH_N 1000000

const int n = DEFAULT_VECTOR_LENGTH_N;
// scalars
float a = 0.2;

// const int threads = 12;

void add()
{
    // add 2 vectors
    float *A = (float *)malloc(n * sizeof(float));
    float *B = (float *)malloc(n * sizeof(float));
    float *C = (float *)malloc(n * sizeof(float));

    struct timeval calc;
    double calctime;

    RandomVector(n, A);
    RandomVector(n, B);

    float mem = 1e-09 * 4.0 * 3 * n;
    float gflops = n * 1e-09;
    tick(&calc);
#pragma omp parallel for
    for (int i = 0; i < n; i++)
    {
        C[i] = A[i] + B[i];
    }
    calctime = tock(&calc);

    printf("Memory bandwidth for  : %f\n", mem / calctime);
         printf("Compute Throughput (in GFlops/s): %f\n", gflops / calctime);

    return;
}

int main(void)
{
    srand(time(NULL));

    printf("BENCHMARKS\n");
    add();

    return (0);
}