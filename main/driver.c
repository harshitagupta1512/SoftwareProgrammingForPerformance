#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "helper.h"
#include "cblas.h"
// #include "blis.h"

#define DEFAULT_VECTOR_LENGTH_N 1000000
#define DEFAULT_VECTOR_LENGTH_M 1000
#define DEFAULT_VECTOR_LENGTH_K 1

// million
// computing Y = aX + Y

// COMMAND LINE ARGUMENTS FORMAT
//  make program_name # for BLAS level 1
//  make program_name option # for BLAS level 3(sgemv) option = 0/1/2/3, rowmajor-notranspose/columnmajor-notranspose/rowmajor-transpose/columnmajor-transpose

int main(int argc, char *argv[])
{
    long long int n; // vector size and number of columns for matrix A
    long long int m; // number of rows for matrix A
    long long int k;

    n = DEFAULT_VECTOR_LENGTH_N;
    m = DEFAULT_VECTOR_LENGTH_M;
    k = DEFAULT_VECTOR_LENGTH_K;

    float array[6][2];
    srand((unsigned)time(NULL));
    int i = 0;

    for (n = 1000; n < 7000; n += 1000)
    {
        struct timeval calc;
        double calctime;
        calctime = 0.0;

        int option;

        float a = 0.8; // scalar value
        float b = 0.2; // scalar value

        // double *X, *Y;

        // float *A;
        // float *B;
        // float *C;

        float *A = (float *)malloc(m * n * sizeof(float));
        float *B = (float *)malloc(m * n * sizeof(float));
        float *C = (float *)malloc(m * n * sizeof(float));
        RandomVector(m * n, A);
        // RandomVector(m * n, B);
        // RandomVector(m * n, C);

        // DRandomVector(n, X);
        // DRandomVector(n, Y);

        char function_name[10];
        // printf("Enter function\n");
        strcpy(function_name, "sgemm");
        int err;
        // err = scanf("%s", function_name);
        double gflops;
        float mem_bw;

        if (strcmp(function_name, "saxpy") == 0)
        {
            float *X, *Y;

            X = (float *)malloc(n * sizeof(float));
            Y = (float *)malloc(n * sizeof(float));

            RandomVector(n, X);
            RandomVector(n, Y);

            tick(&calc);
            Saxpy(n, a, X, Y);

            calctime = tock(&calc);
            gflops = 2.0 * n * 1e-09;
            mem_bw = 8.0 * n * 1e-09; // amount of data fetched from memory

            free(X);
            free(Y);
        }
        else if (strcmp(function_name, "dscal") == 0)
        {
            double *X;
            X = (double *)malloc(n * sizeof(double));
            DRandomVector(n, X);
            tick(&calc);
            Dscal(n, a, X, 1);
            calctime = tock(&calc);
            gflops = 2.0 * n * 1e-09;
            mem_bw = 16.0 * n * 1e-09; // amount of data fetched from memory

            free(X);
        }
        else if (strcmp(function_name, "sscal") == 0)
        {
            float *X;
            X = (float *)malloc(n * sizeof(float));
            RandomVector(n, X);
            tick(&calc);
            Sscal(n, a, X, 1);
            calctime = tock(&calc);
            gflops = n * 1e-09;
            mem_bw = 4.0 * n * 1e-09; // amount of data fetched from memory
            free(X);
        }
        else if (strcmp(function_name, "daxpy") == 0)
        {
            double *X, *Y;
            X = (double *)malloc(n * sizeof(double));
            Y = (double *)malloc(n * sizeof(double));
            DRandomVector(n, X);
            DRandomVector(n, Y);
            tick(&calc);
            Daxpy(n, a, X, Y);
            calctime = tock(&calc);
            gflops = 2.0 * n * 1e-09;
            mem_bw = 16.0 * n * 1e-09; // amount of data fetched from memory
        }
        else if (strcmp(function_name, "sgemv") == 0)
        {
            float *X, *Y;
            // check option
            printf("Enter option\n");
            // err = scanf("%d", &option);
            option = 0;

            if (option == 0)
            {
                X = (float *)malloc(n * sizeof(float));
                Y = (float *)malloc(m * sizeof(float));

                RandomVector(n, X);
                RandomVector(m, Y);

                tick(&calc);
                cblas_sgemv(CblasRowMajor, CblasNoTrans, m, n, a, A, n, X, 1, b, Y, 1);

                gflops = 2.0 * (n + 1) * m * 1e-09;
                mem_bw = 4.0 * (n + m + m * n) * 1e-09; // amount of data fetched from memory
                calctime = tock(&calc);
            }
            else if (option == 1)
            {
                X = (float *)malloc(n * sizeof(float));
                Y = (float *)malloc(m * sizeof(float));

                RandomVector(n, X);
                RandomVector(m, Y);

                tick(&calc);
                cblas_sgemv(CblasColMajor, CblasNoTrans, m, n, a, A, m, X, 1, b, Y, 1);
                gflops = 2.0 * (n + 1) * m * 1e-09;
                mem_bw = 4.0 * (n + m + m * n) * 1e-09; // amount of data fetched from memory
                calctime = tock(&calc);
            }
            else if (option == 2)
            {
                X = (float *)malloc(m * sizeof(float));
                Y = (float *)malloc(n * sizeof(float));

                RandomVector(m, X);
                RandomVector(n, Y);
                // lda = n = number of columns
                tick(&calc);

                cblas_sgemv(CblasRowMajor, CblasTrans, m, n, a, A, n, X, 1, b, Y, 1);

                gflops = 2.0 * (n + 1) * m * 1e-09;
                mem_bw = 4.0 * (n + m + m * n) * 1e-09; // amount of data fetched from memory
                calctime = tock(&calc);
            }
            else
            {
                X = (float *)malloc(m * sizeof(float));
                Y = (float *)malloc(n * sizeof(float));

                RandomVector(m, X);
                RandomVector(n, Y);

                tick(&calc);
                cblas_sgemv(CblasColMajor, CblasTrans, m, n, a, A, m, X, 1, b, Y, 1);
                gflops = 2.0 * (n + 1) * m * 1e-09;
                mem_bw = 4.0 * (n + m + m * n) * 1e-09; // amount of data fetched from memory
                calctime = tock(&calc);
            }
        }
        else if (strcmp(function_name, "sgemm") == 0)
        {
            m = n;
            k = n;
            float *X, *Y;
            // printf("Enter option\n");
            // err = scanf("%d", &option);
            option = 0;

            // option 0(nt, nt)
            // option 1(t, nt)
            // option 2(nt, t)
            // option 3(t, t)

            if (option == 0)
            {
                // row major, transpose, noTranspose
                calctime = 0;
                tick(&calc);
                cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m, n, k, 1, A, n, B, k, 1, C, k);
                gflops = 2 * n * n * (n + 1) * 1e-09;
                mem_bw = 12.0 * n * n * 1e-09;
                calctime = tock(&calc);
            }
            else if (option == 1)
            {
                calctime = 0;
                tick(&calc);
                cblas_sgemm(CblasRowMajor, CblasTrans, CblasNoTrans, m, n, k, 1, A, n, B, k, 1, C, k);
                gflops = 2 * n * n * (n + 1) * 1e-09;
                mem_bw = 12.0 * n * n * 1e-09;
                calctime = tock(&calc);
            }
            else if (option == 2)
            {
                calctime = 0;
                tick(&calc);
                cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasTrans, m, n, k, 1, A, n, B, k, 1, C, k);
                gflops = 2 * n * n * (n + 1) * 1e-09;
                mem_bw = 12.0 * n * n * 1e-09;
                calctime = tock(&calc);
            }
            else
            {
                calctime = 0;
                tick(&calc);
                cblas_sgemm(CblasRowMajor, CblasTrans, CblasTrans, m, n, k, 1, A, n, B, k, 1, C, k);
                gflops = 2 * n * n * (n + 1) * 1e-09;
                mem_bw = 12.0 * n * n * 1e-09;
                calctime = tock(&calc);
            }
        }

        // Changes as per the problem
        // 4.0 - float
        // 8.0 - double
        // 8.0 - 2 vectors (float)
        // float mem_bw = 8.0 * n * 1e-09 / calctime; // amount of data fetched from memory

        mem_bw = mem_bw / calctime;

        printf("Time (in milli-secs) %f\n", calctime * 1000);
        printf("Memory Bandwidth (in GBytes/s): %f\n", mem_bw);
        printf("Compute Throughput (in GFlops/s): %f\n", gflops / calctime);

        array[i][0] = n;
        array[i][1] = gflops / calctime;
        i++;
        // free(A);
        // free(B);
        // free(C);
    }
    for (int i = 0; i < 6; i++)
    {
        -printf("%f %f\n", array[i][0], array[i][1]);
    }
    // free(X);
    // free(Y);
}