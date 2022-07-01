void Daxpy(int n, double a, double *X, double *Y)
{
    // #pragma ivdep
    // #pragma omp simd
    #pragma omp parallel for
    // #pragma vector nodynamic_align

    for (int i = 0; i < n; ++i)
        Y[i] = a * X[i] + Y[i];
}