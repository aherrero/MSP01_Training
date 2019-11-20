#include <msp430.h> 
#include <msp430fr2355.h>

unsigned int timerCount = 0;    // Keep track of timer ticks

/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	P1DIR |= 0x01;
	// P1OUT = 0x00;    // turn off all port
	// P1OUT |= 0x01;   // turn on only P1.1

	// timer control register configuration
	TB1CTL |= 0x0100;   // timer 0, tassel 01, means ACLK
	TB1CTL |= 0x0010;   // count up mode
	TB1CTL |= 0x0004;   // clear the timer

	TB1CCR0 = 4096;     // set capture and control threshold to 1/8 of 32kHz
	TB1CCTL0 |= 0x0010;  // enable interrupt in capture and control

	__bis_SR_register(LPM3_bits | GIE);     // Enter LPM3 w/ interrupt

	return 0;
}

// Timer B1 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = TIMER1_B0_VECTOR
__interrupt void Timer1_B0_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER1_B0_VECTOR))) Timer1_B0_ISR (void)
#else
#error Compiler not supported!
#endif
{
    timerCount++;

    // Timer is 1/8 of a second, so count up to 8 for 1 second toggle
    if (timerCount >= 8)
    {
        timerCount = 0;

        P1OUT ^= 0x01;

        // Wake up MCU
        __bic_SR_register_on_exit(LPM0_bits);
    }
}
