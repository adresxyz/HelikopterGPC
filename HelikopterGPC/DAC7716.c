#include "DAC7716.h"
#include <stdio.h>

unsigned int DAC_Prepare_Frame(unsigned int _RW,unsigned int _Reg_Address,unsigned int _Value)
{
	if(_RW == DAC_WRITE)
	{
		if(_Reg_Address == DAC_AC0 || _Reg_Address == DAC_AC1 || _Reg_Address == DAC_AC2 || _Reg_Address == DAC_AC3)
		{
			return ((_RW | _Reg_Address | ((_Value & DAC_AC_DATA_MSK )<<DAC_AC_DATA_OFFSET)) & DAC_FRAME_MSK);
		}
		else if(_Reg_Address == DAC_ZERO_AC0 || _Reg_Address == DAC_ZERO_AC1 || _Reg_Address == DAC_ZERO_AC2 || _Reg_Address == DAC_ZERO_AC3)
		{
			return ((_RW | _Reg_Address | ((_Value & DAC_ZERO_DATA_MSK )<<DAC_ZERO_DATA_OFFSET)) & DAC_FRAME_MSK);
		}
		else if(_Reg_Address == DAC_GAIN_AC0 || _Reg_Address == DAC_GAIN_AC1 || _Reg_Address == DAC_GAIN_AC2 || _Reg_Address == DAC_GAIN_AC3)
		{
			return ((_RW | _Reg_Address | ((_Value & DAC_GAIN_DATA_MSK )<<DAC_GAIN_DATA_OFFSET)) & DAC_FRAME_MSK);
		}
		else
		{
			return ((_RW | _Reg_Address | _Value) & DAC_FRAME_MSK);
		}
	}
	else if (_RW == DAC_READ)
	{
		return ((_RW | _Reg_Address | ((_Value & DAC_AC_DATA_MSK )<<DAC_AC_DATA_OFFSET)) & DAC_FRAME_MSK);
	}
	return 0;
}

void DAC_Update_Channel_To_Send(short* _Channel_To_Send)
{
	(*_Channel_To_Send) = ((*_Channel_To_Send) + 1) % CHANNELS;
}

void DAC_Prepare_EDMA(short int _PingPong,short _ChannelToSend, int* _PingBuff, int* _PongBuff, volatile DAC_Values _Values)
{
	unsigned int DAC_Input;

	 switch (_ChannelToSend )
	{
	 case 0: DAC_Input = DAC_Prepare_Frame(DAC_WRITE, DAC_AC0, _Values.Channel_A0); break;
	 case 1: DAC_Input = DAC_Prepare_Frame(DAC_WRITE, DAC_AC1, _Values.Channel_A1); break;
	 case 2: DAC_Input = DAC_Prepare_Frame(DAC_WRITE, DAC_AC2, _Values.Channel_A2); break;
	 case 3: DAC_Input = DAC_Prepare_Frame(DAC_WRITE, DAC_AC3, _Values.Channel_A3); break;
	}

	/*Let's copy input value into adequate transmitter buffer before we process it with EDMA*/
	if (_PingPong)
	{
		*_PingBuff = DAC_Input;
	}else
    {
		*_PongBuff = DAC_Input;
	}
}

DAC_Values DAC_Fill_Values_With_Zeros(void)
{
	DAC_Values NewValues;
	NewValues.Channel_A0 = 0;
	NewValues.Channel_A1 = 0;
	NewValues.Channel_A2 = 0;
	NewValues.Channel_A3 = 0;
	return NewValues;
}

void PrintfDACTransferInfo(short int _ChannelToSend,short int _DAC_PingPong,int _ValueToSend )
{
	printf("Channel to send: %d \n",_ChannelToSend);
	printf("DAC PingPong: %d \n",_DAC_PingPong);
	printf("Channel to send: %d \n",_ChannelToSend);
	printf("Value to send: %d \n",_ValueToSend);
}


