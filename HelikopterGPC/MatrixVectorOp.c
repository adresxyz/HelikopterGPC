
#include<math.h>
#include<stdlib.h>
#include<assert.h>
#include <stdio.h>

#include "matrixvectorop.h"
#include "gpcregler.h"
#define DEBUGINFO


//Matrix getMatrix(int row,int col, double A)
//{
//    int i,j;
//    double **data = (double **) malloc((unsigned)row * sizeof(double*));
//    for( i = 0; i < row; i++) data[i] = (double *)malloc((unsigned) col * sizeof(double));

//    for ( i = 0; i < row; ++i) {
//        for ( j = 0; j < col; ++j) {
//            data[i][j]=A;
//        }
//    }

//    Matrix mat;
//    mat.mat = data;
//    mat.col = col;
//    mat.row = row;
//    return mat;
//}

Matrix* getMatrixptr(int row,int col, double A)
{
    int i,j;
    double **data = (double **) malloc((unsigned)row * sizeof(double*));
    for( i = 0; i < row; i++) data[i] = (double *)malloc((unsigned) col * sizeof(double));

    for ( i = 0; i < row; ++i) {
        for ( j = 0; j < col; ++j) {
            data[i][j]=A;
        }
    }

    Matrix* mat = (Matrix*) malloc(sizeof(Matrix));
    mat->mat = data;
    mat->col = col;
    mat->row = row;
    return mat;
}

Matrix getMatrixEye(int row,int col,double A)
{
    int i,j;
    double ** y = (double **)malloc(row * sizeof(double*));
    for( i = 0; i < row; i++) y[i] = (double *)malloc(col * sizeof(double));

    for ( i = 0; i < row; ++i) {
        for ( j = 0; j < col; ++j) {
            y[i][j]=0;
        }
    }

    for ( i = 0; i < row && i< col; ++i) {
        y[i][i]=A;
    }


    Matrix mat;
    mat.mat = y;
    mat.col = col;
    mat.row = row;
    return mat;
}
Matrix* getMatrixEyeptr(int row,int col,double A)
{
    int i,j;
    double ** y = (double **)malloc(row * sizeof(double*));
    for( i = 0; i < row; i++) y[i] = (double *)malloc(col * sizeof(double));

    for ( i = 0; i < row; ++i) {
        for ( j = 0; j < col; ++j) {
            y[i][j]=0;
        }
    }

    for ( i = 0; i < row && i< col; ++i) {
        y[i][i]=A;
    }

    Matrix* mat = (Matrix*) malloc(sizeof(Matrix));
    mat->mat = y;
    mat->col = col;
    mat->row = row;
    return mat;
}
void freeMatrix(Matrix* mat)
{
    int i;
    for( i = 0; i < mat->row; i++) free(mat->mat[i]);
    free(mat->mat);
}

void freeMatrixV(Matrix mat)
{
    int i;
    for( i = 0; i < mat.row; i++) free(mat.mat[i]);
    free(mat.mat);
}



Matrix MatrixMult(Matrix* mat,Matrix* mau)
{
    /// Allocating new Matrix
    Matrix rMatrix;
    /// Copying data
    rMatrix.mat =(double**) matMult(mat->mat,mau->mat,mat->row,mat->col,mau->col);
    rMatrix.col = mau->col;
    rMatrix.row = mat->row;
    return rMatrix;
}

void MatrixMultptr(Matrix* mat,Matrix* mau,Matrix *out)
{
    /// Copying data
    //out->mat =(double**) matMult(mat->mat,mau->mat,mat->row,mat->col,mau->col);
    int l=mat->row, m=mat->col, n=mau->col;
    int i,j,k;
    for ( i = 0; i < l; ++i) {
        for ( j = 0; j < n; ++j) {
            out->mat[i][j]=0;
            for ( k = 0; k < m; ++k) {
                out->mat[i][j]+=mat->mat[i][k] * mau->mat[k][j];
            }
        }
    }

    out->col = mau->col;
    out->row = mat->row;
}


/**
 * @brief MatrixMult
 * @param mat - first matrix
 * @param mau - second matrix
 * @param n - #of rows of f.m.
 * @param m - #of cols of f.m.
 * @param o - #of cols of s.m.
 * @return
 */
double **matMult(double** mat,double** mau,int l,int m,int n )
{

#ifdef DEBUGINFO
    assert(mat!=0);
    assert(mau!=0);
#endif

    int i,j,k;
    double** NewMatrix = (double**)malloc(l*sizeof(double));

    // Allocation of output
    for ( i = 0; i < l; ++i) {
        NewMatrix[i] = (double *)malloc(n * sizeof(double));
    }


    for ( i = 0; i < l; ++i) {
        for ( j = 0; j < n; ++j) {
            NewMatrix[i][j]=0;
            for ( k = 0; k < m; ++k) {
                NewMatrix[i][j]+=mat[i][k] * mau[k][j];
            }
        }
    }

    return NewMatrix;

}




void moveTableLeft(double* A,int size)
{
    int i;
    for (i = 1; i < size; ++i) {
        A[i-1]=A[i];
    }
}

void pushStop(double New,double* A,int size)
{
    int i;
    for (i = 1; i < size; ++i) {
        A[i-1]=A[i];
    }
    A[size-1]=New;
}

void pushStart(double New,double* A,int size)
{
    int i;
    for (i = size-1; i >0; --i) {
        A[i]=A[i-1];
    }
    A[0]=New;
}
