#include <stdio.h>
#include "enkoder.h"

void Encoder_Unfresh(volatile Encoder* _Enc)
{
	_Enc->Is_High_Fresh = 0;
	_Enc->Is_Low_Fresh = 0;
}
int Encoder_Are_Bytes_Fresh(volatile Encoder _Enc)
{
	if(_Enc.Is_High_Fresh == 0)
	{
		return 0;
	}
	//printf("Pierwszy ok!\n");
	if(_Enc.Is_Low_Fresh == 0)
	{
		return 0;
	}
	return 1;
}
Encoder Encoder_Compute_Value(volatile Encoder _Enc)
{
	_Enc.Value = (_Enc.High_Byte << 8)|(_Enc.Low_Byte);
	return _Enc;
}
Encoder Encoder_Fill_With_Zeros(volatile Encoder _Enc)
{
	_Enc.Is_High_Fresh = 0;
	_Enc.Is_Low_Fresh = 0;

	_Enc.High_Byte = 0;
	_Enc.Low_Byte = 0;

	_Enc.Value = 0;

	return _Enc;
}
void Enc_Refresh_Bytes(volatile Enc_Measurement* _Measurement, short int _Value_0, short int _Value_1, Uint8 num)
{
	if(_Measurement != 0)
	{
		//printf("Robie cokolwiek\n");
		if (!num)
		{
			_Measurement->Enc0.High_Byte = _Value_0;
			_Measurement->Enc0.Is_High_Fresh = 1;

			_Measurement->Enc0.Low_Byte = _Value_1;
			_Measurement->Enc0.Is_Low_Fresh = 1;
		}
		else
		{
			_Measurement->Enc1.High_Byte = _Value_0;
			_Measurement->Enc1.Is_High_Fresh = 1;

			_Measurement->Enc1.Low_Byte = _Value_1;
			_Measurement->Enc1.Is_Low_Fresh = 1;
		}
	}

}

int Enc_Are_Both_Enc_Fresh(volatile Enc_Measurement* _Measurement)
{
	//printf("Sprawdzam\n");
	if (Encoder_Are_Bytes_Fresh(_Measurement->Enc0) == 0)
	{
		return 0;
	}
	//printf("Enc0 kompletny!\n");
	_Measurement->Is_Enc0_Fresh = 1;
	if (Encoder_Are_Bytes_Fresh(_Measurement->Enc1) == 0)
	{
		return 0;
	}
	_Measurement->Is_Enc1_Fresh = 1;
	return 1;
}

void Enc_Compute_Values(volatile Enc_Measurement* _Measurement)
{

	_Measurement->Enc0 = Encoder_Compute_Value(_Measurement->Enc0);
	_Measurement->Enc1 = Encoder_Compute_Value(_Measurement->Enc1);
}
void Enc_Unfresh_All(volatile Enc_Measurement* _Measurement)
{
	Encoder_Unfresh(&(_Measurement->Enc0));
	Encoder_Unfresh(&(_Measurement->Enc1));
	_Measurement->Is_Enc0_Fresh = 0;
	_Measurement->Is_Enc1_Fresh = 0;
}
Enc_Measurement Enc_Fill_With_Zeros(volatile Enc_Measurement _Measurement)
{
	_Measurement.Is_Enc0_Fresh = 0;
	_Measurement.Is_Enc1_Fresh = 0;
	_Measurement.Enc0 = Encoder_Fill_With_Zeros(_Measurement.Enc0);
	_Measurement.Enc1 = Encoder_Fill_With_Zeros(_Measurement.Enc1);
	return _Measurement;
}


