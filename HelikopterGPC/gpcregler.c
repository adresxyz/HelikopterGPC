#include "matrixvectorop.h"
#include "gpcregler.h"
#include "lumatrixinv.h"

#include<stdlib.h>
#include<stdio.h>

//#define SHOW_INFO


void GPC_Constructor(GPC* Regulator,ARX* model,
                     int H,int L,
                     double Alpha,double Rho)
{
    Regulator->w0 = (double*) malloc(H *sizeof(double));
    Regulator->y0 = (double*) malloc(H *sizeof(double));
    Regulator->qT = (double*) malloc(H *sizeof(double));
    Regulator->h = (double*) malloc(H *sizeof(double));
    Regulator->wU = (double*) malloc((model->nB + model->k)  *sizeof(double));
    Regulator->wY = (double*) malloc(model->nA *sizeof(double));
    Regulator->h = (double*) malloc(H*sizeof(double));
    Regulator->Q = getMatrixptr(H,L,0.0);
    Regulator->QToInv = getMatrixptr(L,L,0.0);

    Regulator->InvHelper = (double **)malloc(L * sizeof(double*));
    int i;

    for( i = 0; i < L; i++) Regulator->InvHelper[i] = (double *)malloc(L * sizeof(double));

    Regulator->indx = (int *)malloc((unsigned)(L*sizeof(int)));
    Regulator->col = (double *)malloc((unsigned)(L*sizeof(int)));
    Regulator->vv =  (double*)malloc((unsigned)(L*sizeof(double)));

    Regulator->H = H;
    Regulator->L = L;

    Regulator->Alpha =Alpha;
    Regulator->Rho = Rho;
    Regulator->model = model;

}

void GPC_Destructor(GPC* Regulator)
{
    free(Regulator->w0);
    free(Regulator->y0);
    free(Regulator->qT);
    free(Regulator->h);
    free(Regulator->wU);
    free(Regulator->wY);
    freeMatrix(Regulator->Q);
    free(Regulator->col);
    free(Regulator->indx);
    free(Regulator->vv);
    int i;
    for( i = 0; i < Regulator->L; i++) free(Regulator->InvHelper[i]);
    free(Regulator->InvHelper);
}


///
/// \brief CalculateGPC
/// \param model - model
/// \param yk - obecne wyjście
/// \param w - obecne wymuszenie
/// \return
///
double CalculateGPC(GPC* Reg,ARX *model, double*y, double *u, double w)
{

#ifdef SHOW_INFO
    DUMP(y);printTable(y,model->nA);
    DUMP(u);printTable(u,model->nB+model->k);
#endif


    CalcRefModelOutput(Reg,y[model->nA-1],w);

#ifdef SHOW_INFO
    DUMP(Reg->w0);printTable(Reg->w0,Reg->H);
#endif



    CalcClearArx(Reg,model);
#ifdef SHOW_INFO
    DUMP(Reg->h);printTable(Reg->h,Reg->H);
#endif

    FillQ(Reg);
#ifdef SHOW_INFO
    DUMP(Reg->Q);printMatrix(Reg->Q);
#endif


    CalcQT(Reg);
#ifdef SHOW_INFO
    DUMP(Reg->qT);printTable(Reg->qT,Reg->H);
#endif

    CalcArixOutput(Reg,model,y,u);
#ifdef SHOW_INFO
    DUMP(Reg->y0);printTable(Reg->y0,Reg->H);
#endif

    // Calculating u
    double du = 0;
    int i;
    for ( i = 0; i < Reg->H; ++i) {
        du+= Reg->qT[i] * (Reg->w0[i] - Reg->y0[i]);
    }

#ifdef SHOW_INFO
    printf("\n du=%f \n",du);
    printf("\n u=%f \n",du +u[model->nB+model->k-1]);
#endif


    return du +u[model->nB+model->k-1];
}

void CalcQT(GPC* reg)
{
    int i,j,k;

    // CalcMatrixToInv
    for ( i = 0; i < reg->L; ++i) {
        for ( j = 0; j < reg->L; ++j) {
            //Inner product
            reg->QToInv->mat[i][j]=0;
            for (k = 0; k < reg->H; ++k) {
                reg->QToInv->mat[i][j] += reg->Q->mat[k][j] * reg->Q->mat[k][i];
            }
        }
    }

    // Add rho to main diagonal
    for (i = 0; i < reg->L; ++i) {

        reg->QToInv->mat[i][i] += reg->Rho;
    }


#ifdef SHOW_INFO
    DUMP(reg->QToInv);printMatrix(reg->QToInv);
#endif


    inverse(reg->QToInv->mat,reg->InvHelper,reg->col,reg->indx,reg->L,reg->vv);


#ifdef SHOW_INFO
    DUMP(reg->QToInv);printMatrix(reg->QToInv);
#endif

    // Mult QToInv * Q^T = q^T
    for ( k = 0; k < reg->H; ++k) {
        reg->qT[k]=0.0;
        for ( i = 0; i < reg->L; ++i) {
            reg->qT[k]+= reg->QToInv->mat[0][i] * reg->Q->mat[k][i];
        }
    }
}

void FillQ(GPC* reg)
{
    int i,j,k;
    for( j=0;j<reg->L;++j)
    {   k=0;
        for(i=0;i<j;++i)
            reg->Q->mat[i][j]=0;
        for( i=j;i<reg->H;++i,++k)
        {
            reg->Q->mat[i][j]=reg->h[k];
        }
    }
}

/**
 * @brief CalcRefModelOutput
 * Obliczenie H-parametrów modelu odniesienia
 * @param y
 * @param w
 * @param W0
 */
void CalcRefModelOutput(GPC* reg,double y,double w)
{   int i;
    reg->w0[0] = (1.0 - reg->Alpha)*w + reg->Alpha *y;
    for ( i = 1; i < reg->H; ++i) {
        reg->w0[i]=(1.0 - reg->Alpha)*w + reg->Alpha *reg->w0[i-1];
    }
}


/**
 * @brief CalcClearArx
 *
 * Wyliczenie odpowiedzi skokowej z zerowymi warunkami poczatkowymi
 *
 * @param model
 * @param h
 */
void CalcClearArx(GPC* reg,ARX* model)
{
    int j,var=0;
    for (; var < reg->H; ++var) {
        reg->h[var]=0;
        for (j = 0; var-j>0 && j<model->nA; ++j) {
            reg->h[var] -= model->A[j]*reg->h[var-j-1];
        }

        for (j = 0; var - j >=0&& j<model->nB; ++j) {
            reg->h[var] += model->B[j];
        }
    }
}


void CalcArixOutput(GPC* reg,ARX* model,double* y,double* u)
{
    int i,j;
    double ynext;
    double ui=u[model->nB+model->k-1];


    for(j=0;j<model->nA;j++) reg->wY[j]=y[j];
    for(j=0;j<(model->nB +model->k);j++) reg->wU[j]=u[j];

    moveTableLeft(reg->wU,model->nB+model->k);
    reg->wU[model->nB+model->k-1]=ui;

    // There are H elements of y0 to compute
    for (i = 0; i < reg->H; ++i) {
        ynext=0.0;

        for (j = 0; j<model->nA; ++j) {
            ynext -= model->A[j]*reg->wY[model->nA-j-1];
        }

        for (j = 0;j<model->nB; ++j) {
            ynext += model->B[j]*reg->wU[model->nB-j+model->k-1];
        }

        // move numbers left
        moveTableLeft(reg->wY,model->nA);
        reg->wY[model->nA-1]=ynext;

        moveTableLeft(reg->wU,model->nB+model->k);
        reg->wU[model->nB+model->k-1]=ui;
#ifdef SHOW_INFO
        DUMP(reg->wY);printTable(reg->wY,model->nA);
        DUMP(reg->wU);printTable(reg->wU,model->nB +model->k);
#endif
        reg->y0[i]=ynext;
    }


}



double CalcArxOutput(ARX* model,double* y,double* u)
{
    int j;
    double ynext;

    ynext=0.0;

    for (j = 0; j<model->nA; ++j) {
        ynext -= model->A[j]*y[model->nA-j-1];
    }

    for (j = 0;j<model->nB; ++j) {
        ynext += model->B[j]*u[model->nB-j+model->k-1];
    }

    return ynext;
}
