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
            cblas_sgemv(CblasRowMajor, CblasTrans, N, K, alpha, B, ldb, A + i * lda, 1, beta, C + i * ldc, 1);
        }
    }
    else if (TransA == CblasNoTrans && TransB == CblasTrans)
    {
        for (int i = 0; i < M; i++)
        {
            cblas_sgemv(CblasRowMajor, CblasNoTrans, K, N, alpha, B, N, A + i * lda, 1, beta, C + i * ldc, 1);
        }
    }
    else if (TransA == CblasTrans && TransB == CblasNoTrans)
    {
        for (int i = 0; i < M; i++)
        {
            cblas_sgemv(CblasRowMajor, CblasTrans, N, K, alpha, B, ldb, A + i, lda, beta, C + i * ldc, 1);
        }
    }
    else if (TransA == CblasTrans && TransB == CblasTrans)
    {
        for (int i = 0; i < M; i++)
        {
            cblas_sgemv(CblasRowMajor, CblasNoTrans, K, N, alpha, B, N, A + i, lda, beta, C + i * ldc, 1);
        }
    }
}