#include "MainLoop_Helper.h"

#include <stdio.h>
#include <csl.h>
#include <csl_mcbsp.h>
#include <csl_edma.h>

#include <stdlib.h>
#include <math.h>

#include "matrixvectorop.h"
#include "lumatrixinv.h"
#include "gpcregler.h"
#include "ident.h"

#include <dsk6713.h>
#include <dsk6713_dip.h>
#include <dsk6713_led.h>

#include "McBSP_Utility.h" 	/*MCBSP configuration and utility data*/
#include "IRQ_Utility.h"  	/*IRQ configuration and utility data*/
//#include "EDMA_Utility.h"   /*EDMA configuration and utility data*/

//#include "ADC8361.h"		/*ADC utility data*/
#include "DAC7716.h"		/*DAC utility data*/
#include "CPLD.h"

extern volatile short int Wzad_pion;
extern volatile short int Wzad_poziom;
///Zmienne glogalne do PID
float kC = 0.03;
float kPID = 0.07;
int pomiar;
//int wartoscZadana=-150;
float suma = 0;

float kC2 = 0.001;
float kPID2 = 0.7;
int pomiar2;
//int wartoscZadana2=1000;
float suma2 = 0;
int use_Gpc = 1;
// Zmienne globalne GPC
ARX modelPoziom;
ARX modelPion;

GPC regulatorPoziom;
GPC regulatorPion;
IdentObj identyfikatorPion;
IdentObj identyfikatorPoziom;
double *poziom;			//obrót w poziomie
double *uPoziom;
double *pion;			//obrót dooko³a kija
double *uPion;

/*Prototypes of internal functions*/
void ML_ShowGoodbyeMsg();

/*-------------------------------------- MAIN LOOP ROUTINES-------------------------------------*/
unsigned short int ML_CheckSwitch() {
	unsigned short int SelectedButtons = 0;
	if (DSK6713_DIP_get(0) == 0) {
		SelectedButtons = SelectedButtons | 0x01;
	}
	if (DSK6713_DIP_get(1) == 0) {
		SelectedButtons = SelectedButtons | 0x02;
	}
	if (DSK6713_DIP_get(2) == 0) {
		SelectedButtons = SelectedButtons | 0x04;
	}
	if (DSK6713_DIP_get(3) == 0) {
		SelectedButtons = SelectedButtons | 0x08;
	}

	return SelectedButtons;
}




Enc_Measurement Enc_WaitForFreshInput(volatile Enc_Measurement* _EncInput,
		volatile short* _ReceiveToGo) {
	Enc_Measurement EncInput_Buffer;
	while (Enc_Are_Both_Enc_Fresh(_EncInput) == FALSE)
		;
	Enc_Unfresh_All(_EncInput);
	Enc_Compute_Values(_EncInput);
	EncInput_Buffer = (*_EncInput);
	//(*_ReceiveToGo) = TRUE;
	return EncInput_Buffer;
}


void PrepareGPC() {
	int k;

	/* Parametry modelu*/
	modelPoziom.nA = 3;
	modelPoziom.nB = 3;
	modelPoziom.k = 1;
	modelPoziom.A = (double*) malloc(modelPoziom.nA * sizeof(double));

	modelPoziom.B = (double*) malloc((modelPoziom.nB + modelPoziom.k) * sizeof(double));

	modelPoziom.A[0] = -2.747;
	modelPoziom.A[1] = 2.514;
	modelPoziom.A[2] = 0.7641;

	modelPoziom.B[0] = 0.001295;
	modelPoziom.B[1] = 0.001799;
	modelPoziom.B[2] = 0.00005318;

	modelPion.nA = 3;
	modelPion.nB = 3;
	modelPion.k = 1;
	modelPion.A = (double*) malloc(modelPion.nA * sizeof(double));
	modelPion.B = (double*) malloc(
			(modelPion.nB + modelPion.k) * sizeof(double));

	modelPion.A[0] = -2.573;
	modelPion.A[1] = 2.353;
	modelPion.A[2] = -0.7641;

	modelPion.B[0] = 0.01329;
	modelPion.B[1] = 0.004851;
	modelPion.B[2] = -0.001411;

	GPC_Constructor(&regulatorPion, &modelPion, 3, 2, 0.3, 0.5);
	GPC_Constructor(&regulatorPoziom, &modelPoziom, 3, 2, 0.3, 0.5);

	pion = (double*) malloc(modelPion.nA * sizeof(double));
	poziom = (double*) malloc(modelPoziom.nA * sizeof(double));

	for (k = 0; k < modelPion.nA; ++k) {
		pion[k] = 0;
	}
	for (k = 0; k < modelPoziom.nA; ++k) {
		poziom[k] = 0;
	}
	double *uPion = (double*) malloc((modelPion.nB + modelPion.k) * sizeof(double));

	double *uPoziom = (double*) malloc((modelPoziom.nB + modelPoziom.k) * sizeof(double));

	//Sprawdzanie, czy nie zabrak³o nam pamiêci
	if(uPoziom == 0){
		DSK6713_LED_on(0);
	}
	for (k = 0; k < modelPion.nB + modelPion.k; ++k) {
		uPion[k] = 0;
	}
	for (k = 0; k < modelPoziom.nB + modelPion.k; ++k) {
		uPoziom[k] = 0;
	}

	//IdentObj Identyfikator;
	IdentObj_Constructor(&identyfikatorPion,&modelPion,0.3,1000);
	IdentObj_Constructor(&identyfikatorPoziom,&modelPoziom,0.3,1000);

}
DAC_Values Enc_PrepareFreshOutput(Enc_Measurement _EncInput,volatile short* _TransmitToGo, float* k) {
	int sterowanie;
	int sterowanie2;
	int uchyb2 ,uchyb;
	if(use_Gpc==1){
		///GPC1 - wirnik powoduj¹cy ruch w pionie
		pomiar = (int) _EncInput.Enc1.Value;

		//	pomiar = -10;
		if (pomiar > 10000) {
			pomiar = pomiar - 65535;
		}
		moveTableLeft(pion,modelPion.nA);
		pion[modelPion.nA-1]=pomiar;
		sterowanie = 0;//CalculateGPC(&regulatorPion,&modelPion,pion,uPion,Wzad_pion);
		moveTableLeft(uPion,modelPion.nB+modelPion.k);


		///GPC2 - wirnik powoduj¹cy ruch w poziomie
		pomiar2 = (int) _EncInput.Enc0.Value;

		if (pomiar2 > 10000) {
			pomiar2 = pomiar2 - 65535;
		}
		moveTableLeft(poziom,modelPoziom.nA);
		poziom[modelPoziom.nA-1] = pomiar2;
		sterowanie2 = CalculateGPC(&regulatorPoziom,&modelPoziom,poziom,uPoziom,250.0);
		moveTableLeft(uPoziom,modelPoziom.nB+modelPoziom.k);
	}else{
		pomiar = (int)_EncInput.Enc1.Value;

		//	pomiar = -10;
		if(pomiar>10000){
			pomiar = pomiar-65535;
		}
		uchyb = pomiar-Wzad_pion;
		suma = suma+uchyb*kC;

		sterowanie = kPID*uchyb+suma;

		///PID2 - wirnik powoduj¹cy ruch w poziomie
		pomiar2 = (int)_EncInput.Enc0.Value;
		//	pomiar = -10;
		if(pomiar2>10000){
			pomiar2 = pomiar2-65535;
		}
		 uchyb2 = pomiar2-Wzad_poziom;
		suma2 = suma2+uchyb2*kC2;

		sterowanie2 = kPID2*uchyb2+suma2;
	}


	if (sterowanie > 0x7FF) {
		sterowanie = 0x7FF;
		suma = suma-uchyb*kC;	//usuñ
	} else if (sterowanie < -0x7FF) {
		sterowanie = -0x7FF;
	}
	if (sterowanie2 > 0x7FF) {
		sterowanie2 = 0x7FF;
	} else if (sterowanie2 < -0x7FF) {
		sterowanie2 = -0x7FF;
		suma2 = suma2-uchyb2*kC2; //usuñ
	}

	uPoziom[modelPoziom.nB+modelPoziom.k]=sterowanie2;
	uPion[modelPion.nB+modelPion.k] = sterowanie;
	CalculateIdent(&identyfikatorPion,sterowanie,pomiar);
	CalculateIdent(&identyfikatorPoziom,sterowanie2,pomiar2);

	//
	DAC_Values FreshOutput = DAC_Fill_Values_With_Zeros();
	// Zerowanie do testów
	//sterowanie2 = 0;
	FreshOutput.Channel_A0 = sterowanie + 0x7FF;
	FreshOutput.Channel_A1 = sterowanie2 + 0x7FF;

	//(*_TransmitToGo) = TRUE;
	//	EDMA_intEnable(EDMA_DAC_IRQ);
	return FreshOutput;
}
void Enc_SendOrder(int order) {
	int *digital_output = (int *) ADDRESS;
	int *ce2 = (int *) CE2;
	*ce2 = 0x22A28A22;
	*digital_output = order;
}

