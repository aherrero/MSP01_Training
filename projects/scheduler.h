/*
 * scheduler.h
 *
 *  Created on: Nov 24, 2019
 *      Author: aherrero
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

typedef struct Task_t
{
    void (*TaskFunction)(void);   // Function that task executes
    unsigned long Period;       // How often the test happens
    unsigned char Repeat;       // If task should repeat
    unsigned long ElapsedTime;  // Keep time how many timer ticks have elapsed
} Task_t;

void SchedulerCreateTask(void (*Func)(void), int Period_s, unsigned Repeat);

void SchedulerExecuteTask(void);

#endif /* SCHEDULER_H_ */
