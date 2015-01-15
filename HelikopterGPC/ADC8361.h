#ifndef ADC8361_H_
#define ADC8361_H_

/*Constants*/
#define CHANNEL_NUM_MASK 0xC0000
#define CHANNEL_OFFSET 18
#define VALUE_MASK 0x3ffff
#define VALUE_OFFSET 2

/*Structures*/
typedef struct _ADC_Measurement
{
	short IsChannel_A0_Fresh;
	short IsChannel_A1_Fresh;
	short IsChannel_B0_Fresh;
	short IsChannel_B1_Fresh;
	int Channel_A0;
	int Channel_A1;
	int Channel_B0;
	int Channel_B1;
}ADC_Measurement;

/*ADC Variables*/
static volatile ADC_Measurement ADCMeasurement;
static volatile ADC_Measurement Measurement_History[100];

/*Functions*/
int 			ADC_Get_Channel_Num				(int _MeasuredValue);
void 			ADC_Fill_Measurement_Struct		(volatile ADC_Measurement* _Measurement, int _Channel_Num, int _Value);
void			ADC_Collect_EDMA				(int _PingPong, int* _PingBuff, int* _PongBuff, volatile ADC_Measurement* _Measurement);
ADC_Measurement ADC_Fill_Measurement_With_Zeros	(void);
int 			ADC_Are_All_Channels_Fresh		(volatile ADC_Measurement _Measurement);
void 			ADC_Unfresh						(volatile ADC_Measurement* _Measurement);
void 			ADC_Show_Measurement			(volatile ADC_Measurement* _Measurement);

#endif /* ADC8361_H_ */
