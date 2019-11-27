/*
 * led.c
 *
 *  Created on: Nov 24, 2019
 *      Author: aherrero
 */

#include <msp430.h>
#include <msp430fr2355.h>

#include "led.h"

extern unsigned char g_LedBlinkFlag;
extern unsigned char g_LedBlinkColorRegister;

void LedInit(void)
{
    // Dir
    P1DIR |= BIT0;      // P1.0 debug

    P1DIR |= BIT4;
    P5DIR |= 0x000A;    //BIT3 & BIT1

    // Output zero
    LedClear();
}

void LedDebugToogle(void)
{
    P1OUT ^= 0x01;                      // Toogle the P1.0 pin
}

void LedClear(void)
{
    // Output zero
    LedOneOff();
    LedTwoOff();
    LedThreeOff();

    g_LedBlinkColorRegister = 0;
}

void LedOneBlink(void)
{
    g_LedBlinkColorRegister |= g_LedOne;
    g_LedBlinkFlag = 1;
}

void LedTwoBlink(void)
{
    g_LedBlinkColorRegister |= g_LedTwo;
    g_LedBlinkFlag = 1;
}

void LedThreeBlink(void)
{
    g_LedBlinkColorRegister |= g_LedThree;
    g_LedBlinkFlag = 1;
}

void LedOneOn(void)
{
    // 1.4
    P1OUT |= BIT4;
}

void LedOneOff(void)
{
    P1OUT &= ~BIT4;
}

void LedTwoOn(void)
{
    // 5.3
    P5OUT |= BIT3;
}

void LedTwoOff(void)
{
    P5OUT &= ~BIT3;
}

void LedThreeOn(void)
{
    // 5.1
    P5OUT |= BIT1;
}

void LedThreeOff(void)
{
    P5OUT &= ~BIT1;
}
