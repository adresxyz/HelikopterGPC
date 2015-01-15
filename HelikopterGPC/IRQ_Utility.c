#include "IRQ_Utility.h"
#include <csl_irq.h>

/*this function should be called firstly in the program to prepare interrupts*/
void setupIRQ(void)
{
     IRQ_setVecs(vectors);     /* point to the IRQ vector table	*/

     IRQ_nmiEnable();
     IRQ_globalEnable();

     IRQ_map(IRQ_EVT_EDMAINT, 8);
     IRQ_reset(IRQ_EVT_EDMAINT);

     IRQ_map(IRQ_EVT_I2CINT0,9);
     IRQ_reset(IRQ_EVT_I2CINT0);
}

/*to enable necessary interrupts use this function*/
void enableIRQ(void)
{
	IRQ_enable(IRQ_EVT_EDMAINT);
	IRQ_enable(IRQ_EVT_I2CINT0);
}

