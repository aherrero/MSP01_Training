/*
 * scheduler.c
 *
 *  Created on: Nov 24, 2019
 *      Author: aherrero
 */

#include "scheduler.h"
#include "led.h"
#include "timer.h"

static const unsigned char g_TaskMax = 16;

Task_t TaskList[g_TaskMax];
unsigned char g_TaskCount = 0;

void SchedulerCreateTask(void (*Func)(void), int Period_s, unsigned Repeat)
{
    Task_t task_to_add;
    task_to_add.TaskFunction = Func;
    task_to_add.Period = Period_s * g_TimerB0TicksEachSecond;
    task_to_add.Repeat = Repeat;
    task_to_add.ElapsedTime = 0;

    TaskList[g_TaskCount++] = task_to_add;

}

void SchedulerExecuteTask(void)
{
    unsigned int i;
    for(i = 0; i< g_TaskCount; i++)
    {
        TaskList[i].ElapsedTime++;

        if(TaskList[i].ElapsedTime >= TaskList[i].Period)
        {
            TaskList[i].ElapsedTime = 0;
            TaskList[i].TaskFunction();

            if(TaskList[i].Repeat == 0)
            {
                SchedulerDeleteTask(i);
            }
        }
    }
}

void SchedulerDeleteTask(int index)
{
    unsigned int i;
    for(i = index; i< g_TaskCount - 1; i++)
    {
        TaskList[i] = TaskList[i + 1];
    }
    g_TaskCount--;
}
