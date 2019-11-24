#include <msp430.h> 
#include <msp430fr2355.h>

#include "timer.h"
#include "led.h"
#include "scheduler.h"

unsigned char g_LedToogleFlag = 0;
unsigned char g_ExecuteTaskFlag = 0;


struct Task_t g_LedTimingTask;

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

    // Task
    g_LedTimingTask.Period = 3 * g_TimerB0TicksEachSecond;  // 3 seconds
    g_LedTimingTask.ElapsedTime = 0;

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

        // Go to sleep until interruption
        __bis_SR_register(LPM0_bits + GIE);
    }

	return 0;
}


