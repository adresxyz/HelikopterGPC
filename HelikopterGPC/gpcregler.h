#ifndef GPCREGLER
#define GPCREGLER
#include <stdio.h>
#define DUMP(varname) printf("%s = \n", #varname);
#include "matrixvectorop.h"


typedef struct{
int L;
int H;
double Rho;
double Alpha;
double *w0;
double *y0;
double *qT;
double *h;
double *wU;
double *wY;
Matrix* Q;
Matrix* QToInv;
double** InvHelper;
int *indx;
double *col;
double *vv;
ARX* model;

}GPC;

void GPC_Constructor(GPC* Regulator,ARX* model,
                     int H,int L,
                     double Alpha,double Rho);
void GPC_Destructor(GPC* Regulator);


void CalcRefModelOutput(GPC* reg, double y, double w);


void CalcClearArx(GPC* reg,ARX* model);


void FillQ(GPC* reg);


void CalcQT(GPC* reg);


void CalcArixOutput(GPC* reg,ARX* model,double* y,double* u);

double CalculateGPC(GPC* Reg, ARX *model, double*y, double *u, double w);

double CalcArxOutput(ARX* model,double* y,double* u);
void pushStop(double New,double* A,int size);
void pushStart(double New,double* A,int size);
#endif // GPCREGLER

