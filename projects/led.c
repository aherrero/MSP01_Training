/*
 * led.c
 *
 *  Created on: Nov 24, 2019
 *      Author: aherrero
 */

#include <msp430.h>
#include <msp430fr2355.h>

#include "led.h"

void LedInit(void)
{
    // Dir
    P1DIR |= BIT4;
    P5DIR |= 0x000A;    //BIT3 & BIT1

    // Output zero
    LedOneOff();
    LedTwoOff();
    LedThreeOff();
}

void LedToogle(void)
{
    P1OUT ^= 0x01;                      // Toogle the P1.0 pin
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
