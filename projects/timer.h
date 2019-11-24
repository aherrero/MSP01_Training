/*
 * timer.h
 *
 *  Created on: Nov 24, 2019
 *      Author: aherrero
 */

#ifndef TIMER_H_
#define TIMER_H_

static const long g_TimerB0Frequency = 32768;
static const int g_TimerB0Configuration_ms = 125;
static const int g_TimerB0TicksEachSecond = 1 / (g_TimerB0Configuration_ms/1000.0);     // 8 ticks

void TimerInit(void);


#endif /* TIMER_H_ */
