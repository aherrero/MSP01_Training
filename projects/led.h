/*
 * led.h
 *
 *  Created on: Nov 24, 2019
 *      Author: aherrero
 */

#ifndef LED_H_
#define LED_H_

static const unsigned char g_LedOne     = 0x01;
static const unsigned char g_LedTwo     = 0x02;
static const unsigned char g_LedThree   = 0x04;

void LedInit(void);
void LedDebugToogle(void);

void LedClear(void);

void LedOneBlink(void);
void LedTwoBlink(void);
void LedThreeBlink(void);

void LedOneOn(void);
void LedOneOff(void);
void LedTwoOn(void);
void LedTwoOff(void);
void LedThreeOn(void);
void LedThreeOff(void);


#endif /* LED_H_ */
