/*
 * scheduler.c
 *
 *  Created on: Nov 24, 2019
 *      Author: aherrero
 */

#include "scheduler.h"
#include "led.h"

extern struct Task_t g_LedTimingTask;

void SchedulerExecuteTask(void)
{
    g_LedTimingTask.ElapsedTime++;

    if(g_LedTimingTask.ElapsedTime >= g_LedTimingTask.Period)
    {
        LedOneOn();
        LedTwoOn();
        LedThreeOn();
    }
}
