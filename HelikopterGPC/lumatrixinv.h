#ifndef LUMATRIXINV
#define LUMATRIXINV
#define   TINY 1.0e-20

void inverse(float **mat, float **y, float *col, int *indx, int dim, float *vv);
void ludcmp(float **a, int n, int *indx, float *d, float *vv);
void lubksb(float **a, int n, int *indx, float *b);
#endif // LUMATRIXINV

