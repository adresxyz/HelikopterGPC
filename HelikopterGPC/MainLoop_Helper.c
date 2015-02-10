#include "MainLoop_Helper.h"

#include <stdio.h>
#include <csl.h>
#include <csl_mcbsp.h>
#include <csl_edma.h>

#include <stdlib.h>
#include <math.h>

#include "alokacja.h"
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

float kC2 = 0.003;
float kPID2 = 0.7;
int pomiar2;

//float kC2 = 0.004;
//float kPID2 = 0.8;
//int pomiar2;


//int wartoscZadana2=1000;
float suma2 = 0;
int use_GpcPion = 0;
int use_GpcPoziom = 0;


// Zmienne globalne GPC
ARX modelPoziom;
ARX modelPion;


GPC regulatorPoziom;
GPC regulatorPion;

IdentObj identyfikatorPion;
IdentObj identyfikatorPoziom;

float *poziom;			//obrót w poziomie
float *uPoziom;
float *pion;			//obrót dooko³a kija
float *uPion;

float Apion_init[15] = { -0.967103, -0.345464, 0.016679, 0.101649, 0.089887, 0.285890,
							-0.025965, 0.042773, -0.055164, -0.076209,0.0,0.0,0.0,0.0,0.0};
float Bpion_init[15] = { 0.000115, 0.000051, -0.000883, -0.001712, -0.001780, -0.001665,
							-0.001342, -0.000718, -0.000269, -0.000300,0.0,0.0,0.0,0.0,0.0};

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
	while (Enc_Are_Both_Enc_Fresh(_EncInput) == FALSE);
	Enc_Unfresh_All(_EncInput);
	Enc_Compute_Values(_EncInput);
	EncInput_Buffer = (*_EncInput);
	//(*_ReceiveToGo) = TRUE;
	return EncInput_Buffer;
}


void PrepareGPC() {
	int k,i;

	/* Parametry modelu*/
	modelPoziom.nA = 10;
	modelPoziom.nB = 10;
	modelPoziom.k = 1;
	modelPoziom.A = (float*) alokuj(modelPoziom.nA * sizeof(float));

	modelPoziom.B = (float*) alokuj((modelPoziom.nB + modelPoziom.k) * sizeof(float));

	for(i = 0; i<modelPoziom.nA;i++){
		modelPoziom.A[i]=0;
	}
	for(i = 0; i<modelPoziom.nB;i++){
		modelPoziom.B[i]=0;
	}


	modelPoziom.A[0] = -2.747;
	modelPoziom.A[1] = 2.514;
	modelPoziom.A[2] = 0.7641;

	modelPoziom.B[0] = 0.001295;
	modelPoziom.B[1] = 0.001799;
	modelPoziom.B[2] = 0.00005318;

	modelPion.nA = 15;
	modelPion.nB = 15;
	modelPion.k = 1;
	modelPion.A = (float*) alokuj(modelPion.nA * sizeof(float));
	modelPion.B = (float*) alokuj((modelPion.nB + modelPion.k) * sizeof(float));

	for(i = 0; i<modelPion.nA;i++){
		modelPion.A[i]=Apion_init[i];
	}
	for(i = 0; i<modelPion.nB;i++){
		modelPion.B[i]=Bpion_init[i];
	}
//	for(i = 0; i<modelPion.nA;i++){
//			modelPion.A[i]=0;
//	}
//	for(i = 0; i<modelPion.nB;i++){
//			modelPion.B[i]=0;
//	}



	GPC_Constructor(&regulatorPion, &modelPion, 120, 50, 0.0, 0.05);
	regulatorPion.ValMax=2047.0;
	regulatorPion.ValMin=-2047.0;

//	GPC_Constructor(&regulatorPoziom, &modelPoziom, 100, 50, 0, 0.5);
//	regulatorPoziom.ValMax=2000.0;
//	regulatorPoziom.ValMin=-2000.0;

	pion = (float*) alokuj(modelPion.nA * sizeof(float));
	poziom = (float*) alokuj(modelPoziom.nA * sizeof(float));

	for (k = 0; k < modelPion.nA; ++k) {
		pion[k] = 0;
	}
	for (k = 0; k < modelPoziom.nA; ++k) {
		poziom[k] = 0;
	}
	uPion = (float*) alokuj((modelPion.nB + modelPion.k) * sizeof(float));

	uPoziom = (float*) alokuj((modelPoziom.nB + modelPoziom.k) * sizeof(float));


	for (k = 0; k < modelPion.nB + modelPion.k; ++k) {
		uPion[k] = 0;
	}
	for (k = 0; k < modelPoziom.nB + modelPion.k; ++k) {
		uPoziom[k] = 0;
	}

	//IdentObj Identyfikator;
	IdentObj_Constructor(&identyfikatorPion,&modelPion,0.5,1000);
	//IdentObj_Constructor(&identyfikatorPoziom,&modelPoziom,0.3,1000);

}
DAC_Values Enc_PrepareFreshOutput(Enc_Measurement _EncInput,volatile short* _TransmitToGo, float* k) {
	int sterowanie;
	int sterowanie2;
	static int iteracja = 0;
	static int czyIdentyfikowac = 0;
	int uchyb2 ,uchyb,rozniczka;


	//OpóŸnione w³¹czanie identyfikacji i GPC
	iteracja = iteracja+1;
	if(iteracja == 1){
		czyIdentyfikowac = 1;
	}
//	if(iteracja==1500){
//		//Wzad_pion = 100+ (( (float)rand() )/ (float)RAND_MAX)*40 - 20;
//		use_GpcPoziom=1;
//		regulatorPoziom.y=poziom;
//		regulatorPoziom.u=uPoziom;
//	}

	if(iteracja==1){
		//Wzad_pion = 100+ (( (float)rand() )/ (float)RAND_MAX)*40 - 20;
		use_GpcPion=1;
		regulatorPion.y=pion;
		regulatorPion.u=uPion;
	}
//////////////  Regulator przechy³u /////////////////////
	//Pomiary przechy³u
	pomiar = (int)_EncInput.Enc1.Value;
	if(pomiar>10000){
		pomiar = pomiar-65535;
	}
	//£adowanie historii
	moveTableLeft(pion,modelPion.nA);
	pion[modelPion.nA-1]=pomiar;
	//Wybór regulatora
	if(use_GpcPion==1){
		DSK6713_LED_on(1);
		sterowanie = CalculateGPC(&regulatorPion,pomiar,Wzad_pion);
	}else{
		uchyb = pomiar-Wzad_pion;
		suma = suma+uchyb*kC;
		sterowanie = kPID*uchyb+suma;
	}
	moveTableLeft(uPion,modelPion.nB+modelPion.k);

//////////////  Regulator obrotu /////////////////////
	//Pomiar obrotu
	pomiar2 = (int) _EncInput.Enc0.Value;
	if (pomiar2 > 10000) {
		pomiar2 = pomiar2 - 65535;
	}
	moveTableLeft(poziom,modelPoziom.nA);
	poziom[modelPoziom.nA-1] = pomiar2;
	//Wybór regulatora
	if(use_GpcPoziom==1){
		///GPC2 - wirnik powoduj¹cy ruch w poziomie
		DSK6713_LED_on(1);
		sterowanie2  = CalculateGPC(&regulatorPoziom,pomiar2,Wzad_poziom);
	}else{
		///PID2 - wirnik powoduj¹cy ruch w poziomie
		uchyb2 = pomiar2-Wzad_poziom;
		suma2 = suma2+uchyb2*kC2;
		sterowanie2 = kPID2*uchyb2+suma2;
	}
	moveTableLeft(uPoziom,modelPoziom.nB+modelPoziom.k);

	//Ograniczenie sterowania - antywindup
	if (sterowanie > 0x7FF) {
		sterowanie = 0x7FF;
		suma = suma-uchyb*kC;	//TODO usuñ
	} else if (sterowanie < -0x7FF) {
		sterowanie = -0x7FF;
		suma = suma-uchyb*kC;	//TODO usuñ
	}
	if (sterowanie2 > 0x7FF) {
		sterowanie2 = 0x7FF;
		suma2 = suma2-uchyb2*kC2; //TODO usuñ
	} else if (sterowanie2 < -0x7FF) {
		sterowanie2 = -0x7FF;
		suma2 = suma2-uchyb2*kC2; //TODO usuñ
	}

	//uPoziom[modelPoziom.nB+modelPoziom.k]=sterowanie2;
	//if(iteracja )
	uPion[modelPion.nB+modelPion.k-1] = sterowanie;

	if(czyIdentyfikowac == 1){
		CalculateIdent(&identyfikatorPion,sterowanie,pomiar,Wzad_pion);
//		CalculateIdent(&identyfikatorPoziom,sterowanie2,pomiar2);
	}
	//

	DAC_Values FreshOutput = DAC_Fill_Values_With_Zeros();

	FreshOutput.Channel_A0 = sterowanie + 0x7FF;
	FreshOutput.Channel_A1 = sterowanie2 + 0x7FF;


	return FreshOutput;
}
void Enc_SendOrder(int order) {
	int *digital_output = (int *) ADDRESS;
	int *ce2 = (int *) CE2;
	*ce2 = 0x22A28A22;
	*digital_output = order;
}

