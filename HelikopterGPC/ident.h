#ifndef IDENT
#define IDENT
#include "gpcregler.h"

typedef struct{
ARX* model;
int AB;
float Beta;
float Lambda;
float T;
float Alpha;
float Sigma;

Matrix* P;
Matrix* KFiT;
Matrix* KFiTP;
float*Theta;
float*Phi;
float*VectK;
float*memY;
float*memU;
float lastU;
float lastY;

}IdentObj;



void IdentObj_Constructor(IdentObj* obj,ARX* model,float Beta,float Lambda);
void IdentObj_Destructor(IdentObj* obj);
void CalculateIdent(IdentObj *idobj, float u, float y,float w);

#endif // IDENT

