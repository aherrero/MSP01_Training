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
    P1DIR |= 0x01;                          // Set P1.0 to output direction
    P1OUT = 0x00;                           // Set power OFF all pin of P1
    // P1OUT |= 0x01;                          // Turn ON only the P1.0
}

void LedToogle(void)
{
    P1OUT ^= 0x01;                      // Toogle the P1.0 pin
}
