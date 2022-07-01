void tick(struct timeval *t);
double tock(struct timeval *t);
void RandomVector(int n, float *A);
void DRandomVector(int n, double *A);
void Saxpy(int n, float a, float *X, float *Y);
void Daxpy(int n, float a, double *X, double *Y);
void Sscal(int n, float alpha, float *X, int incX);
void Dscal(int n, double alpha, double *X, int incX);
