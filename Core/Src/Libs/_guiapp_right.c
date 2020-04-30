/*
 * _guiapp_right.c
 *
 *  Created on: Mar 11, 2020
 *      Author: pudja
 */
/* Includes ------------------------------------------------------------------*/
#include "_guiapp_right.h"

#if !USE_HMI_LEFT
/* External variables ------------------------------------------------------------------*/
extern GUI_CONST_STORAGE GUI_BITMAP bmHMI_Right_Abs;
extern GUI_CONST_STORAGE GUI_BITMAP bmHMI_Right_Warning;
extern GUI_CONST_STORAGE GUI_BITMAP bmHMI_Right_Temp;
extern GUI_CONST_STORAGE GUI_BITMAP bmHMI_Right_Lamp;
extern GUI_CONST_STORAGE GUI_BITMAP bmHMI_Right_Sein;
extern GUI_CONST_STORAGE GUI_BITMAP bmHMI_Right_Battery_Full;
extern GUI_CONST_STORAGE GUI_BITMAP bmHMI_Right_Battery_Low;
extern GUI_CONST_STORAGE GUI_BITMAP bmHMI_Right;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontSquare721_BT10;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontSquare721_BT14;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontSquare721_BT17;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontSquare721_BT31;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontSquare721_BT60;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontSquare721_Cn_BT62;
extern db_t DB;

/* Variables ------------------------------------------------------------------*/
guiapp_t GAPP = {
		.background = &bmHMI_Right,
		.overlay = {
				.points = {
						{ LCD_SIZE_X - 300, 66 },
						{ LCD_SIZE_X - 257, 66 },
						{ LCD_SIZE_X - 230, 39 },
						{ LCD_SIZE_X - 144, 39 },
						{ LCD_SIZE_X - 87, 66 },
						{ LCD_SIZE_X - 87, 66 },
						{ 273, 135 },
						{ 275, 140 },
						{ LCD_SIZE_X - 39, 175 },
						{ LCD_SIZE_X - 55, 205 },
						{ 150, 205 },
						{ 175, 180 },
						{ 170, 145 },
						{ 150, 128 },
						{ 120, 128 },
						{ 100, 150 },
						{ 100, 180 },
						{ 120, 205 },
						{ LCD_SIZE_X - 215, 205 },
						{ LCD_SIZE_X - 250, 153 },
						{ LCD_SIZE_X - 300, 153 }
				},
				.count = 21
		}
};

rect_t RECT = {
		.speed = { 83, 79, 85 + 102, 79 + 50 },
		.signal = { 122, 50, 122 + 65, 50 + 10 },
		.drive = { 126, 145, 126 + 26, 145 + 40 },
		.battery = {
				.value = { 227, 164, 227 + 35, 164 + 28 },
				.unit = { 266, 170, 266 + 17, 170 + 17 }
		},
		.report = {
				.mode = { 174 + (-10), 191, 174 + 50 + (-10), 191 + 13 },
				.value = { 228 + (-10), 190, 228 + 20 + (-10), 190 + 15 },
				.unit = { 251 + (-10), 194, 251 + 28 + (-10), 194 + 10 }
		}
};

collection_t COL = {
		.drive = {
				.mode = { 'E', 'S', 'P', 'R' }
		},
		.report = {
				.mode = { "Range", "Average" },
				.unit = { "KM", "KM/KWh" },
		}
};

/* Functions -----------------------------------------------------------------*/
void RIGHT_Animation(void) {
	uint16_t k;

	for (k = 0; k <= 40; k++) {
		GUI_FillRect(20, 120 - 1, 20 + k, 170);
		osDelay(20);
	}
	for (k = 0; k <= 180; k++) {
		GUI_DrawPie(60, 120 - 1, 250, 270, 270 + k, 0);
		osDelay(10);
	}
	for (k = 0; k <= 40; k++) {
		GUI_FillRect(60 - k, 50, 60, 120 - 1);
		osDelay(20);
	}
}

void RIGHT_Sein(void) {
	_GUI_IconMem(20, 83, &bmHMI_Right_Sein, DB.hmi1.status.sein_right, 200);
}

void RIGHT_Warning(void) {
	_GUI_IconMem(4, 130, &bmHMI_Right_Warning, DB.hmi1.status.warning, 200);
}

void RIGHT_ABS(void) {
	_GUI_IconMem(63, 135, &bmHMI_Right_Abs, DB.hmi1.status.abs, 200);
}

void RIGHT_Overheat(void) {
	_GUI_IconMem(34, 131, &bmHMI_Right_Temp, DB.hmi1.status.overheat, 200);
}

void RIGHT_Lamp(void) {
	_GUI_IconMem(190, 136, &bmHMI_Right_Lamp, DB.hmi1.status.lamp, 200);
}

void RIGHT_Speed(void) {
	char str[20];

	// create & select MEMDEV
	GUI_SelectLayer(1);
	GUI_MEMDEV_Handle hMem = GUI_MEMDEV_Create(
			RECT.speed.x0, RECT.speed.y0,
			RECT.speed.x1, RECT.speed.y1);
	GUI_MEMDEV_Select(hMem);

	// Drawing
	GUI_SetColor(GUI_MAIN_COLOR);
	GUI_SetFont(&GUI_FontSquare721_BT60);
	sprintf(str, "%03u", DB.vcu.speed);
	GUI_DispStringInRectWrap(str, &(RECT.speed),
	GUI_TA_BOTTOM | GUI_TA_RIGHT, GUI_WRAPMODE_NONE);

	// Print result & delete MEMDEV
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_CopyToLCD(hMem);
	GUI_MEMDEV_Delete(hMem);
}

void RIGHT_Signal(void) {
	// create & select MEMDEV
	GUI_SelectLayer(1);
	GUI_MEMDEV_Handle hMem = GUI_MEMDEV_Create(
			RECT.signal.x0, RECT.signal.y0,
			RECT.signal.x1, RECT.signal.y1);
	GUI_MEMDEV_Select(hMem);

	// Drawing
	GUI_SetColor(GUI_MAIN_COLOR);
	GUI_SetBkColor(GUI_BLACK);
	_GUI_ClearRect(&(RECT.signal));
	// clear some transparent
	GUI_SetBkColor(GUI_TRANSPARENT);
	GUI_ClearRect(
			RECT.signal.x0,
			RECT.signal.y0,
			RECT.signal.x0 + (DB.vcu.signal * (RECT.signal.x1 - RECT.signal.x0) / 100),
			RECT.signal.y1);
	// reset the bg color
	GUI_SetBkColor(GUI_BLACK);

	// Print result & delete MEMDEV
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_CopyToLCD(hMem);
	GUI_MEMDEV_Delete(hMem);
}

void RIGHT_Battery(void) {
	char str[20];
	static uint8_t show = 0;
	static uint32_t tick = 0;
	GUI_CONST_STORAGE GUI_BITMAP *pImage;

	// Detect trigger event
	if (DB.bms.soc <= 20) {
		GUI_SetColor(0xFFE62129);
		pImage = &bmHMI_Right_Battery_Low;
		// decide time to blink
		if (osKernelGetTickCount() - tick > pdMS_TO_TICKS(500)) {
			show = !show;
			tick = osKernelGetTickCount();
		}
	} else {
		GUI_SetColor(GUI_MAIN_COLOR);
		pImage = &bmHMI_Right_Battery_Full;
		// always show
		show = 1;
	}

	// Battery Icon
	_GUI_IconMem(195, 170, pImage, show, 200);

	// create & select MEMDEV
	GUI_SelectLayer(1);
	GUI_MEMDEV_Handle hMem = GUI_MEMDEV_Create(RECT.battery.unit.x0,
			RECT.battery.unit.y0, RECT.battery.unit.x1, RECT.battery.unit.y1);
	GUI_MEMDEV_Handle hMem1 = GUI_MEMDEV_Create(RECT.battery.value.x0,
			RECT.battery.value.y0, RECT.battery.value.x1,
			RECT.battery.value.y1);

	// Battery Unit
	GUI_MEMDEV_Select(hMem);
	_GUI_ClearRect(&(RECT.battery.unit));
	GUI_SetFont(&GUI_FontSquare721_BT17);
	GUI_DispStringInRectWrap("%", &(RECT.battery.unit),
	GUI_TA_BOTTOM | GUI_TA_LEFT, GUI_WRAPMODE_NONE);
	GUI_SetColor(GUI_MAIN_COLOR);

	// Battery Value
	GUI_MEMDEV_Select(hMem1);
	GUI_SetFont(&GUI_FontSquare721_BT31);
	sprintf(str, "%02u", DB.bms.soc);
	GUI_DispStringInRectWrap(str, &(RECT.battery.value),
	GUI_TA_BOTTOM | GUI_TA_RIGHT, GUI_WRAPMODE_NONE);

	// Print result & delete MEMDEV
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_CopyToLCD(hMem);
	GUI_MEMDEV_CopyToLCD(hMem1);
	GUI_MEMDEV_Delete(hMem);
	GUI_MEMDEV_Delete(hMem1);
}

void RIGHT_ModeReport(void) {
	char str[20];

	// create & select MEMDEV
	GUI_SelectLayer(1);
	GUI_MEMDEV_Handle hMem = GUI_MEMDEV_Create(RECT.report.unit.x0,
			RECT.report.unit.y0, RECT.report.unit.x1, RECT.report.unit.y1);
	GUI_MEMDEV_Handle hMem1 = GUI_MEMDEV_Create(RECT.report.mode.x0,
			RECT.report.mode.y0, RECT.report.mode.x1, RECT.report.mode.y1);
	GUI_MEMDEV_Handle hMem2 = GUI_MEMDEV_Create(RECT.report.value.x0,
			RECT.report.value.y0, RECT.report.value.x1, RECT.report.value.y1);

	// Drawing
	GUI_SetColor(GUI_MAIN_COLOR);

	// Mode Report: Unit
	GUI_MEMDEV_Select(hMem);
	_GUI_ClearRect(&(RECT.report.unit));
	GUI_SetFont(&GUI_FontSquare721_BT10);
	sprintf(str, "%s", COL.report.unit[DB.hmi1.mode.report.sel]);
	GUI_DispStringInRectWrap(str, &(RECT.report.unit),
	GUI_TA_BOTTOM | GUI_TA_LEFT, GUI_WRAPMODE_NONE);

	// Mode Report: Label
	GUI_MEMDEV_Select(hMem1);
	_GUI_ClearRect(&(RECT.report.mode));
	if (DB.hmi1.mode.sel == SW_M_REPORT && !DB.hmi1.mode.hide) {
		GUI_SetFont(&GUI_FontSquare721_BT14);
		sprintf(str, "%s", COL.report.mode[DB.hmi1.mode.report.sel]);
		GUI_DispStringInRectWrap(str, &(RECT.report.mode),
		GUI_TA_BOTTOM | GUI_TA_RIGHT, GUI_WRAPMODE_NONE);
	}

	// Mode Report: Value
	GUI_MEMDEV_Select(hMem2);
	GUI_SetFont(&GUI_FontSquare721_BT17);
	sprintf(str, "%02u", DB.hmi1.mode.report.val);
	GUI_DispStringInRectWrap(str, &(RECT.report.value),
	GUI_TA_BOTTOM | GUI_TA_RIGHT, GUI_WRAPMODE_NONE);

	// Print result & delete MEMDEV
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_CopyToLCD(hMem);
	GUI_MEMDEV_CopyToLCD(hMem1);
	GUI_MEMDEV_CopyToLCD(hMem2);
	GUI_MEMDEV_Delete(hMem);
	GUI_MEMDEV_Delete(hMem1);
	GUI_MEMDEV_Delete(hMem2);
}

void RIGHT_ModeDrive(void) {
	char str[20];

	// create & select MEMDEV
	GUI_SelectLayer(1);
	GUI_MEMDEV_Handle hMem = GUI_MEMDEV_Create(RECT.drive.x0, RECT.drive.y0,
			RECT.drive.x1, RECT.drive.y1);

	// Drawing
	GUI_SetColor(GUI_MAIN_COLOR);

	// Drive Mode
	_GUI_ClearRect(&(RECT.drive));
	if (DB.hmi1.mode.sel == SW_M_DRIVE && !DB.hmi1.mode.hide) {
		// if reverse, change color
		if (DB.hmi1.mode.drive == SW_M_DRIVE_R) {
			GUI_SetColor(0xFFFF8000);
		}
		GUI_SetFont(&GUI_FontSquare721_Cn_BT62);
		sprintf(str, "%c", COL.drive.mode[DB.hmi1.mode.drive]);
		GUI_DispStringInRectWrap(str, &(RECT.drive),
		GUI_TA_VCENTER | GUI_TA_HCENTER, GUI_WRAPMODE_NONE);
	}

	// Print result & delete MEMDEV
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_CopyToLCD(hMem);
	GUI_MEMDEV_Delete(hMem);
}
#endif
