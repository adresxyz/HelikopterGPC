#ifndef I2C_UTILITY_H_
#define I2C_UTILITY_H_

#include <csl_i2c.h>
#include "Command_Utility.h"
/*Constants*/
static int const WORDS_TO_SEND = 8;

/*Config Structures*/


/*Variables*/

/*I2C Handlers*/
static I2C_Handle hI2C0;  							/*Handler for I2C_DEV0*/

/*Methods*/
I2C_Config I2C_PrepareMasterConfigStruct(int _WordsToSend);	/*Config Structure Preparation*/
I2C_Config I2C_PrepareSlaveConfigStruct();
Uint8 I2C_InterruptsRoutine(Uint8 _Val,Uint8* _ReceivedData, Uint8 ValueToSend, I2C_Handle _handler);

#endif /* I2C_UTILITY_H_ */
