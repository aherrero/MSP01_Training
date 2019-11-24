#include <msp430.h> 
#include <msp430fr2355.h>

#include "timer.h"
#include "led.h"

unsigned char g_LedToogleFlag = 0;

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

    // testing
    LedOneOn();
    LedTwoOn();
    LedThreeOn();

    // Loop
    while(1)
    {
        if(g_LedToogleFlag == 1)
        {
            g_LedToogleFlag = 0;
            LedToogle();
        }

        // Go to sleep until interruption
        __bis_SR_register(LPM0_bits + GIE);
    }

	return 0;
}


