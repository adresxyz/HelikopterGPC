#ifndef MATRIXVECTOROP
#define MATRIXVECTOROP

typedef struct
{
    double** mat;
    int row;
    int col;
}Matrix;

typedef struct
{
    int nA;
    int nB;
    int k;
    double* A;
    double* B;
}ARX;

Matrix MatrixMult(Matrix* mat,Matrix* mau);
void MatrixMultptr(Matrix* mat,Matrix* mau,Matrix *out);
Matrix getMatrix(int row,int col, double A);
Matrix* getMatrixptr(int row,int col, double A);

Matrix getMatrixEye(int row, int col, double A);
Matrix* getMatrixEyeptr(int row,int col, double A);
double** matMult(double** mat,double** mau,int l,int m,int n );
void freeMatrix(Matrix* mat);



void moveTableLeft(double* A,int size);
void pushStop(double New,double* A,int size);
void pushStart(double New,double* A,int size);
#endif // MATRIXVECTOROP

