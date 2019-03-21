#include <msp430.h>
#include <msp430fr2355.h>

#include "timer.h"

/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    // ------------------------------------------------------
    // Led Output

    P1DIR |= 0x01;  // The pin 1 from port 1 (pin 1.0) is set as an output.
                    // The OR gate to keep the previous configuration

    // P1OUT |= 0x01;  // Port1 output, pin 1.1 to HIGH

    // Configure timer
    timer_init();

    // Start timer interruption
    __bis_SR_register(LPM3_bits | GIE);     // Enter LPM3 w/ interrupt


    return 0;
}
