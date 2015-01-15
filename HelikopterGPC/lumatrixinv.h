#ifndef LUMATRIXINV
#define LUMATRIXINV
#define   TINY 1.0e-20

void inverse(double **mat, double **y, double *col, int *indx, int dim, double *vv);
void ludcmp(double **a, int n, int *indx, double *d, double *vv);
void lubksb(double **a, int n, int *indx, double *b);
#endif // LUMATRIXINV

