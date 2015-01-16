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
#include "EDMA_Utility.h"   /*EDMA configuration and utility data*/

//#include "ADC8361.h"		/*ADC utility data*/
#include "DAC7716.h"		/*DAC utility data*/
#include "CPLD.h"

extern volatile short int Wzad_pion;
extern volatile short int Wzad_poziom;
///Zmienne glogalne do PID
float kC = 0.05;
float kPID = 0.1;
int pomiar;
//int wartoscZadana=-150;
float suma = 0;

float kC2 = 0.001;
float kPID2 = 1;
int pomiar2;
//int wartoscZadana2=1000;
float suma2 = 0;

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

void ML_ExitProcedure(EDMA_Handle* _hEDMA_ADC, int _ADC_IRQ,
		EDMA_Handle* _hEDMA_ADC_Ping, EDMA_Handle* _hEDMA_ADC_Pong,
		EDMA_Handle* _hEDMA_Dac, int _DAC_IRQ, EDMA_Handle* _hEDMA_DAC_Ping,
		EDMA_Handle* _hEDMA_DAC_Pong, MCBSP_Handle _hMCBSP_ADC,
		MCBSP_Handle _hMCBSP_DAC, int _ShowMsg) {
	stopEdma(_hEDMA_ADC, _ADC_IRQ, _hEDMA_ADC_Ping, _hEDMA_ADC_Pong);
	stopEdma(_hEDMA_Dac, _DAC_IRQ, _hEDMA_DAC_Ping, _hEDMA_DAC_Pong);
	MCBSP_close(_hMCBSP_ADC);
	MCBSP_close(_hMCBSP_DAC);

	if (_ShowMsg) {
		ML_ShowGoodbyeMsg();
	}
}

void ML_ShowGoodbyeMsg() {
	printf("Program was properly terminated!\n");
	printf("Goodbye!\n");
}

//ADC_Measurement ML_WaitForFreshInput(volatile ADC_Measurement* _ADCInput,
//		volatile short* _ReceiveToGo) {
//	ADC_Measurement ADCInput_Buffor;
//	//while(ADC_Are_All_Channels_Fresh(*_ADCInput) == FALSE);
//	ADC_Unfresh(_ADCInput);
//	ADCInput_Buffor = (*_ADCInput);
//	(*_ReceiveToGo) = TRUE;
//	EDMA_intEnable(EDMA_ADC_IRQ);
//	return ADCInput_Buffor;
//}
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

//DAC_Values ML_PrepareFreshOutput(ADC_Measurement _ADCInput,
//		volatile short* _TransmitToGo) {
//	static int i = 0;
//
//	DAC_Values FreshOutput = DAC_Fill_Values_With_Zeros();
//	i++;
//	if (i * 8 > 0xfff) {
//		i = 0;
//	}
//
//	FreshOutput.Channel_A0 = 0xfff;
//	FreshOutput.Channel_A1 = 0xeff;
//	FreshOutput.Channel_A2 = i * 4;
//	FreshOutput.Channel_A3 = i * 8;
//
//	(*_TransmitToGo) = TRUE;
//	EDMA_intEnable(EDMA_DAC_IRQ);
//	return FreshOutput;
//}
void PrepareGPC() {
	int k;

	/* Parametry modelu*/
	modelPoziom.nA = 1;
	modelPoziom.nB = 2;
	modelPoziom.k = 1;
	modelPoziom.A = (double*) malloc(modelPoziom.nA * sizeof(double));
	if(modelPoziom.A ==0){
		DSK6713_LED_on(0);
	}
	modelPoziom.B = (double*) malloc((modelPoziom.nB + modelPoziom.k) * sizeof(double));
	if(modelPoziom.B ==0){
		DSK6713_LED_on(0);
	}
	modelPoziom.A[0] = -0.8;
	modelPoziom.B[0] = 0.6;
	modelPoziom.B[1] = 0.4;

	modelPion.nA = 1;
	modelPion.nB = 2;
	modelPion.k = 1;
	modelPion.A = (double*) malloc(modelPion.nA * sizeof(double));
	modelPion.B = (double*) malloc(
			(modelPion.nB + modelPion.k) * sizeof(double));

	modelPion.A[0] = -0.8;
	modelPion.B[0] = 0.6;
	modelPion.B[1] = 0.4;

	GPC_Constructor(&regulatorPion, &modelPion, 3, 2, 0.2, 0.3);
	GPC_Constructor(&regulatorPoziom, &modelPoziom, 3, 2, 0.2, 0.3);

	pion = (double*) malloc(modelPion.nA * sizeof(double));
	poziom = (double*) malloc(modelPoziom.nA * sizeof(double));

	for (k = 0; k < modelPion.nA; ++k) {
		pion[k] = 0;
	}
	for (k = 0; k < modelPoziom.nA; ++k) {
		poziom[k] = 0;
	}
	double *uPion = (double*) malloc((modelPion.nB + modelPion.k) * sizeof(double));
	if(uPion==0){
		DSK6713_LED_on(0);
	}
	double *uPoziom = (double*) malloc((modelPoziom.nB + modelPoziom.k) * sizeof(double));
	if(uPoziom==0){
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

	///PID w pionie - wirnik powoduj¹cy ruch
	pomiar = (int) _EncInput.Enc1.Value;
	int sterowanie;
	//	pomiar = -10;
	if (pomiar > 10000) {
		pomiar = pomiar - 65535;
	}
	moveTableLeft(pion,modelPion.nA);
	pion[modelPion.nA-1]=pomiar;
	sterowanie = CalculateGPC(&regulatorPion,&modelPion,pion,uPion,Wzad_pion);
	moveTableLeft(uPion,modelPion.nB+modelPion.k);
	uPion[modelPion.nB+modelPion.k] = pomiar;
	CalculateIdent(&identyfikatorPion,sterowanie,pomiar);


	///PID2 - wirnik powoduj¹cy ruch w poziomie
	pomiar2 = (int) _EncInput.Enc0.Value;
	int sterowanie2;
	if (pomiar2 > 10000) {
		pomiar2 = pomiar2 - 65535;
	}
	moveTableLeft(poziom,modelPoziom.nA);
	pion[modelPoziom.nA-1] = pomiar2;
	sterowanie2 = CalculateGPC(&regulatorPoziom,&modelPoziom,poziom,uPoziom,Wzad_poziom);
	moveTableLeft(uPoziom,modelPoziom.nB+modelPoziom.k);
	uPoziom[modelPoziom.nB+modelPoziom.k]=pomiar2;
	CalculateIdent(&identyfikatorPoziom,sterowanie2,pomiar2);



	if (sterowanie > 0x7FF) {
		sterowanie = 0x7FF;
	} else if (sterowanie < -0x7FF) {
		sterowanie = -0x7FF;
	}
	if (sterowanie2 > 0x7FF) {
		sterowanie2 = 0x7FF;
	} else if (sterowanie2 < -0x7FF) {
		sterowanie2 = -0x7FF;
	}

	//
	DAC_Values FreshOutput = DAC_Fill_Values_With_Zeros();
	// Zerowanie do testów
	//sterowanie2 = 0;
	FreshOutput.Channel_A0 = sterowanie + 0x7FF;
	FreshOutput.Channel_A1 = sterowanie2 + 0x7FF;

	(*_TransmitToGo) = TRUE;
//	EDMA_intEnable(EDMA_DAC_IRQ);
	return FreshOutput;
}
void Enc_SendOrder(int order) {
	int *digital_output = (int *) ADDRESS;
	int *ce2 = (int *) CE2;
	*ce2 = 0x22A28A22;
	*digital_output = order;
}

