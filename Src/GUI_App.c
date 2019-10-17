/**
 ******************************************************************************
 * @file    GUI_App.c
 * @author  MCD Application Team
 * @brief   Simple demo drawing "Hello world"
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright © 2018 STMicroelectronics International N.V.
 * All rights reserved.</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted, provided that the following conditions are met:
 *
 * 1. Redistribution of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of other
 *    contributors to this software may be used to endorse or promote products
 *    derived from this software without specific written permission.
 * 4. This software, including modifications and/or derivative works of this
 *    software, must execute solely and exclusively on microcontroller or
 *    microprocessor devices manufactured by or for STMicroelectronics.
 * 5. Redistribution and use of this software other than as permitted under
 *    this license is void and will automatically terminate your rights under
 *    this license.
 *
 * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
 * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
 * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */
#define HMI_Left 1

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "GUI_App.h"
#include "GUI.h"
#include <stdio.h>				// for: sprintf()
#include <string.h>				// for: strlen()
#include <math.h>					// for: sin(), cos()
#if (HMI_Left == 1)
#include "HMI_Left.c"
#else
#include "HMI_Right.c"
#endif

/* Functions prototypes --------------------------------------------------------*/
float D2R(uint16_t deg);
void Set_Indikator(GUI_CONST_STORAGE GUI_BITMAP *bg, GUI_RECT *pRect, GUI_CONST_STORAGE GUI_BITMAP *fg, uint16_t x, uint16_t y,
		uint8_t status, uint8_t alpha);
#if (HMI_Left == 1)
void Set_Left_Sein(uint8_t status, uint32_t *tick);
void Set_Left_Temp(uint8_t status);
void Set_Left_Lamp(uint8_t status);
void Set_Left_Jarum(uint8_t deg, uint16_t x, uint16_t y, uint16_t r, uint16_t h, uint8_t max);
void Set_Left_Trip(char mode);
#else
void Set_Right_Sein(uint8_t status, uint32_t *tick);
void Set_Right_Warning(uint8_t status);
void Set_Right_Abs(uint8_t status);
#endif

/* Main task ------------------------------------------------------------------*/
void GRAPHICS_MainTask(void) {
	/* USER CODE BEGIN GRAPHICS_MainTask */
	char str[20];

	GUI_SelectLayer(1);
	GUI_SetBkColor(GUI_TRANSPARENT);
	GUI_Clear();

	GUI_SelectLayer(0);
#if (HMI_Left == 1)
	GUI_DrawBitmap(&bmHMI_Left, 0, 0);
	const GUI_POINT aPoints[] = { { 300, 66 }, { 257, 66 }, { 230, 39 }, { 144, 39 }, { 87, 66 }, { 39, 175 }, { 55, 205 }, { 215, 205 }, {
			250, 153 }, { 300, 153 } };
#else
	GUI_DrawBitmap(&bmHMI_Right, 0, 0);
	const GUI_POINT aPoints[] = {
			{ LCD_GetXSize() - 1 - 300, 66},
			{ LCD_GetXSize() - 1 - 257, 66},
			{ LCD_GetXSize() - 1 - 230, 39},
			{ LCD_GetXSize() - 1 - 144, 39},
			{ LCD_GetXSize() - 1 - 87, 66},
			{ LCD_GetXSize() - 1 - 87, 66},
			{ 273, 135},
			{ 275, 140},
			{ LCD_GetXSize() - 1 - 39, 175},
			{ LCD_GetXSize() - 1 - 55, 205},
			{150, 205},
			{175, 180},
			{170, 145},
			{150, 128},
			{120, 128},
			{100, 150},
			{100, 180},
			{120, 205},
			{ LCD_GetXSize() - 1 - 215, 205},
			{ LCD_GetXSize() - 1 - 250, 153},
			{ LCD_GetXSize() - 1 - 300, 153}
	};
#endif
	// overlay for first booting
	GUI_SetColor(GUI_BLACK);
	GUI_FillPolygon(aPoints, GUI_COUNTOF(aPoints), 0, 0);
	// start of booting animation
	GUI_SelectLayer(1);
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	// start of circular booting animation
	uint16_t k;
	GUI_SetColor(GUI_TRANSPARENT);
#if (HMI_Left == 1)
	for (k = 0; k <= 20; k++) {
		GUI_FillRect(320 - 40 - k, 120 - 1, 320 - 40, 170);
		GUI_Delay(20);
	}
	for (k = 0; k <= 180; k++) {
		GUI_DrawPie(320 - 60, 120 - 1, 250, 270 - k, 270, 0);
		GUI_Delay(10);
	}
	for (k = 0; k <= 20; k++) {
		GUI_FillRect(320 - 60, 50, 320 - 60 + k, 120 - 1);
		GUI_Delay(20);
	}
#else
	//	for(k = 0; k <= 360; k++){
	//		GUI_DrawPie(139, 165, 33, 180, 180+k, 0);
	//		GUI_Delay(2);
	//	}
	for(k=0; k<=20; k++){
		GUI_FillRect(40, 120-1, 40+k, 170);
		GUI_Delay(20);
	}
	for(k = 0; k <= 180; k++){
		GUI_DrawPie(60, 120-1, 250, 270, 270+k, 0);
		GUI_Delay(10);
	}
	for(k=0; k<=20; k++){
		GUI_FillRect(60-k, 50, 60, 120-1);
		GUI_Delay(20);
	}
#endif
	// end of booting animation

	GUI_SelectLayer(0);
#if (HMI_Left == 1)
	GUI_DrawBitmap(&bmHMI_Left, 0, 0);
	GUI_RECT pRect_SubTrip = { 159, 84, 159 + 64, 84 + 24 };
	GUI_RECT pRect_TotalTrip = { 159, 107, 159 + 64, 107 + 24 };

	GUI_SelectLayer(1);
	uint16_t x = 58, y = 161, r = 123, h = 7;
	uint8_t max = 112;
	GUI_MEMDEV_Handle hMem = GUI_MEMDEV_Create(x, y - r, x + r + (r * cos(D2R(max + 180))) + 5 - (x), y + h + 5 - (y - r));
#else
	GUI_DrawBitmap(&bmHMI_Right, 0, 0);
	GUI_RECT pRect_Speed = {85, 79, 85+100, 79+41};
	GUI_RECT pRect_Battery = {227, 164, 227+35, 164+28};
	GUI_RECT pRect_Range = {235, 188, 235+20, 188+15};
	GUI_RECT pRect_Temp = {178, 132, 178+32, 132+22};
	GUI_RECT pRect_Datetime = {65, 48, 65+150, 48+16};
	GUI_RECT pRect_Drive = {126, 145, 126+26, 145+40};
	char Drive_Mode[4] = {'E', 'S', 'C', 'P'};
#endif
	GUI_Delay(500);

	GUI_SelectLayer(1);
	GUI_SetBkColor(GUI_TRANSPARENT);
	GUI_Clear();
	GUI_SetBkColor(GUI_BLACK);

	uint32_t i = 0;
	uint32_t tick = osKernelSysTick();
	while (1) {

#if (HMI_Left == 1)
		Set_Left_Sein(1, &tick);
		Set_Left_Temp((i / 20) % 2);
		Set_Left_Lamp((i / 15) % 2);

		GUI_MEMDEV_Select(hMem);
		GUI_DrawBitmapEx(&bmHMI_Left, x, y - r, x, y - r, 1000, 1000);

		GUI_SetColor(0xFFC0C0C0);
		GUI_SetFont(&GUI_FontSquare721_BT23);
		sprintf(str, "%lu", i);
		GUI_DispStringInRectWrap(str, &pRect_SubTrip, GUI_TA_VCENTER | GUI_TA_RIGHT, GUI_WRAPMODE_NONE);

		GUI_SetFont(&GUI_FontSquare721_BT23);
		sprintf(str, "%lu", i * 90);
		GUI_DispStringInRectWrap(str, &pRect_TotalTrip, GUI_TA_VCENTER | GUI_TA_RIGHT, GUI_WRAPMODE_NONE);

		Set_Left_Trip('A');
		Set_Left_Jarum(i - (i / max * max), x, y, r, h, max);
		// Print result to LCD
		GUI_MEMDEV_Select(0);
		GUI_MEMDEV_CopyToLCD(hMem);

#else
		Set_Right_Sein(1, &tick);
		Set_Right_Warning((i/600)%2);
		Set_Right_Abs((i/900)%2);

		GUI_SetFont(&GUI_FontSquare721_BT60);
		sprintf(str, "%lu", i);
		GUI_DispStringInRectWrap(str, &pRect_Speed, GUI_TA_VCENTER | GUI_TA_RIGHT, GUI_WRAPMODE_NONE);

		GUI_SetFont(&GUI_FontSquare721_BT31);
		sprintf(str, "%lu", i/20);
		GUI_DispStringInRectWrap(str, &pRect_Battery, GUI_TA_VCENTER | GUI_TA_RIGHT, GUI_WRAPMODE_NONE);

		GUI_SetFont(&GUI_FontSquare721_BT17);
		sprintf(str, "%lu", i/30);
		GUI_DispStringInRectWrap(str, &pRect_Range, GUI_TA_VCENTER | GUI_TA_RIGHT, GUI_WRAPMODE_NONE);

		GUI_SetFont(&GUI_FontSquare721_BT30);
		sprintf(str, "%lu", i/40);
		GUI_DispStringInRectWrap(str, &pRect_Temp, GUI_TA_VCENTER | GUI_TA_RIGHT, GUI_WRAPMODE_NONE);

		GUI_SetFont(&GUI_FontSquare721_BT16);
		GUI_DispStringInRectWrap("Wed, Oct 10  15:18", &pRect_Datetime, GUI_TA_VCENTER | GUI_TA_RIGHT, GUI_WRAPMODE_NONE);

		GUI_SetFont(&GUI_FontSquare721_Cn_BT62);
		sprintf(str, "%c", Drive_Mode[(i/500)%4]);
		GUI_DispStringInRectWrap(str, &pRect_Drive, GUI_TA_VCENTER | GUI_TA_HCENTER, GUI_WRAPMODE_NONE);

#endif

		i++;
		GUI_Delay(1);
	}
	/* USER CODE END GRAPHICS_MainTask */
}

float D2R(uint16_t deg) {
	return deg * M_PI / 180.0;
}

void Set_Indikator(GUI_CONST_STORAGE GUI_BITMAP *bg, GUI_RECT *pRect, GUI_CONST_STORAGE GUI_BITMAP *fg, uint16_t x, uint16_t y,
		uint8_t status, uint8_t alpha) {
	GUI_SetClipRect(pRect);
	GUI_DrawBitmapEx(bg, x, y, x, y, 1000, 1000);
	GUI_SetClipRect(NULL);
	if (status == 1) {
		GUI_SetAlpha(alpha);
		GUI_DrawBitmap(fg, x, y);
		GUI_SetAlpha(255);
	}
}

#if (HMI_Left == 1)

void Set_Left_Sein(uint8_t status, uint32_t *tick) {
	uint16_t x = 277, y = 82;
	static uint8_t stat = 2, toggle = 1;

	GUI_RECT pRect_Left_Sein = { x, y, x + bmHMI_Left_Sein.XSize, y + bmHMI_Left_Sein.YSize };
	if (status == 1) {
		if ((osKernelSysTick() - *tick) >= osKernelSysTickMicroSec(500*1000)) {
			Set_Indikator(&bmHMI_Left, &pRect_Left_Sein, &bmHMI_Left_Sein, x, y, toggle, 200);
			toggle = !toggle;
			*tick = osKernelSysTick();
		}
	} else {
		if (status != stat) {
			Set_Indikator(&bmHMI_Left, &pRect_Left_Sein, &bmHMI_Left_Sein, x, y, 0, 200);
			stat = status;
		}
	}
}

void Set_Left_Temp(uint8_t status) {
	uint16_t x = 285, y = 130;
	static uint8_t stat = 2;

	if (status != stat) {
		GUI_RECT pRect_Left_Temp = { x, y, x + bmHMI_Left_Temp.XSize, y + bmHMI_Left_Temp.YSize };
		Set_Indikator(&bmHMI_Left, &pRect_Left_Temp, &bmHMI_Left_Temp, x, y, status, 200);
		stat = status;
	}
}

void Set_Left_Lamp(uint8_t status) {
	uint16_t x = 267, y = 161;
	static uint8_t stat = 2;

	if (status != stat) {
		GUI_RECT pRect_Left_Lamp = { x, y, x + bmHMI_Left_Lamp.XSize, y + bmHMI_Left_Lamp.YSize };
		Set_Indikator(&bmHMI_Left, &pRect_Left_Lamp, &bmHMI_Left_Lamp, x, y, status, 200);
		stat = status;
	}
}

void Set_Left_Jarum(uint8_t deg, uint16_t x, uint16_t y, uint16_t r, uint16_t h, uint8_t max) {
	GUI_POINT aPoints_Jarum[] = {
			{ (x + r) + (((h / 2) + 1) * cos(D2R(deg + 270))), (y + (h / 2) + 1) + (((h / 2) + 1) * sin(D2R(deg + 270))) }, //atas
			{ (x + r) + (r * cos(D2R(deg + 180))), (y + (h / 2) + 1) + (r * sin(D2R(deg + 180))) }, //ujung
			{ (x + r) + (((h / 2) + 1) * cos(D2R(deg + 90))), (y + (h / 2) + 1) + (((h / 2) + 1) * sin(D2R(deg + 90))) }  //bawah
	};
	GUI_SetColor(GUI_RED);
	GUI_AA_SetFactor(6);
	GUI_SetAlpha(205);
	GUI_AA_FillPolygon(aPoints_Jarum, GUI_COUNTOF(aPoints_Jarum), 0, 0);
	GUI_SetAlpha(255);
	GUI_AA_FillCircle(x + r, y + (h / 2) + 1, (h / 2) + 2);
	GUI_AA_SetFactor(1);
}

void Set_Left_Trip(char mode) {
	uint16_t x = 131, y = 86;
//	static char mod = 'C';

//	if(mode != mod){
	GUI_RECT pRect_Left_Trip = { x, y, x + bmHMI_Left_Trip_A.XSize, y + bmHMI_Left_Trip_A.YSize };
	if (mode == 'A') {
		Set_Indikator(&bmHMI_Left, &pRect_Left_Trip, &bmHMI_Left_Trip_A, x, y, 1, 254);
	} else {
		Set_Indikator(&bmHMI_Left, &pRect_Left_Trip, &bmHMI_Left_Trip_B, x, y, 1, 254);
	}
//		mod = mode;
//	}
}
#else

void Set_Right_Sein(uint8_t status, uint32_t *tick){
	uint16_t x = 20, y = 82;
	static uint8_t stat = 2, toggle = 1;

	GUI_RECT pRect_Right_Sein = {x, y, x + bmHMI_Right_Sein.XSize, y + bmHMI_Right_Sein.YSize};
	if(status == 1){
		if((osKernelSysTick() - *tick) >= osKernelSysTickMicroSec(500*1000)){
			Set_Indikator(&bmHMI_Right, &pRect_Right_Sein, &bmHMI_Right_Sein, x, y, toggle, 200);
			toggle = !toggle;
			*tick = osKernelSysTick();
		}
	} else {
		if(status != stat){
			Set_Indikator(&bmHMI_Right, &pRect_Right_Sein, &bmHMI_Right_Sein, x, y, 0, 200);
			stat = status;
		}
	}
}

void Set_Right_Warning(uint8_t status){
	uint16_t x = 14, y = 130;
	static uint8_t stat = 2;

	if(status != stat){
		GUI_RECT pRect_Right_Warning = {x, y, x + bmHMI_Right_Warning.XSize, y + bmHMI_Right_Warning.YSize};
		Set_Indikator(&bmHMI_Right, &pRect_Right_Warning, &bmHMI_Right_Warning, x, y, status, 200);
		stat = status;
	}
}

void Set_Right_Abs(uint8_t status){
	uint16_t x = 26, y = 161;
	static uint8_t stat = 2;

	if(status != stat){
		GUI_RECT pRect_Right_Abs = {x, y, x + bmHMI_Right_Abs.XSize, y + bmHMI_Right_Abs.YSize};
		Set_Indikator(&bmHMI_Right, &pRect_Right_Abs, &bmHMI_Right_Abs, x, y, status, 200);
		stat = status;
	}
}
#endif
/*************************** End of file ****************************/
