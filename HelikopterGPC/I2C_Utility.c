#include "I2C_Utility.h"
#include <csl_i2c.h>
#include <stdio.h>

void I2C_Send_Polling(I2C_Handle _handler)
{

	I2C_start(_handler);

}

I2C_Config I2C_PrepareMasterConfigStruct(int _WordsToSend)
{
	I2C_Config Config = {
			I2C_I2COAR_RMK(0x0f), 						//own address
			I2C_I2CIMR_RMK(								//I2C0 Interrupt Mask/Status register
					I2C_I2CIMR_ICXRDY_UNMSK,
					I2C_I2CIMR_ICRRDY_UNMSK,
					I2C_I2CIMR_ARDY_UNMSK,
					I2C_I2CIMR_NACK_UNMSK,
					I2C_I2CIMR_AL_UNMSK),
			I2C_I2CCLKL_RMK(50), 						//I2C0 Clock Divider Low register
			I2C_I2CCLKH_RMK(50),						//I2C0 Clock Divider High register
			I2C_I2CCNT_RMK(8), 				//I2C0 Data Count register
			I2C_I2CSAR_RMK(0x25), 						//I2C0 Slave Address register
			I2C_I2CMDR_RMK(								//I2C0 Mode register
					I2C_I2CMDR_NACKMOD_ACK,
					I2C_I2CMDR_FREE_RFREE,
					I2C_I2CMDR_STT_NONE,
					I2C_I2CMDR_STP_NONE,
					I2C_I2CMDR_MST_MASTER,
					I2C_I2CMDR_TRX_XMT,
					I2C_I2CMDR_XA_7BIT,
					I2C_I2CMDR_RM_NONE,
					I2C_I2CMDR_DLB_LOOPBACK,
					I2C_I2CMDR_IRS_NRST,
					I2C_I2CMDR_STB_NONE,
					I2C_I2CMDR_FDF_NONE,
					I2C_I2CMDR_BC_BIT8FDF),
			I2C_I2CPSC_RMK(0xff)						//I2C0 Prescaler register
	};
	Config.i2ccnt = I2C_I2CCNT_RMK(_WordsToSend);

	return Config;
}

I2C_Config I2C_PrepareSlaveConfigStruct()
{
	I2C_Config Config = {
			I2C_I2COAR_RMK(0x5f), 						//own address
			I2C_I2CIMR_RMK(								//I2C0 Interrupt Mask/Status register
					I2C_I2CIMR_ICXRDY_UNMSK,
					I2C_I2CIMR_ICRRDY_UNMSK,
					I2C_I2CIMR_ARDY_UNMSK,
					I2C_I2CIMR_NACK_UNMSK,
					I2C_I2CIMR_AL_UNMSK),
			I2C_I2CCLKL_RMK(50), 						//I2C0 Clock Divider Low register
			I2C_I2CCLKH_RMK(50),						//I2C0 Clock Divider High register
			I2C_I2CCNT_RMK(4), 							//I2C0 Data Count register
			I2C_I2CSAR_RMK(0x25), 						//I2C0 Slave Address register
			I2C_I2CMDR_RMK(								//I2C0 Mode register
					I2C_I2CMDR_NACKMOD_NACK,
					I2C_I2CMDR_FREE_BSTOP,
					I2C_I2CMDR_STT_NONE,
					I2C_I2CMDR_STP_NONE,
					I2C_I2CMDR_MST_SLAVE,
					I2C_I2CMDR_TRX_RCV,
					I2C_I2CMDR_XA_7BIT,
					I2C_I2CMDR_RM_NONE,
					I2C_I2CMDR_DLB_NONE,
					I2C_I2CMDR_IRS_NRST,
					I2C_I2CMDR_STB_NONE,
					I2C_I2CMDR_FDF_NONE,
					I2C_I2CMDR_BC_BIT8FDF),
			I2C_I2CPSC_RMK(0x0e)						//I2C0 Prescaler register
	};
	return Config;
}

Uint8 I2C_InterruptsRoutine(Uint8 _Val,Uint8* _ReceivedData, Uint8 ValueToSend, I2C_Handle _handler)
{
	/*if(_Val == I2C_EVT_AL) 	// receive data ready
	{
		printf("AL\n");
	}
	else if(_Val == I2C_EVT_NACK) 	// receive data ready
	{
		printf("NACK\n");
	}
	else if(_Val == I2C_EVT_ARDY) 	// receive data ready
	{
		printf("ARDY\n");
	}
	else */
	if(_Val == I2C_EVT_ICRRDY) 	// receive data ready
	{
		*_ReceivedData = I2C_readByte(_handler);
		//printf("received data= %x\n",*_ReceivedData);

		return 1;
	}
	else if(_Val == I2C_EVT_ICXRDY)	// transmit data ready
	{
		I2C_writeByte(_handler,ValueToSend);
		//printf("Send data= %x\n",ValueToSend);
		return 0;
	}
	return 0;
}
