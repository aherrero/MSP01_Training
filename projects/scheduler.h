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
    unsigned long Period;       // How often the test happens
    unsigned long ElapsedTime;  // Keep time how many timer ticks have elapsed
} Task_t;

void SchedulerExecuteTask(void);

#endif /* SCHEDULER_H_ */
