#include "cblas.h"
// #include "helper.h"
float cblas_sdot(const int N, const float *X, const int incX,
                 const float *Y, const int incY)
{
    float dot = 0.0;
// #pragma omp parallel for
    for (int i = 0; i < N; i++)
    {
        dot += X[i * incX] * Y[i * incY];
    }
    return dot;
}

void saxpy(int n, float a, float *X, float *Y)
{

    for (int i = 0; i < n; ++i)
        Y[i] = a * X[i] + Y[i];
}

void sscal(int N, float alpha, float *X, int incX)
{
// #pragma omp parallel for
    for (int i = 0; i < N; ++i)
        X[i * incX] *= alpha;
}

void cblas_sgemv(enum CBLAS_ORDER order,
                 enum CBLAS_TRANSPOSE TransA, int M, int N,
                 float alpha, float *A, int lda,
                 float *X, int incX, float beta,
                 float *Y, int incY)
{

    // Y = αAX + βY or Y = αAT X + βY

    if (order == CblasRowMajor && TransA == CblasNoTrans)
    {
        sscal(M, beta, Y, incY);

// #pragma omp parallel for

        for (int i = 0; i < M; i++)
        {
            Y[i * incY] = alpha * cblas_sdot(N, A + i * lda, 1, X, incX) + Y[i * incY];
        }
    }
    else if (order == CblasRowMajor && TransA == CblasTrans)
    {
        sscal(N, beta, Y, incY);

// #pragma omp parallel for

        for (int i = 0; i < M; i++)
        {
            saxpy(N, alpha * X[i * incX], A + i * lda, Y);
        }
    }
    else if (order == CblasColMajor && TransA == CblasNoTrans)
    {

        sscal(M, beta, Y, incY);

// #pragma omp parallel for

        for (int i = 0; i < N; i++)
        {
            saxpy(M, alpha * X[i * incX], A + i * lda, Y);
        }
    }
    else if (order == CblasColMajor && TransA == CblasTrans)
    {
        sscal(N, beta, Y, incY);
// #pragma omp parallel for

        for (int i = 0; i < N; i++)
        {
            Y[i] = alpha * cblas_sdot(M, A + i * lda, 1, X, incX) + Y[i];
        }
    }
}
