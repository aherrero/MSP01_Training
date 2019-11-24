#include <msp430.h> 
#include <msp430fr2355.h>

#include "timer.h"
#include "led.h"

/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings

    // Pin IO
    LedInit();

    // Timer
    TimerInit();

    __bis_SR_register(LPM0_bits + GIE);

	return 0;
}


