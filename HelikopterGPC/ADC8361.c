#include <stdio.h>
#include "ADC8361.h"

/*Variable*/
int Ch0_Counter = 0;
int Ch1_Counter = 0;
int Ch2_Counter = 0;
int Ch3_Counter = 0;
int Ch_Error_Counter = 0;

/*Help Functions*/

int ADC_Are_All_Channels_Fresh(volatile ADC_Measurement _Measurement)
{
	if(_Measurement.IsChannel_A0_Fresh == 0)
	{
		return 0;
	}
	if(_Measurement.IsChannel_A1_Fresh == 0)
	{
		return 0;
	}
	if(_Measurement.IsChannel_B0_Fresh == 0)
	{
		return 0;
	}
	if(_Measurement.IsChannel_B1_Fresh == 0)
	{
		return 0;
	}

	return 1;
}

void ADC_Unfresh(volatile ADC_Measurement* _Measurement)
{
	_Measurement->IsChannel_A0_Fresh = 0;
	_Measurement->IsChannel_A1_Fresh = 0;
	_Measurement->IsChannel_B0_Fresh = 0;
	_Measurement->IsChannel_B1_Fresh = 0;
}

int ADC_Get_Channel_Num(int _MeasuredValue)
{
   int SelectedChannel = (_MeasuredValue & CHANNEL_NUM_MASK) >> CHANNEL_OFFSET;
   return SelectedChannel;
}

void ADC_Fill_Measurement_Struct(volatile ADC_Measurement* _Measurement, int _Channel_Num, int _Value)
{
	if(_Measurement != 0)
	{
		if(_Channel_Num == 0)
		{
			_Measurement->Channel_A0 = (_Value & VALUE_MASK) >> VALUE_OFFSET;
			_Measurement->IsChannel_A0_Fresh = 1;
			Ch0_Counter++;
		}
		else if(_Channel_Num == 1)
		{
			_Measurement->Channel_B0 = (_Value & VALUE_MASK) >> VALUE_OFFSET;
			_Measurement->IsChannel_B0_Fresh = 1;
			Ch1_Counter++;
		}
		else if(_Channel_Num == 2)
		{
			_Measurement->Channel_A1 = (_Value & VALUE_MASK) >> VALUE_OFFSET;
			_Measurement->IsChannel_A1_Fresh = 1;
			Ch2_Counter++;
		}
		else if(_Channel_Num == 3)
		{
			_Measurement->Channel_B1 = (_Value & VALUE_MASK) >> VALUE_OFFSET;
			_Measurement->IsChannel_B1_Fresh = 1;
			Ch3_Counter++;
		}
		else
		{
			Ch_Error_Counter++;
		}
	}
}

ADC_Measurement ADC_Fill_Measurement_With_Zeros(void)
{
	ADC_Measurement EmptyMeasurement;
	EmptyMeasurement.IsChannel_A0_Fresh = 0;
	EmptyMeasurement.IsChannel_A1_Fresh = 0;
	EmptyMeasurement.IsChannel_B0_Fresh = 0;
	EmptyMeasurement.IsChannel_B1_Fresh = 0;
	EmptyMeasurement.Channel_A0 = 0;
	EmptyMeasurement.Channel_A1 = 0;
	EmptyMeasurement.Channel_B0 = 0;
	EmptyMeasurement.Channel_B1 = 0;
	return EmptyMeasurement;
}

void ADC_Collect_EDMA(int _PingPong, int* _PingBuff, int* _PongBuff, volatile ADC_Measurement* _Measurement)
{
	  int ReceivedValue;

	  if (_PingPong)
	  {
		  ReceivedValue = (*_PingBuff);
	  }else
	  {
		  ReceivedValue = (*_PongBuff);
	  }

	  ADC_Fill_Measurement_Struct(_Measurement, ADC_Get_Channel_Num(ReceivedValue), ReceivedValue);
}

/*Printing Functions*/

void ADC_Show_Measurement(volatile ADC_Measurement* _Measurement)
{
	printf("\nChannel_A0 = %d \nChannel_B0 = %d \nChannel_A1 = %d \nChannel_B1 = %d\n\n", _Measurement->Channel_A0, _Measurement->Channel_B0,_Measurement->Channel_A1,_Measurement->Channel_B1);
}
