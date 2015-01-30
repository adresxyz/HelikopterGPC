#ifndef MATRIXVECTOROP
#define MATRIXVECTOROP

typedef struct
{
    float** mat;
    int row;
    int col;
}Matrix;

typedef struct
{
    int nA;
    int nB;
    int k;
    float* A;
    float* B;
}ARX;

Matrix MatrixMult(Matrix* mat,Matrix* mau);
void MatrixMultptr(Matrix* mat,Matrix* mau,Matrix *out);
Matrix getMatrix(int row,int col, float A);
Matrix* getMatrixptr(int row,int col, float A);

Matrix getMatrixEye(int row, int col, float A);
Matrix* getMatrixEyeptr(int row,int col, float A);
float** matMult(float** mat,float** mau,int l,int m,int n );
void freeMatrix(Matrix* mat);



void moveTableLeft(float* A,int size);
void pushStop(float New,float* A,int size);
void pushStart(float New,float* A,int size);
#endif // MATRIXVECTOROP

