#include "timer.h"
void TimerConfig(){
	/* Open TIMER1 device, and reset them to power-on default state */
	hTimer1 = TIMER_open(TIMER_DEV1, TIMER_OPEN_RESET);

	/* Obtain the event ID for the timer device */
	TimerEventId = TIMER_getEventId(hTimer1);

	IRQ_setVecs(vectors);     /* point to the IRQ vector table    */
	IRQ_globalEnable();       /* Globally enable interrupts       */
	IRQ_nmiEnable();          /* Enable NMI interrupt             */

	/* Map TIMER events to physical interrupt number */
	IRQ_map(TimerEventId, 14);

	/* Reset the timer events */
	IRQ_reset(TimerEventId);

	/* Configure the timer devices */
	TIMER_configArgs(hTimer1,
			TimerControl, /* use predefined control value  */
			//0x2719c40,   /* set period                    */
			0x3719c40,
			0x00000000    /* start count value at zero     */
	);

	/* Enable the timer events(events are disabled while resetting) */
	IRQ_enable(TimerEventId);

	/* Start the timers */
	TIMER_start(hTimer1);
}
