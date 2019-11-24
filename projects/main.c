#include <msp430.h> 
#include <msp430fr2355.h>

unsigned int g_TimerCount = 0;

/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings

    // Pin IO
    P1DIR |= 0x01;                          // Set P1.0 to output direction
    P1OUT = 0x00;                           // Set power OFF all pin of P1
    P1OUT |= 0x01;                          // Turn ON only the P1.0

    // Timer
    TB0CTL |= 0x0100;                       // TASSEL to ACLK (0x01)
    TB0CTL |= 0x0010;                       // MC to Up Mode (0x01)
    TB0CTL |= 0x0004;                       // TBCLR to 1, clear the timer. (0x04);

    TB0CCR0 |= 8192;                        // Set capture. Source = 32768Hz ticks each second. For 1/4 seconds 32768/4 = 8192;

    TB0CCTL0 |= 0x0010;                     // CCIE enable (Enable interruption each end counter)

    __bis_SR_register(LPM0_bits + GIE);

	return 0;
}


//******************************************************************************
//
//This is the Timer B0 interrupt vector service routine.
//
//******************************************************************************
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER0_B0_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(TIMER0_B0_VECTOR)))
#endif
void TIMER0_B0_ISR(void)
{
    g_TimerCount++;

    if(g_TimerCount >= 4)                   // Interrpution called each 1/4 seconds. After 4 calls, enter in this function to toggle the led.
    {
        g_TimerCount = 0;
        P1OUT ^= 0x01;                      // Toogle the P1.0 pin
    }
}

