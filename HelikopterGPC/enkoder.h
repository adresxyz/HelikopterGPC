#ifndef ENKODER_H_
#define ENKODER_H_

#include <stdio.h>
#include <csl.h>

/* Struktura enkodera */
typedef struct _Encoder
{
	short Is_High_Fresh;
	short Is_Low_Fresh;

	Uint8 High_Byte;
	Uint8 Low_Byte;

	short int Value;

}Encoder;

/* G³ówna struktura */
typedef struct _Enc_Measurement
{
	short Is_Enc0_Fresh;
	short Is_Enc1_Fresh;

	Encoder Enc0;
	Encoder Enc1;
}Enc_Measurement;

/* Zmienne globalne */




/* Funkcje */
int Encoder_Are_Bytes_Fresh(volatile Encoder _Enc);
Encoder Encoder_Compute_Value(volatile Encoder _Enc);
void Encoder_Unfresh(volatile Encoder* _Enc);
Encoder Encoder_Fill_With_Zeros(volatile Encoder _Enc);

void Enc_Refresh_Bytes(volatile Enc_Measurement* _Measurement, short int _Value_0, short int _Value_1,Uint8 num);
//void Enc_Refresh_Low_Bytes(volatile Enc_Measurement* _Measurement, short int _Value_0, short int _Value_1);

int Enc_Are_Both_Enc_Fresh(volatile Enc_Measurement* _Measurement);
void Enc_Compute_Values(volatile Enc_Measurement* _Measurement);
void Enc_Unfresh_All(volatile Enc_Measurement* _Measurement);
Enc_Measurement Enc_Fill_With_Zeros(volatile Enc_Measurement _Measurement);

#endif
