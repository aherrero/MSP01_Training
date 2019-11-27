/*
 * timer.c
 *
 *  Created on: Nov 24, 2019
 *      Author: aherrero
 */

#include "timer.h"
#include <msp430.h>
#include <msp430fr2355.h>

unsigned int g_TimerCount = 0;

extern unsigned char g_LedDebugToogleFlag;       // Declared in main
extern unsigned char g_ExecuteTaskFlag;     // Declared in main

void TimerInit(void)
{
    const int timer_tick = g_TimerB0Frequency*g_TimerB0Configuration_ms/1000.0;

    TB0CTL |= 0x0100;                       // TASSEL to ACLK (0x01)
    TB0CTL |= 0x0010;                       // MC to Up Mode (0x01)
    TB0CTL |= 0x0004;                       // TBCLR to 1, clear the timer. (0x04);

    TB0CCR0 |= timer_tick;                  // Set capture. Source = 32768Hz ticks each second.
                                            // For 1/4 seconds 32768/4 = 8192;
                                            // For 1/8 seconds, 32768/8 = 4046;

    TB0CCTL0 |= 0x0010;                     // CCIE enable (Enable interruption each end counter)
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
    // Increase counter
    g_TimerCount++;

    // debug function
    if(g_TimerCount >= g_TimerB0TicksEachSecond)  // Interruption called each 1/8 seconds. After 8 calls, enter in this function to toggle the led.
    {
        g_TimerCount = 0;
        g_LedDebugToogleFlag = 1;                // Set the flag to 1, so the main function will call the toogle led function
    }

    // Scheduler flag
    g_ExecuteTaskFlag = 1;

    // Wake up
    __bic_SR_register_on_exit(LPM0_bits);
}

