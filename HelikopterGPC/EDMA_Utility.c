#include <csl_edma.h>
#include "EDMA_Utility.h"


Uint32 EDMAADCConfOpt(void)
{
	return  EDMA_OPT_RMK(          /* Making Options parameter register - EDMA_OPT    */

			   EDMA_OPT_PRI_LOW,    /* Priority levels for EDMA events:-
			                             EDMA_OPT_PRI_LOW  - Low priority EDMA transfer
			                             EDMA_OPT_PRI_HIGH - High priority EDMA transfer*/

			   EDMA_OPT_ESIZE_32BIT,/* Element size :-
			                             EDMA_OPT_ESIZE_32BIT - 32 bit word
			                             EDMA_OPT_ESIZE_16BIT - 16 bit word
			                             EDMA_OPT_ESIZE_8BIT  -  8 bit word              */

			   EDMA_OPT_2DS_NO,     /* Source dimension :-
			                             EDMA_OPT_2DS_NO  - 1-dimensional source
			                             EDMA_OPT_2DS_YES - 2-dimensional source         */

			   EDMA_OPT_SUM_NONE,   /* Source address update mode :-
			                             EDMA_OPT_SUM_NONE - Fixed address mode
			                             EDMA_OPT_SUM_INC  - Increment address mode
			                             EDMA_OPT_SUM_DEC  - Decrement address mode
			                             EDMA_OPT_SUM_IDX  - Address modified by element
			                                                 index or frame Index        */
			   EDMA_OPT_2DD_NO,     /* Destination dimension :-
			                             EDMA_OPT_2DD_NO   - 1-dimensional source
			                             EDMA_OPT_2DD_YES  - 2-dimensional source        */

			   EDMA_OPT_DUM_NONE,    /* Destination address update mode :-
			                             EDMA_OPT_DUM_NONE - Fixed address mode
			                             EDMA_OPT_DUM_INC  - Increment address mode
			                             EDMA_OPT_DUM_DEC  - Decrement address mode
			                             EDMA_OPT_DUM_IDX  - Address modified by element
			                                                 index or frame Index        */

			   EDMA_OPT_TCINT_YES,  /* Transfer complete interrupt :-
			                             EDMA_OPT_TCINT_NO  - Indication disabled
			                             EDMA_OPT_TCINT_YES - Indication enabled         */

			   EDMA_OPT_TCC_OF(EDMA_ADC_IRQ),/* Transfer complete code                     */

			   EDMA_OPT_LINK_YES,   /* Linking of event parameters
			                             EDMA_OPT_LINK_NO   -  Disabled
			                             EDMA_OPT_LINK_YES  -  Enabled                   */

			   EDMA_OPT_FS_NO       /* Frame synchronization
			                             EDMA_OPT_FS_NO  - Channel is element/array
			                                                synchronized
			                             EDMA_OPT_FS_YES -  Channel is frame synchronized*/
			  );
}

Uint32 EDMADACConfOpt(void)
{
	return  EDMA_OPT_RMK(          /* Making Options parameter register - EDMA_OPT    */

			   EDMA_OPT_PRI_LOW,    /* Priority levels for EDMA events:-
			                             EDMA_OPT_PRI_LOW  - Low priority EDMA transfer
			                             EDMA_OPT_PRI_HIGH - High priority EDMA transfer*/

			   EDMA_OPT_ESIZE_32BIT,/* Element size :-
			                             EDMA_OPT_ESIZE_32BIT - 32 bit word
			                             EDMA_OPT_ESIZE_16BIT - 16 bit word
			                             EDMA_OPT_ESIZE_8BIT  -  8 bit word              */

			   EDMA_OPT_2DS_NO,     /* Source dimension :-
			                             EDMA_OPT_2DS_NO  - 1-dimensional source
			                             EDMA_OPT_2DS_YES - 2-dimensional source         */

			   EDMA_OPT_SUM_NONE,   /* Source address update mode :-
			                             EDMA_OPT_SUM_NONE - Fixed address mode
			                             EDMA_OPT_SUM_INC  - Increment address mode
			                             EDMA_OPT_SUM_DEC  - Decrement address mode
			                             EDMA_OPT_SUM_IDX  - Address modified by element
			                                                 index or frame Index        */
			   EDMA_OPT_2DD_NO,     /* Destination dimension :-
			                             EDMA_OPT_2DD_NO   - 1-dimensional source
			                             EDMA_OPT_2DD_YES  - 2-dimensional source        */

			   EDMA_OPT_DUM_NONE,    /* Destination address update mode :-
			                             EDMA_OPT_DUM_NONE - Fixed address mode
			                             EDMA_OPT_DUM_INC  - Increment address mode
			                             EDMA_OPT_DUM_DEC  - Decrement address mode
			                             EDMA_OPT_DUM_IDX  - Address modified by element
			                                                 index or frame Index        */

			   EDMA_OPT_TCINT_YES,  /* Transfer complete interrupt :-
			                             EDMA_OPT_TCINT_NO  - Indication disabled
			                             EDMA_OPT_TCINT_YES - Indication enabled         */

			   EDMA_OPT_TCC_OF(EDMA_DAC_IRQ),/* Transfer complete code                     */

			   EDMA_OPT_LINK_YES,   /* Linking of event parameters
			                             EDMA_OPT_LINK_NO   -  Disabled
			                             EDMA_OPT_LINK_YES  -  Enabled                   */

			   EDMA_OPT_FS_NO       /* Frame synchronization
			                             EDMA_OPT_FS_NO  - Channel is element/array
			                                                synchronized
			                             EDMA_OPT_FS_YES -  Channel is frame synchronized*/
			  );
}

Uint32 EDMI2CRecConfOpt(void)
{
	return  EDMA_OPT_RMK(          /* Making Options parameter register - EDMA_OPT    */

			   EDMA_OPT_PRI_LOW,    /* Priority levels for EDMA events:-
			                             EDMA_OPT_PRI_LOW  - Low priority EDMA transfer
			                             EDMA_OPT_PRI_HIGH - High priority EDMA transfer*/

			   EDMA_OPT_ESIZE_32BIT,/* Element size :-
			                             EDMA_OPT_ESIZE_32BIT - 32 bit word
			                             EDMA_OPT_ESIZE_16BIT - 16 bit word
			                             EDMA_OPT_ESIZE_8BIT  -  8 bit word              */

			   EDMA_OPT_2DS_NO,     /* Source dimension :-
			                             EDMA_OPT_2DS_NO  - 1-dimensional source
			                             EDMA_OPT_2DS_YES - 2-dimensional source         */

			   EDMA_OPT_SUM_NONE,   /* Source address update mode :-
			                             EDMA_OPT_SUM_NONE - Fixed address mode
			                             EDMA_OPT_SUM_INC  - Increment address mode
			                             EDMA_OPT_SUM_DEC  - Decrement address mode
			                             EDMA_OPT_SUM_IDX  - Address modified by element
			                                                 index or frame Index        */
			   EDMA_OPT_2DD_NO,     /* Destination dimension :-
			                             EDMA_OPT_2DD_NO   - 1-dimensional source
			                             EDMA_OPT_2DD_YES  - 2-dimensional source        */

			   EDMA_OPT_DUM_NONE,    /* Destination address update mode :-
			                             EDMA_OPT_DUM_NONE - Fixed address mode
			                             EDMA_OPT_DUM_INC  - Increment address mode
			                             EDMA_OPT_DUM_DEC  - Decrement address mode
			                             EDMA_OPT_DUM_IDX  - Address modified by element
			                                                 index or frame Index        */

			   EDMA_OPT_TCINT_YES,  /* Transfer complete interrupt :-
			                             EDMA_OPT_TCINT_NO  - Indication disabled
			                             EDMA_OPT_TCINT_YES - Indication enabled         */

			   EDMA_OPT_TCC_OF(EDMA_I2C_REC_IRQ),/* Transfer complete code                     */

			   EDMA_OPT_LINK_YES,   /* Linking of event parameters
			                             EDMA_OPT_LINK_NO   -  Disabled
			                             EDMA_OPT_LINK_YES  -  Enabled                   */

			   EDMA_OPT_FS_NO       /* Frame synchronization
			                             EDMA_OPT_FS_NO  - Channel is element/array
			                                                synchronized
			                             EDMA_OPT_FS_YES -  Channel is frame synchronized*/
			  );
}

Uint32 EDMI2CTransConfOpt(void)
{
	return  EDMA_OPT_RMK(          /* Making Options parameter register - EDMA_OPT    */

			   EDMA_OPT_PRI_LOW,    /* Priority levels for EDMA events:-
			                             EDMA_OPT_PRI_LOW  - Low priority EDMA transfer
			                             EDMA_OPT_PRI_HIGH - High priority EDMA transfer*/

			   EDMA_OPT_ESIZE_32BIT,/* Element size :-
			                             EDMA_OPT_ESIZE_32BIT - 32 bit word
			                             EDMA_OPT_ESIZE_16BIT - 16 bit word
			                             EDMA_OPT_ESIZE_8BIT  -  8 bit word              */

			   EDMA_OPT_2DS_NO,     /* Source dimension :-
			                             EDMA_OPT_2DS_NO  - 1-dimensional source
			                             EDMA_OPT_2DS_YES - 2-dimensional source         */

			   EDMA_OPT_SUM_NONE,   /* Source address update mode :-
			                             EDMA_OPT_SUM_NONE - Fixed address mode
			                             EDMA_OPT_SUM_INC  - Increment address mode
			                             EDMA_OPT_SUM_DEC  - Decrement address mode
			                             EDMA_OPT_SUM_IDX  - Address modified by element
			                                                 index or frame Index        */
			   EDMA_OPT_2DD_NO,     /* Destination dimension :-
			                             EDMA_OPT_2DD_NO   - 1-dimensional source
			                             EDMA_OPT_2DD_YES  - 2-dimensional source        */

			   EDMA_OPT_DUM_NONE,    /* Destination address update mode :-
			                             EDMA_OPT_DUM_NONE - Fixed address mode
			                             EDMA_OPT_DUM_INC  - Increment address mode
			                             EDMA_OPT_DUM_DEC  - Decrement address mode
			                             EDMA_OPT_DUM_IDX  - Address modified by element
			                                                 index or frame Index        */

			   EDMA_OPT_TCINT_YES,  /* Transfer complete interrupt :-
			                             EDMA_OPT_TCINT_NO  - Indication disabled
			                             EDMA_OPT_TCINT_YES - Indication enabled         */

			   EDMA_OPT_TCC_OF(EDMA_I2C_TRANS_IRQ),/* Transfer complete code                     */

			   EDMA_OPT_LINK_YES,   /* Linking of event parameters
			                             EDMA_OPT_LINK_NO   -  Disabled
			                             EDMA_OPT_LINK_YES  -  Enabled                   */

			   EDMA_OPT_FS_NO       /* Frame synchronization
			                             EDMA_OPT_FS_NO  - Channel is element/array
			                                                synchronized
			                             EDMA_OPT_FS_YES -  Channel is frame synchronized*/
			  );
}

void enableIRQ_EDMA(void)
{
	 EDMA_intDisable(EDMA_ADC_IRQ);
	 EDMA_intClear(EDMA_ADC_IRQ);
	 EDMA_intEnable(EDMA_ADC_IRQ);

	 EDMA_intDisable(EDMA_DAC_IRQ);
	 EDMA_intClear(EDMA_DAC_IRQ);
	 EDMA_intEnable(EDMA_DAC_IRQ);

	 EDMA_intDisable(EDMA_I2C_REC_IRQ);
	 EDMA_intClear(EDMA_I2C_REC_IRQ);
	 EDMA_intEnable(EDMA_I2C_REC_IRQ);

	 EDMA_intDisable(EDMA_I2C_TRANS_IRQ);
	 EDMA_intClear(EDMA_I2C_TRANS_IRQ);
	 EDMA_intEnable(EDMA_I2C_TRANS_IRQ);
}

void stopEdma(EDMA_Handle* _Handler, int _EDMA_IRQ, EDMA_Handle* _HPing, EDMA_Handle* _HPong)
{
    /*Disable interrupts, close EDMA channel before exit of the program*/
    IRQ_disable(IRQ_EVT_EDMAINT);
    EDMA_RSET(CCER,0x00000000);
    EDMA_disableChannel(*_Handler);
    EDMA_intDisable(_EDMA_IRQ);
    EDMA_intClear(_EDMA_IRQ);

 	EDMA_close(*_Handler);
 	EDMA_resetAll();
 	EDMA_RSET(CIPR,0xFFFFFFFF);
 	EDMA_RSET(ECR,0xFFFFFFFF);

 	EDMA_freeTable(*_HPing);
 	EDMA_freeTable(*_HPong);
}


