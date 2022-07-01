void Dscal(const int N, const double alpha, double *X, const int incX)
{
    // # pragma ivdep
    // # pragma omp simd
    // # pragma omp parallel for
    // # pragma vector nodynamic_align

    for (int i = 0; i < N; ++i)
        X[i * incX] *= alpha;
}