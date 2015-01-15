#include <csl_timer.h>
///*----------------------------------------------------------------------------*/
extern far void vectors();
static TIMER_Handle hTimer1;
static Uint32 TimerEventId;
///*----------------------------------------------------------------------------*/
static Uint32 TimerControl = TIMER_CTL_RMK( /* Timer control register (CTL)*/
  TIMER_CTL_INVINP_NO, /* TINP inverter control(INVINP). Only affects operation
                          if CLKSRC =0.
                           TIMER_CTL_INVINP_NO  - Uninverted TINP drives timer
                           TIMER_CTL_INVINP_YES - inverted TINP drives timer */

  TIMER_CTL_CLKSRC_CPUOVR4,/* Timer input clock source (CLKSRC)
                           TIMER_CTL_CLKSRC_CPUOVR4 - CPU clock /4           */

  TIMER_CTL_CP_PULSE, /* Clock/pulse mode(CP)
                           TIMER_CTL_CP_PULSE - Pulse mode.TSTAT is active one
                                CPU clock after the timer reaches the timer
                                period.PWID determines when it goes inactive.*/

  TIMER_CTL_HLD_YES, /* Hold(HLD). Counter may be read or written regardless of
                        HLD value.
                           TIMER_CTL_HLD_YES - Counter is disabled and held in
                                current value.
                           TIMER_CTL_HLD_NO - COunter is allowed to count.   */

  TIMER_CTL_GO_NO, /* Go bit(GO). Resets and starts the timer counter.
                           TIMER_CTL_GO_NO - No effects on the timer.
                           TIMER_CTL_GO_YES - if HLD =1, the counter register
                                is zeroed and begins counting on next clock. */
  TIMER_CTL_PWID_ONE, /* Pulse width(PWID). Only used in pulse mode.
                           TIMER_CTL_PWID_ONE - TSTAT goes inactive one timer
                                input clock cycle after the timer counter value
                                equals the timer period value.
                           TIMER_CTL_PWID_TWO -  TSTAT goes inactive one timer
                                input clock cycle after the timer counter value
                                equals the timer period value.               */

  TIMER_CTL_DATOUT_0, /* Data output (DATOUT).
                           TIMER_CTL_DATOUT_0 - If FUNC  =0,the DATOUT is
                                driven on TOUT.
                           TIMER_CTL_DATOUT_1 - If FUNC =1,The DATOUT is driven
                                on TOUT after inversion by INVOUT.           */

  TIMER_CTL_INVOUT_NO, /* TOUT inverter control (INVOUT)
                           TIMER_CTL_INVOUT_NO - Uninverted TSTAT drives TOUT
                           TIMER_CTL_INVOUT_YES - Inverted TSTAT drives TOUT.*/
  TIMER_CTL_FUNC_GPIO /* Function of TOUT pin(FUNC).
                           TIMER_CTL_FUNC_GPIO - TOU is a general purpose
                                output pin
                           TIMER_CTL_FUNC_TOUT - TOUT is a timer output pin  */

);

void TimerConfig();
