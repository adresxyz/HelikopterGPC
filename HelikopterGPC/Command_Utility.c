#include "Command_Utility.h"


//Constants
#define _16BIT_LEN 2
#define _24BIT_LEN 3
#define _48BIT_LEN 6



//Private function declarations:
void CopyString(Uint8* _Source, Uint8* _Destination, int _Length);
void Copy16Bit(int Source,Uint8* _Destination);

void DownloadCommand(Uint8* _CommandBuffer,Uint8* _CommandCounter, Uint8 _NewSign)
{
	int i = 0;

	if((*_CommandCounter)<MAX_COMMAND_LENGTH)
	{
		_CommandBuffer[(*_CommandCounter)] = _NewSign;
		(*_CommandCounter)++;
	}
	else
	{
		for(i=0; i<MAX_COMMAND_LENGTH-1; i++)
		{
			_CommandBuffer[i] = _CommandBuffer[i+1];
		}
		_CommandBuffer[MAX_COMMAND_LENGTH-1] = _NewSign;
	}
}

Commands AnalyzeCommands(Uint8 _ReceivedData)
{
		switch(_ReceivedData)
		{
		case Hello: return Hello;

		case GetDAC_0: return GetDAC_0;
		case GetDAC_1: return GetDAC_1;
		/*case GetADC_2: return GetADC_2;
		case GetADC_3: return GetADC_3;
		case GetADC_4: return GetADC_4;
		case GetADCAll: return GetADCAll;*/

		case SetEnc_0: return SetEnc_0;
		case SetEnc_1: return SetEnc_1;

		case SetWzad_0: return SetWzad_0;
		case SetWzad_1: return SetWzad_1;

		case SetParams1: return SetParams1;
		case SetParams2: return SetParams2;
		/*
		case SetDAC_3: return SetDAC_3;
		case SetDAC_4: return SetDAC_4;
		case SetDACAll: return SetDACAll;*/

		default: return Error;
	}
}

void CommandEngine(Commands _Command, Uint8* _DataToSend, Uint8* _WordsToSend,Uint8* _WordsToReveive, DAC_Values _DAC_Values)
{
	if(_Command == Hello)
	{
//		printf("Halo!\n");
		DSK6713_LED_on(3);
	}
	else if(_Command == GetDAC_0)
	{

		(*_WordsToSend) = _16BIT_LEN;
		Copy16Bit(_DAC_Values.Channel_A0, _DataToSend);
	}
	else if(_Command == GetDAC_1)
		{
			(*_WordsToSend) = _16BIT_LEN;
			Copy16Bit(_DAC_Values.Channel_A1, _DataToSend);

		}
	else if(_Command == SetEnc_0 || _Command == SetEnc_1  || _Command == SetWzad_1)
		{
			(*_WordsToReveive) = _16BIT_LEN;
		}
	else if(_Command == SetWzad_0)
			{
				(*_WordsToReveive) = _24BIT_LEN;
			}
	else if(_Command == SetParams1 || _Command == SetParams2)
		{
			(*_WordsToReveive) = _48BIT_LEN;
		}
}

void RemoveCompletedCommand(Uint8* _CommandBuffer, Uint8* _CommandCounter)
{
	Uint8 i = 0;
	if((*_CommandCounter)>0)
	{
		for(i=0; i<(*_CommandCounter);i++)
		{
			if(i+1 <MAX_COMMAND_LENGTH)
			{
				_CommandBuffer[i]=_CommandBuffer[i+1];
			}
			else
			{
				_CommandBuffer[i] = 0;
			}
		}
		(*_CommandCounter)--;
	}
}

void ProcessReceivedData(Commands _Command,Uint8* _ReceivedData,volatile Enc_Measurement* _pEncMeasurement)
{
	/*int ReceivedValue = 0;
	ReceivedValue = (_ReceivedData[0]<<8) + _ReceivedData[1];*/
	if(_Command == SetEnc_0)
	{
		Enc_ReadEnc(_pEncMeasurement,_ReceivedData,0);
		//printf("Ustawiam Enc0!\n");
	}
	else if(_Command == SetEnc_1)
	{
		Enc_ReadEnc(_pEncMeasurement,_ReceivedData,1);
	}
	else if(_Command == SetWzad_0)
	{
		Wzad_pion = ((_ReceivedData[0]<<8) | _ReceivedData[1])-2*_ReceivedData[2]*((_ReceivedData[0]<<8) | _ReceivedData[1]);
	}
	else if(_Command == SetWzad_1)
	{
		Wzad_poziom = (_ReceivedData[0]<<8) | _ReceivedData[1];

	}
	else if(_Command == SetParams1)
	{
			Parametry1[0] = (_ReceivedData[0]<<8) | _ReceivedData[1];
			Parametry1[1] = (_ReceivedData[2]<<8) | _ReceivedData[3];
			Parametry1[2] = (_ReceivedData[4]<<8) | _ReceivedData[5];

	}
	else if(_Command == SetParams2)
		{
				Parametry2[0] = (_ReceivedData[0]<<8) | _ReceivedData[1];
				Parametry2[1] = (_ReceivedData[2]<<8) | _ReceivedData[3];
				Parametry2[2] = (_ReceivedData[4]<<8) | _ReceivedData[5];
		}

}

//Private functions:
void CopyString(Uint8* _Source, Uint8* _Destination, int _Length)
{
	int i = 0;
	if( _Source != NULL && _Destination != NULL && _Length>0)
	{
		for(i=0; i<_Length; i++)
		{
			_Destination[i] = _Source[i];
		}
	}
}

void Copy16Bit(int Source, Uint8* _Destination)
{
	Uint8 MSB = (Source & 0xff00) >> 8;
	Uint8 LSB = (Source & 0x00ff);
	_Destination[0] = MSB;
	_Destination[1] = LSB;
}


void Enc_ReadEnc(volatile Enc_Measurement* _EncInput, Uint8* _ReceivedData,Uint8 num)
{
	Enc_Refresh_Bytes(_EncInput, _ReceivedData[0], _ReceivedData[1],num);
}
