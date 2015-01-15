#ifndef COMMAND_UTILITY_H_
#define COMMAND_UTILITY_H_

#include <stdio.h>
#include <csl.h>

#include "ADC8361.h"
#include "DAC7716.h"
#include "enkoder.h"

extern volatile short int Wzad_pion;
extern volatile short int Wzad_poziom;
extern volatile short int Parametry1[3];
extern volatile short int Parametry2[3];
//Constants
#define MAX_COMMAND_LENGTH 50

//Enumeratives
typedef enum E_Commands{
	//Diagnostics:
	Hello = 1,
	Error = 2,
	Data = 3,
	Debug = 4,

	//Data Receiving:
	GetDAC_0 = 11,
	GetDAC_1 = 12,
	/*GetADC_2 = 12,
	GetADC_3 = 13,
	GetADC_4 = 14,
	GetADCAll = 15,*/

	//Data Sending:
	SetEnc_0 = 21,
	SetEnc_1 = 22,

	//SetPoint
	SetWzad_0 = 31,
	SetWzad_1 = 32,

	// Params
	SetParams1 = 41,
	SetParams2 = 42
	/*SetDAC_3 = 23,
	SetDAC_4 = 24,
	SetDACAll = 25*/
}Commands;

//Variables
static volatile Uint8 CommandsBuffer[MAX_COMMAND_LENGTH];
static volatile Uint8 CommandCounter = 0;


//Methods

void DownloadCommand( Uint8* _CommandBuffer, Uint8* _CommandCounter, Uint8 _NewSign);
Commands AnalyzeCommands(Uint8 _ReceivedData);
void CommandEngine(Commands _Command, Uint8* _DataToSend, Uint8* _WordsToSend,Uint8* _WordsToReveive, DAC_Values _DAC_Values);
void RemoveCompletedCommand( Uint8* _CommandBuffer, Uint8* _CommandCounter);
void ProcessReceivedData(Commands _Command,Uint8* _ReceivedData,volatile Enc_Measurement* _pEncMeasurement);
void Enc_ReadEnc(volatile Enc_Measurement* _EncInput, Uint8* _ReceivedData,Uint8 num);


#endif
