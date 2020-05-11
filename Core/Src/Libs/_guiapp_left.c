/*
 * _guiapp_left.c
 *
 *  Created on: Mar 11, 2020
 *      Author: pudja
 */
/* Includes ------------------------------------------------------------------*/
#include "_guiapp_left.h"
#include "HMI1.h"
#include "VCU.h"
#include "MCU.h"

#if USE_HMI_LEFT
/* External variables ---------------------------------------------------------*/
extern GUI_CONST_STORAGE GUI_BITMAP bmHMI_Left;
extern GUI_CONST_STORAGE GUI_BITMAP bmHMI_Left_Finger;
extern GUI_CONST_STORAGE GUI_BITMAP bmHMI_Left_Keyless;
extern GUI_CONST_STORAGE GUI_BITMAP bmHMI_Left_Mirror;
extern GUI_CONST_STORAGE GUI_BITMAP bmHMI_Left_Sein;
extern GUI_CONST_STORAGE GUI_BITMAP bmHMI_Left_Trip_A;
extern GUI_CONST_STORAGE GUI_BITMAP bmHMI_Left_Trip_B;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontSquare721_BT23;
extern hmi1_t HMI1;
extern vcu_t VCU;
extern mcu_t MCU;

/* Global Variables -----------------------------------------------------------*/
display_t DISPLAY = {
		.background = &bmHMI_Left,
		.overlay = {
				.points = {
						{ 300, 66 },
						{ 257, 66 },
						{ 230, 39 },
						{ 144, 39 },
						{ 87, 66 },
						{ 39, 175 },
						{ 55, 205 },
						{ 215, 205 },
						{ 250, 153 },
						{ 300, 153 }
				},
				.count = 10
		}
};

/* Private Variables ---------------------------------------------------------*/
static GUI_MEMDEV_Handle hMem;
static rect_t RECT = {
		.trip = {
				.total = { 156, 106, 156 + 66, 106 + 24 },
				.sub = { 156, 83, 156 + 66, 83 + 24 }
		}
};
static collection_t COL = {
		.x = 58,
		.y = 161,
		.r = 123,
		.h = 7,
		.max = 112
};

/* Functions -----------------------------------------------------------------*/
void LEFT_Animation(void) {
	uint16_t k;

	for (k = 0; k <= 40; k++) {
		GUI_FillRect(320 - 20 - k, 120 - 1, 320 - 20, 170);
		osDelay(20);
	}
	for (k = 0; k <= 180; k++) {
		GUI_DrawPie(320 - 60, 120 - 1, 250, 270 - k, 270, 0);
		osDelay(10);
	}
	for (k = 0; k <= 40; k++) {
		GUI_FillRect(320 - 60, 50, 320 - 60 + k, 120 - 1);
		osDelay(20);
	}
}

void LEFT_MemGroupEnter(void) {
	GUI_SelectLayer(1);
	hMem = GUI_MEMDEV_Create(
			COL.x,
			COL.y - COL.r,
			COL.x + COL.r + (COL.r * cos(_D2R(COL.max + 180))) + 5 - COL.x + 25,
			COL.y + COL.h + 5 - (COL.y - COL.r));

	// MEMDEV: Draw to MEM
	GUI_MEMDEV_Select(hMem);
	GUI_DrawBitmapEx(DISPLAY.background, COL.x, COL.y - COL.r, COL.x, COL.y - COL.r, 1000, 1000);
}

void LEFT_MemGroupExit(void) {
	// MEMDEV: Print result to LCD
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_CopyToLCD(hMem);
	GUI_MEMDEV_Delete(hMem);
}

void LEFT_Sein(void) {
	_GUI_IconMem(275, 84, &bmHMI_Left_Sein, HMI1.d.status.sein_left, 200);
}

void LEFT_Finger(void) {
	_GUI_IconMem(293, 127, &bmHMI_Left_Finger, HMI1.d.status.finger, 200);
}

void LEFT_Mirror(void) {
	_GUI_IconMem(261, 129, &bmHMI_Left_Mirror, HMI1.d.status.mirror, 200);
}

void LEFT_Keyless(void) {
	_GUI_Icon(228, 133, &bmHMI_Left_Keyless, HMI1.d.status.keyless, 200);
}

void LEFT_Odometer(void) {
	char str[20];

	// Drawing
	GUI_SetColor(GUI_MAIN_COLOR);
	GUI_SetFont(&GUI_FontSquare721_BT23);
	sprintf(str, "%05u", (unsigned int) VCU.d.odometer);
	GUI_DispStringInRectWrap(str, &(RECT.trip.total),
	GUI_TA_BOTTOM | GUI_TA_RIGHT, GUI_WRAPMODE_NONE);

}

void LEFT_ModeTrip(void) {
	char str[20];
	uint8_t show;
	GUI_CONST_STORAGE GUI_BITMAP *pImage;

	// Decide the image
	if (HMI1.d.mode.sel == SW_M_TRIP) {
		if (HMI1.d.mode.trip.sel == SW_M_TRIP_A) {
			pImage = &bmHMI_Left_Trip_A;
		} else {
			pImage = &bmHMI_Left_Trip_B;
		}
	}

	// Mode Trip Label
	show = HMI1.d.mode.sel == SW_M_TRIP && !HMI1.d.mode.hide;
	_GUI_Icon(129, 89, pImage, show, 254);

	// Mode Trip Value
	GUI_SetColor(GUI_MAIN_COLOR);
	GUI_SetFont(&GUI_FontSquare721_BT23);
	sprintf(str, "%05u", (unsigned int) HMI1.d.mode.trip.val);
	GUI_DispStringInRectWrap(str, &(RECT.trip.sub),
	GUI_TA_BOTTOM | GUI_TA_RIGHT, GUI_WRAPMODE_NONE);

}

void LEFT_Needle(void) {
	uint8_t deg = MCU.d.rpm <= MCU_RPM_MAX ? (MCU.d.rpm * COL.max / MCU_RPM_MAX) : COL.max;
	GUI_POINT pNeedle[] = {
			{
					(COL.x + COL.r) + (((COL.h / 2) + 1) * cos(_D2R(deg + 270))),
					(COL.y + (COL.h / 2) + 1) + (((COL.h / 2) + 1) * sin(_D2R(deg + 270)))
			}, // top
			{
					(COL.x + COL.r) + (COL.r * cos(_D2R(deg + 180))),
					(COL.y + (COL.h / 2) + 1) + (COL.r * sin(_D2R(deg + 180)))
			}, // corner
			{
					(COL.x + COL.r) + (((COL.h / 2) + 1) * cos(_D2R(deg + 90))),
					(COL.y + (COL.h / 2) + 1) + (((COL.h / 2) + 1) * sin(_D2R(deg + 90)))
			} // bottom
	};

	// Drawing
	GUI_SetColor(GUI_RED);
	GUI_AA_SetFactor(6);
	GUI_SetAlpha(205);
	GUI_AA_FillPolygon(pNeedle, GUI_COUNTOF(pNeedle), 0, 0);
	GUI_SetAlpha(255);
	GUI_AA_FillCircle(COL.x + COL.r, COL.y + (COL.h / 2) + 1, (COL.h / 2) + 2);
	GUI_AA_SetFactor(1);
}

#endif
