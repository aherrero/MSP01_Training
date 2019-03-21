/*
 * led.c
 *
 *  Created on: Mar 21, 2019
 *      Author: aherrero
 */

#include "led.h"
#include <msp430fr2355.h>

void led_toogle()
{
    P1OUT ^= BIT0;  //BIT0 = 0x01 -> Bit 0 for Port 1 tootle (P1.0)
}
