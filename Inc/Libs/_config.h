/*
 * _config.h
 *
 *  Created on: Aug 26, 2019
 *      Author: Puja
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include "main.h"
#include <stdlib.h>				// for: itoa()
#include <stdio.h>				// for: sprintf()
#include "_guiapp.h"
#include "_swv.h"

#define USE_HMI_LEFT 					0

// macro to manipulate bit
#define SetBit(x) 								(1 << x)
#define SetBitOf(var, x) 					(var |= 1 << x)
#define ClearBitOf(var, x) 				(var &= ~(1 << x))
#define ToggleBitOf(var, x) 			(number ^= 1 << x)

// list event
#define EVENT_CAN_RX_IT							SetBit(0)

// Function prototype
void BSP_Led_Write(uint8_t number, uint8_t state);
void BSP_Led_Toggle(uint8_t number);
void BSP_Set_Backlight(uint8_t state);

#endif /* CONFIG_H_ */