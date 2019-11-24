#include <msp430.h> 
#include <msp430fr2355.h>

#include "timer.h"
#include "led.h"
#include "scheduler.h"

unsigned char g_LedToogleFlag = 0;
unsigned char g_ExecuteTaskFlag = 0;
unsigned char g_LedBlinkFlag = 0;

unsigned char g_LedBlinkColorRegister = 0;

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

    // Create task
    SchedulerCreateTask(LedOneBlink, 1, 1);
    SchedulerCreateTask(LedTwoBlink, 2, 1);
    SchedulerCreateTask(LedThreeBlink, 3, 1);

    // Loop
    while(1)
    {
        // Led debug function
        if(g_LedToogleFlag == 1)
        {
            g_LedToogleFlag = 0;
            LedToogle();
        }

        // Scheduler
        if(g_ExecuteTaskFlag == 1)
        {
            g_ExecuteTaskFlag = 0;
            SchedulerExecuteTask();
        }

        if(g_LedBlinkFlag == 1)
        {
            g_LedBlinkFlag = 0;

            if(g_LedBlinkColorRegister & g_LedOne)
            {
                LedOneOn();
            }

            if(g_LedBlinkColorRegister & g_LedTwo)
            {
                LedTwoOn();
            }

            if(g_LedBlinkColorRegister & g_LedThree)
            {
                LedThreeOn();
            }
        }
        else
        {
            LedClear();
        }

        // Go to sleep until interruption
        __bis_SR_register(LPM0_bits + GIE);
    }

	return 0;
}


