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
#include <math.h>					// for: M_PI
#include "_guiapp.h"
#include "_swv.h"

#define USE_HMI_LEFT 							1

// macro to manipulate bit
#define SetBit(x) 								(1 << x)
#define SetBitOf(var, x) 					(var |= 1 << x)
#define ClearBitOf(var, x) 				(var &= ~(1 << x))
#define ToggleBitOf(var, x) 			(number ^= 1 << x)

// list event
#define EVENT_CAN_RX_IT						SetBit(0)

// internal USART LCD protocol
#define CMD_RESET_BUFFER						'X'
#define CMD_LEFT_SEIN_ON						'A'
#define CMD_LEFT_SEIN_ON_ACK				'B'

// Function prototype
void BSP_Led_Write(uint8_t number, uint8_t state);
void BSP_Led_Toggle(uint8_t number);
void BSP_Set_Backlight(uint8_t state);
float D2R(uint16_t deg);

#endif /* CONFIG_H_ */
