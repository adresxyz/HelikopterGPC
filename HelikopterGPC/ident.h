#ifndef IDENT
#define IDENT
#include "gpcregler.h"

typedef struct{
ARX* model;
int AB;
double Beta;
double Lambda;
double T;
double Alpha;
double Sigma;

Matrix* P;
Matrix* KFiT;
Matrix* KFiTP;
double*Theta;
double*Phi;
double*VectK;
double*memY;
double*memU;

}IdentObj;



void IdentObj_Constructor(IdentObj* obj,ARX* model,double Beta,double Lambda);
void IdentObj_Destructor(IdentObj* obj);
void CalculateIdent(IdentObj *idobj, double u, double y);

#endif // IDENT

