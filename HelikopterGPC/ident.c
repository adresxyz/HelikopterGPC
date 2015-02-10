
#include "ident.h"
#include "matrixvectorop.h"
#include <math.h>
#include <stdlib.h>
#include "alokacja.h"





void IdentObj_Constructor(IdentObj* obj,ARX* model,float Beta,float Lambda)
{
    obj->model = model;
    obj->Beta = Beta;
    obj->Lambda = Lambda;
    obj->T = 1000.0;
    obj->Alpha = 0;
    obj->Sigma =1000;
    obj->AB = model->nA + model->nB;
    obj->Theta = (float*) alokuj((model->nA+model->nB)*sizeof(float));
    obj->Phi = (float*) alokuj((model->nA+model->nB)*sizeof(float));
    obj->VectK= (float*) alokuj((model->nA+model->nB)*sizeof(float));
    obj->memY= (float*) alokuj((model->nA+model->nB+1)*sizeof(float));
    obj->memU= (float*) alokuj((model->nA+model->nB+1)*sizeof(float));
    obj->P = getMatrixEyeptr(model->nA+model->nB,model->nA+model->nB,Lambda);
    obj->KFiT = getMatrixptr(model->nA + model->nB,model->nA + model->nB,0.0);
    obj->KFiTP = getMatrixptr(model->nA + model->nB,model->nA + model->nB,0.0);


    int i;
    for ( i = 0; i < model->nA+model->nB; ++i) {
        obj->Theta[i]=obj->Phi[i] = obj->VectK[i]=0.0;
    }

    for ( i = 0; i < model->nA+model->nB+1; ++i) {
        obj->memY[i]=obj->memU[i] =0.0;
    }

    obj->lastU=obj->lastY=0;

}

void IdentObj_Destructor(IdentObj *obj)
{
    //    obj->Theta = (float*) alokuj((model->nA+model->nB)*sizeof(float));
    //    obj->Phi = (float*) alokuj((model->nA+model->nB)*sizeof(float));
    //    obj->VectK= (float*) alokuj((model->nA+model->nB)*sizeof(float));
    //    obj->memY= (float*) alokuj((model->nA+model->nB)*sizeof(float));
    //    obj->memU= (float*) alokuj((model->nA+model->nB)*sizeof(float));
    //    obj->P = getMatrixEyeptr(model->nA+model->nB,model->nA+model->nB,Lambda);
    //    obj->KFiT = getMatrixptr(model->nA + model->nB,model->nA + model->nB,0.0);
    //    obj->KFiTP = getMatrixptr(model->nA + model->nB,model->nA + model->nB,0.0);


    free(obj->Theta);
    free(obj->Phi);
    free(obj->Phi);
    free(obj->VectK);
    free(obj->memY);
    free(obj->memU);
    freeMatrix(obj->P);
}

void CalculateIdent(IdentObj *idobj,float u,float y,float w)
{
    int i,j,k;

//    float u = Nu-idobj->lastU;
//    float y = Ny;//-idobj->lastY;
//
//    idobj->lastU=Nu;
//    idobj->lastY=Ny;

    pushStart(u,idobj->memU,idobj->AB);

    pushStart(-y,idobj->memY,idobj->AB);

    for (k = 0; k < idobj->model->nB; ++k) {
        idobj->Phi[k] = idobj->memU[k+idobj->model->k];
    }

    float Epsilon = y;
    for (i = 0; i < idobj->AB; ++i) {
        Epsilon-= idobj->Theta[i] * idobj->Phi[i];
    }




    idobj->Sigma = 1000 * sqrt(idobj->Beta*(idobj->Sigma*idobj->Sigma)/(1000000.0) +
                               (1-idobj->Beta) * Epsilon *Epsilon);


    /* Mult. of Phi^T * P * Phi*/

    float temp = 1.0;
    for ( i = 0; i < idobj->AB; ++i) {
        float Accum =0.0;
        for ( j = 0; j < idobj->AB; ++j) {
            Accum+= idobj->Phi[j] * idobj->P->mat[i][j];
        }
        temp+=Accum * idobj->Phi[i];
    }
//    idobj->Alpha= 1 - (Epsilon * Epsilon)/(temp * idobj->Sigma);
    //idobj->Alpha = 0.97;
    //idobj->Alpha= 0.95;

    if( abs(w-y)>20)
        idobj->Alpha = 0.95;
    else
    	 idobj->Alpha= 1 - (Epsilon * Epsilon)/(temp * idobj->Sigma);

    /* Computing k:VectK */
    for ( i = 0; i < idobj->AB; ++i) {
        idobj->VectK[i] =0.0;
        for ( j = 0; j < idobj->AB; ++j) {
            idobj->VectK[i] += idobj->Phi[j] * idobj->P->mat[i][j];
        }
        idobj->VectK[i]/=temp;
    }



    /* Computing P */


    for ( i = 0; i < idobj->AB; ++i) {
        for ( j = 0; j < idobj->AB; ++j) {
            idobj->KFiT->mat[i][j] = idobj->VectK[i] * idobj->Phi[j];
        }
    }

    MatrixMultptr(idobj->KFiT,idobj->P,idobj->KFiTP);



    for ( i = 0; i < idobj->AB; ++i) {
        for ( j = 0; j < idobj->AB; ++j) {
            idobj->P->mat[i][j] -= idobj->KFiTP->mat[i][j];
        }
    }


    float Trace =0;
    for (k = 0; k < idobj->AB; ++k) {
        Trace += idobj->P->mat[k][k];
    }

    if(Trace/idobj->Alpha < idobj->T)
    {
        for ( i = 0; i < idobj->AB; ++i) {
            for ( j = 0; j < idobj->AB; ++j) {
                idobj->P->mat[i][j] /= idobj->Alpha;
            }
        }
    }

    /* Theta */

    // Theta = Theta + k * epsilon;
    for ( j = 0; j < idobj->AB; ++j) {
        idobj->Theta[j] += idobj->VectK[j]*Epsilon;
    }

    for (k = 0; k < idobj->model->nA; ++k) {
        idobj->Phi[k+idobj->model->nB] =  idobj->memY[k];
    }

	ARX* model = idobj->model;
    for (i = 0; i < model->nB; ++i) {
        model->B[i]=idobj->Theta[i];
    }
    for(i= 0;i<model->nA;++i)
    {
    model->A[i]=idobj->Theta[i+model->nB];
    }

}
