#ifndef GPCREGLER
#define GPCREGLER
#include <stdio.h>
#include "matrixvectorop.h"


typedef struct{
int L;
int H;
float Rho;
float Alpha;
float ValMax;
float ValMin;
float *w0;
float *y0;
float *qT;
float *h;
float *wU;
float *wY;
float *y;
float *u;
Matrix* Q;
Matrix* QToInv;
float** InvHelper;
int *indx;
float *col;
float *vv;
ARX* model;

}GPC;

void GPC_Constructor(GPC* Regulator,ARX* model,
                     int H,int L,
                     float Alpha,float Rho);
void GPC_Destructor(GPC* Regulator);


void CalcRefModelOutput(GPC* reg, float y, float w);


void CalcClearArx(GPC* reg,ARX* model);


void FillQ(GPC* reg);


void CalcQT(GPC* reg);


void CalcArixOutput(GPC* reg,ARX* model,float* y,float* u);

float CalculateGPC(GPC* Reg, float CurrY, float w);

float CalcArxOutput(ARX* model,float* y,float* u);
void pushStop(float New,float* A,int size);
void pushStart(float New,float* A,int size);
#endif // GPCREGLER

