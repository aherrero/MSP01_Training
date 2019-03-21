/*
 * timer.c
 *
 *  Created on: Mar 21, 2019
 *      Author: aherrero
 */
#include "timer.h"
#include <msp430.h>
#include <msp430fr2355.h>

#include "led.h"

extern unsigned char ledToogleFlag; //Extern allow tof using this global in main

unsigned int timerCount = 0;    // Keep track of timer ticks

void timer_init()
{
    // Timer1_B3 setup
    TB1CCTL0 = CCIE;                        // CCIE = 0x0010, TBCCR0 interrupt enabled
    TB1CCR0 = 4096;                         // Set capture and control threshold to 1/8 of 32kHz clock
    TB1CTL = TBSSEL_1 | MC_1 | TBCLR;       // TBSSEL_1 = 0x0100 -> ACLK
                                            // MC_1 = 0x0010 -> up mode
                                            // TBCLR = 0x0004 -> Clear the timer;
    return;
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

        ledToogleFlag = 1;

        // Wake up MCU
        __bic_SR_register_on_exit(LPM0_bits);
    }
}
