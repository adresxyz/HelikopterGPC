#include <csl.h>
#include <csl_mcbsp.h>

#include "McBSP_Utility.h"

void Polling_Transmit(MCBSP_Handle _hMcbsp, int _WriteValue)
{
	 /* wait until the transmitter is ready for a sample then write to it */
	 while (!MCBSP_xrdy(_hMcbsp));
	 MCBSP_write(_hMcbsp,_WriteValue);
	 return;
}

void Polling_Single_Receive(MCBSP_Handle _hMcbsp, int* _ReadTo)
{
	  /* now wait until the value is received then read it */
	    while (!MCBSP_rrdy(_hMcbsp));
	    *_ReadTo = MCBSP_read(_hMcbsp);
	    return;
}

