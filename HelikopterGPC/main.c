#include <stdio.h>

#include <csl.h>
#include <csl_mcbsp.h>
#include <csl_irq.h>
#include <csl_cache.h>
#include <csl_edma.h>
#include <csl_i2c.h>


#include "dsk6713_led.h"
#include <csl_emif.h>

#include <dsk6713.h>
#include <dsk6713_dip.h>

#include "McBSP_Utility.h" 	/*MCBSP configuration and utility data*/
#include "IRQ_Utility.h"  	/*IRQ configuration and utility data*/
#include "EDMA_Utility.h"   /*EDMA configuration and utility data*/
#include "I2C_Utility.h"    /*I2C configuration and utility data*/
#include "Command_Utility.h"


//#include <DSPF_dp_mat_mul.h>

#include "ADC8361.h"		/*ADC utility data*/
#include "DAC7716.h"		/*DAC utility data*/
#include "CPLD.h"
#include "timer.h"
#include "enkoder.h"
#include "MainLoop_Helper.h" /*Functions used in main loop of the program*/


volatile int ADCCounter = 0;

void Initialize(void);
void Intialize_Chipset(void);
//void Initialize_I2C(void);
volatile Enc_Measurement EncMeasurement;
volatile Enc_Measurement* pEncMeasurement = &EncMeasurement;
volatile int fstart = 1;
int *digital_output=(int *)ADDRESS;
int *ce2 = (int *)CE2;

float WzmocnienieRegulatoraP = 1;
float WzmocnienieCalki = 1;
double wynik[3][3];

volatile short int Wzad_pion = -150;
volatile short int Wzad_poziom = 150;
volatile short int Parametry1[3];
volatile short int Parametry2[3];
/*----------------------------------------------------------------------------*/

void TimerEventHandler(int);


/*----------------------------------------------------------------------------*/

/* --------------------------MAIN----------------------------------*/
void main() {

	Enc_Measurement EncMeasurement_Buffer;
//	int i;
//	int bezcelowaTablica[10000];
//
//	for(i=1;i<10000;i++){
//		bezcelowaTablica[i]=1;
//	}
	Intialize_Chipset();


	//Pozosta³a inicjalizacja - patrz ni¿ej
	Initialize();

	//first polling transfer to initiate EDMA events chain
	Polling_Transmit(hMcBSP_DAC,DAC_Prepare_Frame(DAC_WRITE,DAC_AC0,0x0ff));
	DSK6713_LED_off(0);
	PrepareGPC();

	while(1)
	{

		EncMeasurement_Buffer = Enc_WaitForFreshInput(pEncMeasurement,&Enc_ReceiveToGo);

		DACValues = Enc_PrepareFreshOutput(EncMeasurement_Buffer, &DAC_TransmitToGo,&WzmocnienieRegulatoraP);

		Polling_Transmit(hMcBSP_DAC,DAC_Prepare_Frame(DAC_WRITE, DAC_AC0, DACValues.Channel_A0));
		Polling_Transmit(hMcBSP_DAC,DAC_Prepare_Frame(DAC_WRITE, DAC_AC3, DACValues.Channel_A1));

		DSK6713_LED_toggle(2);
	}
}

/*-----------------INTERRUPTS ROUTINES-----------------*/
interrupt void
c_int08(void)   //EDMA Interrupts
{

	EDMA_intDisable(EDMA_DAC_IRQ);

	if (EDMA_intTest(EDMA_DAC_IRQ) && DAC_TransmitToGo)/*Transmitter data transfer is completed*/
	{
		//printf("Przerwanie DAC\n");
		/* Clear the pending interrupt from the EDMA interrupt pending register */
		EDMA_intClear(EDMA_DAC_IRQ);

		/* Perform ping-pong for receiver */
		DAC_PingPong = (DAC_PingPong + 1) & 1;

		/*Save input to adequate buffer*/
		DAC_Prepare_EDMA(DAC_PingPong, DAC_Channel_To_Send, &DAC_Ping, &DAC_Pong, DACValues);

		if(DAC_PingPong)
		{
			EDMA_link(hEdmaDAC,hEdmaDACPing);
			//PrintfDACTransferInfo( DAC_Channel_To_Send, DAC_PingPong,DAC_Ping);
		}
		else
		{
			EDMA_link(hEdmaDAC,hEdmaDACPong);
			//PrintfDACTransferInfo( DAC_Channel_To_Send, DAC_PingPong,DAC_Pong);
		}

		DAC_Update_Channel_To_Send(&DAC_Channel_To_Send);

		/*we need to perform sending data to all 4 channels before we can disable EDMA*/
		if(DAC_Channel_To_Send == 0)
		{
			DAC_TransmitToGo = FALSE;

			EDMA_intDisable(EDMA_DAC_IRQ);
			return;
		}


		EDMA_intEnable(EDMA_DAC_IRQ);
	}

	return;
}
interrupt void //I2C Interrupts
c_int09(void)
{
	IRQ_disable(IRQ_EVT_I2CINT0);
	//printf("I2C interrupt\n");
	Uint32 val=0;
	static Uint8 WordToSend = 0;
	static Uint8 WordsToSend = 0;
	static Uint8 DataToSend[50];

	static int WordToReceive = -1; //to enable easy incrementing in the loop, when the first byte is a command and not a data
	static Uint8 WordsToReceive = 0;
	static Uint8 DataReceived[50];

	static Commands ReceivedCommand;

	val = I2C_intClear(hI2C0);


	Uint8 ValueToSend = DataToSend[WordToSend];
	DAC_Values DACValuesCopy= DACValues;
	Uint8 ReceivedData;

	if(I2C_InterruptsRoutine(val, &ReceivedData, ValueToSend, hI2C0))
	{
		if(WordsToReceive == 0) //we are waiting for new command
		{

			ReceivedCommand = AnalyzeCommands(ReceivedData);
			CommandEngine(ReceivedCommand,DataToSend,&WordsToSend,&WordsToReceive,DACValuesCopy);

			//now it is very important to swift old value remaining in I2CDXR register
			//with new one before the ask for write from XMEGA will occur
			//6 hours wasted to figure it out!
			if(WordsToReceive == 0)
			{
				WordToSend = 0;
				I2C_writeByte(hI2C0,DataToSend[0]);
				WordToSend++;
			}
		}
		else
		{
			DataReceived[WordToReceive] = ReceivedData;
		}

		if(WordsToReceive != 0) //there is some data to receive
		{
			WordToReceive++;
			if(WordToReceive == WordsToReceive) //when all data is collected
			{
				//printf("All data!\n");
				WordToReceive = -1;
				WordsToReceive = 0;
				ProcessReceivedData(ReceivedCommand,DataReceived, pEncMeasurement);
			}
		}

	}
	else if(WordsToReceive == 0)
	{
		WordToSend++;
		if(WordToSend == WordsToSend)
		{
			WordToSend = 0;
		}
	}

	IRQ_enable(IRQ_EVT_I2CINT0);

}
///************************************************************************\
// name:      TimerEventHandler
//\************************************************************************/
void TimerEventHandler(int _cnt) {
	/* process timer event here */
	/*switch (_cnt){
	case 0:Enc_SendOrder(ACTIVATE);printf("Aktywacja: %#010x\n", *digital_output);break;
	case 1:Enc_SendOrder(R_HIGH);printf("Rozkaz H: %#010x\n", *digital_output);break;
	case 2:Enc_ReadHigh(pEncMeasurement);printf("Odczyt H: %#010x\n", *digital_output);break;
	case 3:Enc_SendOrder(R_LOW);printf("Rozkaz L: %#010x\n", *digital_output);break;
	case 4:Enc_ReadLow(pEncMeasurement);printf("Odczyt L: %#010x\n", *digital_output);Enc_ReceiveToGo = FALSE;Enc_Compute_Values(pEncMeasurement);break;
	}*/


	DSK6713_LED_toggle(3);
}

///************************************************************************\
// name:      Interrupt Service Routine c_int14
//\************************************************************************/
interrupt void
c_int14(void)
{
	static int cnt = 0;


	TimerEventHandler(cnt);
	if (cnt++ == 5)
	{
		cnt = 0;
	}

	return;
} /* end c_int14 */

/*-----------------INITIALIZATION ROUTINES-----------------*/

void Intialize_Chipset(void)
{
	/* Initialize the chip support library */
	CSL_init();
	DSK6713_init();
	DSK6713_DIP_init();

	//Activating McBSP1
	CPLD_WriteMisc(3);
}

void Initialize(void)
{


	/*I2C configuration */
	I2C_Config I2C0_Config = I2C_PrepareSlaveConfigStruct();
	hI2C0 = I2C_open(I2C_DEV0,I2C_OPEN_RESET);


	//Wype³nienie struktury przechowuj¹cej pomiary z ADC zerami - DO WYRZUCENIA
	ADCMeasurement = ADC_Fill_Measurement_With_Zeros();

	//Wype³nienie struktury przechowuj¹cej wartosci dla DAC zerami
	DACValues = DAC_Fill_Values_With_Zeros();

	/*Setting up interrupts*/
	setupIRQ();



	/* Let's open up and configure serial ports */
	//Otwieramy port szeregowy dla DAC - przypisujemy go do statycznego handlera
	hMcBSP_DAC = MCBSP_open(MCBSP_DEV1, MCBSP_OPEN_RESET);

	//Konfiguracja portów, @param handler, wskaŸnik do funkcji z konfiguracj¹
	MCBSP_config(hMcBSP_DAC,&McBSP_DAC_Confing);

	/*Configure and start I2C*/
	I2C_config(hI2C0,&I2C0_Config);

	// Enhanced Direct Memory Access
	/*EMDA opening*/
	EDMA_clearPram(0x00000000);

	hEdmaDAC = EDMA_open(EDMA_CHA_XEVT1, EDMA_OPEN_RESET);
	hEdmaDACPing = EDMA_allocTable(-1);
	hEdmaDACPong = EDMA_allocTable(-1);


	/* EDMA Configuration*/
	EDMA_configArgs(hEdmaDACPing,EDMADACConfOpt(),(Uint32)&DAC_Ping,1,MCBSP_getXmtAddr(hMcBSP_DAC),EDMA_IDX_OF(0),EDMA_RLD_RMK(0,hEdmaDACPing));
	EDMA_configArgs(hEdmaDACPong,EDMADACConfOpt(),(Uint32)&DAC_Pong,1,MCBSP_getXmtAddr(hMcBSP_DAC),EDMA_IDX_OF(0),EDMA_RLD_RMK(0,hEdmaDACPong));
	EDMA_configArgs(hEdmaDAC,EDMADACConfOpt(),(Uint32)&DAC_Pong,1,MCBSP_getXmtAddr(hMcBSP_DAC),EDMA_IDX_OF(0),EDMA_RLD_RMK(0,hEdmaDACPong));

	/*Setting up interrupts*/
	enableIRQ();
	enableIRQ_EDMA();

	/* Enable the EDMA channels */

	EDMA_enableChannel(hEdmaDAC);

	/* Now that the port is setup, let's enable it in steps. */
	MCBSP_start(hMcBSP_DAC, MCBSP_XMIT_START | MCBSP_SRGR_START| MCBSP_SRGR_FRAMESYNC, MCBSP_SRGR_DEFAULT_DELAY);

	//printf("Konfiguracja ok \n");
	// Konfiugracja i uruchomienie timera
	//TimerConfig();
	/*gpio_handle = GPIO_open( GPIO_DEV0, GPIO_OPEN_RESET );

	GPIO_config(gpio_handle,&gpio_config);
	GPIO_pinDirection(gpio_handle , GPIO_PIN0, GPIO_OUTPUT);
	GPIO_pinWrite(gpio_handle,GPIO_PIN2,1);*/
}



