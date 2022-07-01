#include "cblas.h"

void cblas_sgemm(enum CBLAS_ORDER Order, enum CBLAS_TRANSPOSE TransA,
                 enum CBLAS_TRANSPOSE TransB, int M, int N,
                 int K, float alpha, float *A,
                 int lda, float *B, int ldb,
                 float beta, float *C, int ldc)
{

    if (TransA == CblasNoTrans && TransB == CblasNoTrans)
    {
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                float sum = 0;
                for (int k = 0; k < K; k++)
                {
                    sum += A[i * lda + k] * B[k * ldb + j];
                }
                C[i * ldc + j] = alpha * sum + beta * C[i * ldc + j];
            }
        }
    }
    else if (TransA == CblasNoTrans && TransB == CblasTrans)
    {
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                float sum = 0;
                for (int k = 0; k < K; k++)
                {
                    sum += A[i * lda + k] * B[j * ldb + k];
                }
                C[i * ldc + j] = alpha * sum + beta * C[i * ldc + j];
            }
        }
    }
    else if (TransA == CblasTrans && TransB == CblasNoTrans)
    {
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                float sum = 0;
                for (int k = 0; k < K; k++)
                {
                    sum += A[k * lda + i] * B[k * ldb + j];
                }
                C[i * ldc + j] = alpha * sum + beta * C[i * ldc + j];
            }
        }
    }
    else if (TransA == CblasTrans && TransB == CblasTrans)
    {
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                float sum = 0;
                for (int k = 0; k < K; k)
                {
                    sum += A[k * lda + i] * B[j * ldb + k];
                }
                C[i * ldc + j] = alpha * sum + beta * C[i * ldc + j];
            }
        }
    }
}