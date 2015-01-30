#include "matrixvectorop.h"
#include "gpcregler.h"
#include "lumatrixinv.h"
#include "alokacja.h"
#include<stdlib.h>
#include<stdio.h>

//#define SHOW_INFO


void GPC_Constructor(GPC* Regulator,ARX* model,
                     int H,int L,
                     float Alpha,float Rho)
{
    Regulator->w0 = (float*) alokuj(H *sizeof(float));
    Regulator->y0 = (float*) alokuj(H *sizeof(float));
    Regulator->qT = (float*) alokuj(H *sizeof(float));
    Regulator->h = (float*) alokuj(H *sizeof(float));
    Regulator->wU = (float*) alokuj((model->nB + model->k)  *sizeof(float));
    Regulator->wY = (float*) alokuj(model->nA *sizeof(float));
    Regulator->h = (float*) alokuj(H*sizeof(float));
    Regulator->Q = getMatrixptr(H,L,0.0);
    Regulator->QToInv = getMatrixptr(L,L,0.0);

    Regulator->InvHelper = (float **)alokuj(L * sizeof(float*));
    int i;

    for( i = 0; i < L; i++) Regulator->InvHelper[i] = (float *)alokuj(L * sizeof(float));

    Regulator->indx = (int *)alokuj((unsigned)(L*sizeof(int)));
    Regulator->col = (float *)alokuj((unsigned)(L*sizeof(int)));
    Regulator->vv =  (float*)alokuj((unsigned)(L*sizeof(float)));

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
float CalculateGPC(GPC* Reg,ARX *model, float*y, float *u, float w)
{
    CalcRefModelOutput(Reg,y[model->nA-1],w);
    CalcClearArx(Reg,model);
    FillQ(Reg);
    CalcQT(Reg);
    CalcArixOutput(Reg,model,y,u);
    // Calculating u
    float du = 0;
    int i;
    for ( i = 0; i < Reg->H; ++i) {
        du+= Reg->qT[i] * (Reg->w0[i] - Reg->y0[i]);
    }
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




    inverse(reg->QToInv->mat,reg->InvHelper,reg->col,reg->indx,reg->L,reg->vv);


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
void CalcRefModelOutput(GPC* reg,float y,float w)
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


void CalcArixOutput(GPC* reg,ARX* model,float* y,float* u)
{
    int i,j;
    float ynext;
    float ui=u[model->nB+model->k-1];


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

        reg->y0[i]=ynext;
    }


}



float CalcArxOutput(ARX* model,float* y,float* u)
{
    int j;
    float ynext;

    ynext=0.0;

    for (j = 0; j<model->nA; ++j) {
        ynext -= model->A[j]*y[model->nA-j-1];
    }

    for (j = 0;j<model->nB; ++j) {
        ynext += model->B[j]*u[model->nB-j+model->k-1];
    }

    return ynext;
}
