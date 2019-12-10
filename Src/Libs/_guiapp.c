/*
 * _gui.c
 *
 *  Created on: Oct 21, 2019
 *      Author: Puja
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "GUI.h"
#include <stdio.h>				// for: sprintf()
#include <string.h>				// for: strlen()
#include <math.h>					// for: sin(), cos()
#include <limits.h>
#include "_guiapp.h"
#include "_config.h"
#include "_canbus.h"
#include "_database.h"
#if USE_HMI_LEFT
#include "HMI_Left.c"
#else
#include "HMI_Right.c"
#endif

/* External variable */
extern IWDG_HandleTypeDef hiwdg;

/* Functions prototypes --------------------------------------------------------*/
void Set_Default_Data(void);
void Run_Boot_Animation(void);
void Set_Boot_Overlay(void);
void Set_Indicator( GUI_CONST_STORAGE GUI_BITMAP *bg,
GUI_CONST_STORAGE GUI_BITMAP *fg, uint16_t x, uint16_t y, uint8_t status, uint8_t alpha);
#if USE_HMI_LEFT
void Set_Left_Sein(uint8_t status);
void Set_Left_Finger(uint8_t status);
void Set_Left_Mirror(uint8_t status);
void Set_Left_Keyless(uint8_t status);
void Set_Left_Jarum(uint8_t deg, uint16_t x, uint16_t y, uint16_t r, uint16_t h, uint8_t max);
void Set_Left_Trip(switch_mode_trip_t mode_trip);
#else
void Set_Right_Sein(uint8_t status);
void Set_Right_Warning(uint8_t status);
void Set_Right_Abs(uint8_t status);
void Set_Right_Temp(uint8_t status);
void Set_Right_Lamp(uint8_t status);
void Set_Right_Battery(int8_t status);
#endif

/* Main task ------------------------------------------------------------------*/
void GUI_MainTask(void) {
	/* USER CODE BEGIN GUI_MainTask */
	char str[20];
	uint8_t init = 1;
	uint32_t ulNotifiedValue;
	BaseType_t xResult;
	// background
	GUI_CONST_STORAGE GUI_BITMAP *Background;

	extern modes_t DB_HMI_Mode;
	extern status_t DB_HMI_Status;
	status_t DB_HMI_Status_Old;
	modes_t DB_HMI_Mode_Old;

#if USE_HMI_LEFT
	const uint8_t x = 58, y = 161, r = 123, h = 7, max = 112;
	GUI_RECT pRect_SubTrip = { 159, 83, 159 + 64, 83 + 24 };
	GUI_RECT pRect_TotalTrip = { 159, 106, 159 + 64, 106 + 24 };

	extern uint32_t DB_MCU_RPM;
	extern uint32_t DB_ECU_Odometer;
	uint32_t DB_MCU_RPM_Old;
	uint32_t DB_ECU_Odometer_Old;
	uint8_t Mode_Hide_Trip_Old;

	// background
	Background = &bmHMI_Left;
	// create MEMDEV on layer 1
	GUI_SelectLayer(1);
	GUI_MEMDEV_Handle hMem = GUI_MEMDEV_Create(x, y - r, x + r + (r * cos(D2R(max + 180))) + 5 - (x) + 25, y + h + 5 - (y - r));
#else
	int8_t RM_XO = -10;
	GUI_RECT pRect_Speed = { 83, 79, 85 + 102, 79 + 50 };
	GUI_RECT pRect_Battery = { 227, 164, 227 + 35, 164 + 28 };
	GUI_RECT pRect_Battery_Unit = { 266, 170, 266 + 17, 170 + 17 };
	GUI_RECT pRect_Signal = { 122, 50, 122 + 65, 50 + 10 };
	GUI_RECT pRect_Drive = { 126, 145, 126 + 26, 145 + 40 };
	GUI_RECT pRect_Report_Mode = { 174 + RM_XO, 191, 174 + 50 + RM_XO, 191 + 13 };
	GUI_RECT pRect_Report_Value = { 228 + RM_XO, 190, 228 + 20 + RM_XO, 190 + 15 };
	GUI_RECT pRect_Report_Unit = { 251 + RM_XO, 194, 251 + 28 + RM_XO, 194 + 10 };

	const char Drive_Mode[4] = { 'E', 'S', 'P', 'R' };
	const char Report_Mode[2][8] = { "Range", "Average" };
	const char Report_Unit[2][6] = { "KM", "KM/KW" };
	const TickType_t tick500ms = pdMS_TO_TICKS(500);
	TickType_t tickBatteryLow;
	uint8_t Hide_Battery_Low = 0;

	extern uint8_t DB_ECU_Speed;
	extern uint8_t DB_BMS_SoC;
	extern uint8_t DB_ECU_Signal;
	uint8_t DB_ECU_Speed_Old;
	uint8_t DB_BMS_SoC_Old;
	uint8_t DB_BMS_SoC_Low;
	uint8_t DB_BMS_SoC_Update;
	uint8_t DB_ECU_Signal_Old;
	uint8_t Mode_Hide_Drive_Old;
	uint8_t Mode_Hide_Report_Old;

	// background
	Background = &bmHMI_Right;
#endif

	// Set overlay on all indicator on boot
	Set_Boot_Overlay();

	// Run booting animation on start
	Run_Boot_Animation();

	// Draw the layer 0 background
	GUI_SelectLayer(0);
	GUI_DrawBitmap(Background, 0, 0);
	GUI_Delay(500);

	// Make layer 1 transparent
	GUI_SelectLayer(1);
	GUI_SetBkColor(GUI_TRANSPARENT);
	GUI_Clear();
	GUI_SetBkColor(GUI_BLACK);

	while (1) {
		// Feed the dog
		HAL_IWDG_Refresh(&hiwdg);

		if (!init) {
			// check if has new can message
			xResult = xTaskNotifyWait(0x00, ULONG_MAX, &ulNotifiedValue, pdMS_TO_TICKS(500));
		}

		// if not receive any CAN message
		if (xResult == pdFALSE) {
			init = 1;
		}

		// init hook
		if (init) {
			// reset data to default
			Set_Default_Data();
			// set backlight ON
			BSP_Set_Backlight(1);
		}

#if USE_HMI_LEFT

		// Sein Left
		if (DB_HMI_Status_Old.sein_left != DB_HMI_Status.sein_left) {
			DB_HMI_Status_Old.sein_left = DB_HMI_Status.sein_left;
			Set_Left_Sein(DB_HMI_Status.sein_left);
		}

		// Finger
		if (init || DB_HMI_Status_Old.finger != DB_HMI_Status.finger) {
			DB_HMI_Status_Old.finger = DB_HMI_Status.finger;
			Set_Left_Finger(DB_HMI_Status.finger);
		}

		// Mirror
		if (init || DB_HMI_Status_Old.mirror != DB_HMI_Status.mirror) {
			DB_HMI_Status_Old.mirror = DB_HMI_Status.mirror;
			Set_Left_Mirror(DB_HMI_Status.mirror);
		}

		// Others
		if (init || DB_HMI_Mode_Old.mode_trip != DB_HMI_Mode.mode_trip
				|| DB_HMI_Mode_Old.mode_trip_value != DB_HMI_Mode.mode_trip_value
				|| DB_ECU_Odometer_Old != DB_ECU_Odometer
				|| DB_MCU_RPM_Old != DB_MCU_RPM
				|| DB_HMI_Status_Old.keyless != DB_HMI_Status.keyless
				|| Mode_Hide_Trip_Old != (DB_HMI_Mode.mode == SWITCH_MODE_TRIP && DB_HMI_Mode.hide)) {

			// Set Color
			GUI_SetColor(0xFFC0C0C0);

			// Clear Left HMI
			GUI_MEMDEV_Select(hMem);
			GUI_DrawBitmapEx(&bmHMI_Left, x, y - r, x, y - r, 1000, 1000);

			// Mode Trip
			{
				DB_HMI_Mode_Old.mode_trip = DB_HMI_Mode.mode_trip;
				Mode_Hide_Trip_Old = (DB_HMI_Mode.mode == SWITCH_MODE_TRIP && DB_HMI_Mode.hide);

				if (!Mode_Hide_Trip_Old) {
					// Mode Trip Label
					Set_Left_Trip(DB_HMI_Mode.mode_trip);
				}

				// Mode Trip Value
				DB_HMI_Mode_Old.mode_trip_value = DB_HMI_Mode.mode_trip_value;
				GUI_SetFont(&GUI_FontSquare721_BT23);
				sprintf(str, "%05u", (unsigned int) DB_HMI_Mode.mode_trip_value);
				GUI_DispStringInRectWrap(str, &pRect_SubTrip, GUI_TA_BOTTOM | GUI_TA_RIGHT, GUI_WRAPMODE_NONE);
			}

			// Odometer
			DB_ECU_Odometer_Old = DB_ECU_Odometer;
			GUI_SetFont(&GUI_FontSquare721_BT23);
			sprintf(str, "%05u", (unsigned int) DB_ECU_Odometer);
			GUI_DispStringInRectWrap(str, &pRect_TotalTrip, GUI_TA_BOTTOM | GUI_TA_RIGHT, GUI_WRAPMODE_NONE);

			// Keyless
			DB_HMI_Status_Old.keyless = DB_HMI_Status.keyless;
			Set_Left_Keyless(DB_HMI_Status.keyless);

			// RPM Needle
			DB_MCU_RPM_Old = DB_MCU_RPM;
			Set_Left_Jarum(DB_MCU_RPM <= MCU_RPM_MAX ? DB_MCU_RPM * max / MCU_RPM_MAX : max, x, y, r, h, max);

			// Print result to LCD
			GUI_MEMDEV_Select(0);
			GUI_MEMDEV_CopyToLCD(hMem);
		}

#else
		// Sein Right
		if (DB_HMI_Status_Old.sein_right != DB_HMI_Status.sein_right) {
			DB_HMI_Status_Old.sein_right = DB_HMI_Status.sein_right;
			Set_Right_Sein(DB_HMI_Status.sein_right);
		}

		// Warning
		if (init || DB_HMI_Status_Old.warning != DB_HMI_Status.warning) {
			DB_HMI_Status_Old.warning = DB_HMI_Status.warning;
			Set_Right_Warning(DB_HMI_Status.warning);
		}

		// ABS
		if (init || DB_HMI_Status_Old.abs != DB_HMI_Status.abs) {
			DB_HMI_Status_Old.abs = DB_HMI_Status.abs;
			Set_Right_Abs(DB_HMI_Status.abs);
		}

		// Temperature Indicator
		if (init || DB_HMI_Status_Old.temperature != DB_HMI_Status.temperature) {
			DB_HMI_Status_Old.temperature = DB_HMI_Status.temperature;
			Set_Right_Temp(DB_HMI_Status.temperature);
		}

		// Lamp
		if (init || DB_HMI_Status_Old.lamp != DB_HMI_Status.lamp) {
			DB_HMI_Status_Old.lamp = DB_HMI_Status.lamp;
			Set_Right_Lamp(DB_HMI_Status.lamp);
		}

		// Set Color
		GUI_SetColor(0xFFC0C0C0);

		// Speed
		if (init || DB_ECU_Speed_Old != DB_ECU_Speed) {
			DB_ECU_Speed_Old = DB_ECU_Speed;

			GUI_SetFont(&GUI_FontSquare721_BT60);
			sprintf(str, "%03u", DB_ECU_Speed);
			GUI_DispStringInRectWrap(str, &pRect_Speed, GUI_TA_BOTTOM | GUI_TA_RIGHT, GUI_WRAPMODE_NONE);
		}

		// Battery Percentage
		{
			if (init || DB_BMS_SoC_Old != DB_BMS_SoC) {
				DB_BMS_SoC_Old = DB_BMS_SoC;

				// Battery Value
				GUI_SetFont(&GUI_FontSquare721_BT31);
				sprintf(str, "%02u", DB_BMS_SoC);
				GUI_DispStringInRectWrap(str, &pRect_Battery, GUI_TA_BOTTOM | GUI_TA_RIGHT, GUI_WRAPMODE_NONE);
			}

			// Detect trigger event
			if (DB_BMS_SoC <= 20) {
				if (!DB_BMS_SoC_Low) {
					DB_BMS_SoC_Low = 1;
					Hide_Battery_Low = 0;
					DB_BMS_SoC_Update = 1;
				} else if ((osKernelSysTick() - tickBatteryLow) >= tick500ms) {
					tickBatteryLow = osKernelSysTick();
					Hide_Battery_Low = !Hide_Battery_Low;
					DB_BMS_SoC_Update = 1;
				}
			} else if (DB_BMS_SoC > 20 && DB_BMS_SoC_Low) {
				DB_BMS_SoC_Low = 0;
				Hide_Battery_Low = 0;
				DB_BMS_SoC_Update = 1;
			}

			// Battery Icon & Unit
			if (init || DB_BMS_SoC_Update) {
				DB_BMS_SoC_Update = 0;

				// Battery Icon
				Set_Right_Battery(Hide_Battery_Low ? -1 : DB_BMS_SoC);

				// Battery Unit
				if (DB_BMS_SoC <= 20) {
					GUI_SetColor(0xFFE62129);
				}
				GUI_ClearRect(pRect_Battery_Unit.x0, pRect_Battery_Unit.y0, pRect_Battery_Unit.x1, pRect_Battery_Unit.y1);
				GUI_SetFont(&GUI_FontSquare721_BT17);
				sprintf(str, "%c", '%');
				GUI_DispStringInRectWrap(str, &pRect_Battery_Unit, GUI_TA_BOTTOM | GUI_TA_LEFT, GUI_WRAPMODE_NONE);
				GUI_SetColor(0xFFC0C0C0);
			}
		}

		// Signal Percentage
		if (init || DB_ECU_Signal_Old != DB_ECU_Signal) {
			DB_ECU_Signal_Old = DB_ECU_Signal;

			// fill all black
			GUI_SetBkColor(GUI_BLACK);
			GUI_ClearRect(pRect_Signal.x0, pRect_Signal.y0, pRect_Signal.x1, pRect_Signal.y1);
			// clear some transparent
			GUI_SetBkColor(GUI_TRANSPARENT);
			GUI_ClearRect(
					pRect_Signal.x0,
					pRect_Signal.y0,
					pRect_Signal.x0 + (DB_ECU_Signal * (pRect_Signal.x1 - pRect_Signal.x0) / 100),
					pRect_Signal.y1
					);
			// reset the bg color
			GUI_SetBkColor(GUI_BLACK);
		}

		// Mode Report
		{
			// Mode Report Unit
			if (init || DB_HMI_Mode_Old.mode_report != DB_HMI_Mode.mode_report) {
				GUI_ClearRect(pRect_Report_Unit.x0, pRect_Report_Unit.y0, pRect_Report_Unit.x1, pRect_Report_Unit.y1);
				GUI_SetFont(&GUI_FontSquare721_BT10);
				sprintf(str, "%s", Report_Unit[DB_HMI_Mode.mode_report]);
				GUI_DispStringInRectWrap(str, &pRect_Report_Unit, GUI_TA_BOTTOM | GUI_TA_LEFT, GUI_WRAPMODE_NONE);
			}

			// Mode Report Label
			if (init || DB_HMI_Mode_Old.mode_report != DB_HMI_Mode.mode_report
					|| Mode_Hide_Report_Old != (DB_HMI_Mode.mode == SWITCH_MODE_REPORT && DB_HMI_Mode.hide)) {
				DB_HMI_Mode_Old.mode_report = DB_HMI_Mode.mode_report;
				Mode_Hide_Report_Old = (DB_HMI_Mode.mode == SWITCH_MODE_REPORT && DB_HMI_Mode.hide);

				GUI_ClearRect(pRect_Report_Mode.x0, pRect_Report_Mode.y0, pRect_Report_Mode.x1, pRect_Report_Mode.y1);
				if (!Mode_Hide_Report_Old) {
					GUI_SetFont(&GUI_FontSquare721_BT14);
					sprintf(str, "%s", Report_Mode[DB_HMI_Mode.mode_report]);
					GUI_DispStringInRectWrap(str, &pRect_Report_Mode, GUI_TA_BOTTOM | GUI_TA_RIGHT, GUI_WRAPMODE_NONE);
				}
			}

			// Mode Report Value
			if (init || DB_HMI_Mode_Old.mode_report_value != DB_HMI_Mode.mode_report_value) {
				DB_HMI_Mode_Old.mode_report_value = DB_HMI_Mode.mode_report_value;

				GUI_SetFont(&GUI_FontSquare721_BT17);
				sprintf(str, "%02u", DB_HMI_Mode.mode_report_value);
				GUI_DispStringInRectWrap(str, &pRect_Report_Value, GUI_TA_BOTTOM | GUI_TA_RIGHT, GUI_WRAPMODE_NONE);
			}
		}

		// Mode Drive
		if (init || DB_HMI_Mode_Old.mode_drive != DB_HMI_Mode.mode_drive
				|| Mode_Hide_Drive_Old != (DB_HMI_Mode.mode == SWITCH_MODE_DRIVE && DB_HMI_Mode.hide)) {
			DB_HMI_Mode_Old.mode_drive = DB_HMI_Mode.mode_drive;
			Mode_Hide_Drive_Old = (DB_HMI_Mode.mode == SWITCH_MODE_DRIVE && DB_HMI_Mode.hide);

			if (!Mode_Hide_Drive_Old) {
				// if reverse, change color
				if (DB_HMI_Mode.mode_drive == SWITCH_MODE_DRIVE_R) {
					GUI_SetColor(0xFFFF8000);
				}
				GUI_SetFont(&GUI_FontSquare721_Cn_BT62);
				sprintf(str, "%c", Drive_Mode[DB_HMI_Mode.mode_drive]);
				GUI_DispStringInRectWrap(str, &pRect_Drive,
				GUI_TA_VCENTER | GUI_TA_HCENTER, GUI_WRAPMODE_NONE);
			} else {
				// hide
				GUI_ClearRect(pRect_Drive.x0, pRect_Drive.y0, pRect_Drive.x1, pRect_Drive.y1);
			}
		}
#endif

		init = 0;
	}
	/* USER CODE END GUI_MainTask */
}

// Functions list
void Set_Default_Data(void) {
	extern modes_t DB_HMI_Mode;
	extern status_t DB_HMI_Status;
	extern uint32_t DB_ECU_Odometer, DB_MCU_RPM;
	extern uint8_t DB_ECU_Signal, DB_ECU_Speed, DB_BMS_SoC;

	DB_HMI_Mode.mode = SWITCH_MODE_TRIP;
	DB_HMI_Mode.hide = 0;
	DB_HMI_Mode.mode_drive = SWITCH_MODE_DRIVE_E;
	DB_HMI_Mode.mode_trip = SWITCH_MODE_TRIP_A;
	DB_HMI_Mode.mode_trip_value = 0;
	DB_HMI_Mode.mode_report = SWITCH_MODE_REPORT_RANGE;
	DB_HMI_Mode.mode_report_value = 0;

	DB_HMI_Status.abs = 0;
	DB_HMI_Status.mirror = 0;
	DB_HMI_Status.lamp = 0;
	DB_HMI_Status.warning = 1;
	DB_HMI_Status.temperature = 0;
	DB_HMI_Status.finger = 0;
	DB_HMI_Status.keyless = 0;
	DB_HMI_Status.daylight = 1;
	DB_HMI_Status.sein_left = 0;
	DB_HMI_Status.sein_right = 0;

	DB_ECU_Odometer = 0;
	DB_ECU_Signal = 0;
	DB_ECU_Speed = 0;
	DB_MCU_RPM = 0;
	DB_BMS_SoC = 0;
}
void Run_Boot_Animation(void) {
	uint16_t k;
	// start of booting animation
	GUI_SelectLayer(1);
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	// start of circular booting animation
	GUI_SetColor(GUI_TRANSPARENT);
#if USE_HMI_LEFT
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
	for (k = 0; k <= 20; k++) {
		GUI_FillRect(40, 120 - 1, 40 + k, 170);
		GUI_Delay(20);
	}
	for (k = 0; k <= 180; k++) {
		GUI_DrawPie(60, 120 - 1, 250, 270, 270 + k, 0);
		GUI_Delay(10);
	}
	for (k = 0; k <= 20; k++) {
		GUI_FillRect(60 - k, 50, 60, 120 - 1);
		GUI_Delay(20);
	}
#endif
	// end of booting animation
}

void Set_Boot_Overlay(void) {
	// Make layer 1 transparent
	GUI_SelectLayer(1);
	GUI_SetBkColor(GUI_TRANSPARENT);
	GUI_Clear();

	// Give overlay on indicators at layer 1
	GUI_SelectLayer(0);
#if USE_HMI_LEFT
	GUI_DrawBitmap(&bmHMI_Left, 0, 0);
	const GUI_POINT aPoints[] = { { 300, 66 }, { 257, 66 }, { 230, 39 }, { 144, 39 }, { 87, 66 }, { 39, 175 }, { 55, 205 }, { 215,
			205 }, { 250, 153 }, { 300, 153 } };
#else
	GUI_DrawBitmap(&bmHMI_Right, 0, 0);
	const GUI_POINT aPoints[] = { { LCD_GetXSize() - 1 - 300, 66 }, { LCD_GetXSize() - 1 - 257, 66 },
			{ LCD_GetXSize() - 1 - 230, 39 }, { LCD_GetXSize() - 1 - 144, 39 }, { LCD_GetXSize() - 1 - 87, 66 }, { LCD_GetXSize() - 1
					- 87, 66 }, { 273, 135 }, { 275, 140 }, { LCD_GetXSize() - 1 - 39, 175 }, { LCD_GetXSize() - 1 - 55, 205 },
			{ 150, 205 }, { 175, 180 }, { 170, 145 }, { 150, 128 }, { 120, 128 }, { 100, 150 }, { 100, 180 }, { 120, 205 }, {
					LCD_GetXSize() - 1 - 215, 205 }, { LCD_GetXSize() - 1 - 250, 153 }, { LCD_GetXSize() - 1 - 300, 153 } };
#endif
	// overlay for first booting
	GUI_SetColor(GUI_BLACK);
	GUI_FillPolygon(aPoints, GUI_COUNTOF(aPoints), 0, 0);
}

void Set_Indicator(GUI_CONST_STORAGE GUI_BITMAP *bg,
GUI_CONST_STORAGE GUI_BITMAP *fg, uint16_t x, uint16_t y, uint8_t status, uint8_t alpha) {

	GUI_RECT pRect = { x, y, x + fg->XSize, y + fg->YSize };

	// draw background
	GUI_SetClipRect(&pRect);
	GUI_DrawBitmapEx(bg, x, y, x, y, 1000, 1000);
	GUI_SetClipRect(NULL);
	// draw indicator image
	if (status == 1) {
		GUI_SetAlpha(alpha);
		GUI_DrawBitmap(fg, x, y);
		GUI_SetAlpha(255);
	}
}

#if USE_HMI_LEFT

void Set_Left_Sein(uint8_t status) {
	Set_Indicator(&bmHMI_Left, &bmHMI_Left_Sein, 275, 84, status, 200);
}

void Set_Left_Finger(uint8_t status) {
	Set_Indicator(&bmHMI_Left, &bmHMI_Left_Finger, 293, 127, status, 200);
}

void Set_Left_Mirror(uint8_t status) {
	Set_Indicator(&bmHMI_Left, &bmHMI_Left_Mirror, 261, 129, status, 200);
}

void Set_Left_Keyless(uint8_t status) {
	Set_Indicator(&bmHMI_Left, &bmHMI_Left_Keyless, 228, 133, status, 200);
}

void Set_Left_Trip(switch_mode_trip_t mode_trip) {
	const uint16_t x = 129, y = 89;
	GUI_CONST_STORAGE GUI_BITMAP *pImage;

	// decide the image
	if (mode_trip == SWITCH_MODE_TRIP_A) {
		pImage = &bmHMI_Left_Trip_A;
	} else {
		pImage = &bmHMI_Left_Trip_B;
	}

	Set_Indicator(&bmHMI_Left, pImage, x, y, 1, 254);
}

void Set_Left_Jarum(uint8_t deg, uint16_t x, uint16_t y, uint16_t r, uint16_t h, uint8_t max) {
	GUI_POINT aPoints_Jarum[] = {
			{
					(x + r) + (((h / 2) + 1) * cos(D2R(deg + 270))),
					(y + (h / 2) + 1) + (((h / 2) + 1) * sin(D2R(deg + 270)))
			}, //atas
			{
					(x + r) + (r * cos(D2R(deg + 180))),
					(y + (h / 2) + 1) + (r * sin(D2R(deg + 180)))
			}, //ujung
			{
					(x + r) + (((h / 2) + 1) * cos(D2R(deg + 90))),
					(y + (h / 2) + 1) + (((h / 2) + 1) * sin(D2R(deg + 90)))
			} //bawah
	};

	GUI_SetColor(GUI_RED);
	GUI_AA_SetFactor(6);
	GUI_SetAlpha(205);
	GUI_AA_FillPolygon(aPoints_Jarum, GUI_COUNTOF(aPoints_Jarum), 0, 0);
	GUI_SetAlpha(255);
	GUI_AA_FillCircle(x + r, y + (h / 2) + 1, (h / 2) + 2);
	GUI_AA_SetFactor(1);
}

#else

void Set_Right_Sein(uint8_t status) {
	Set_Indicator(&bmHMI_Right, &bmHMI_Right_Sein, 20, 83, status, 200);
}

void Set_Right_Temp(uint8_t status) {
	Set_Indicator(&bmHMI_Right, &bmHMI_Right_Temp, 34, 131, status, 200);
}

void Set_Right_Lamp(uint8_t status) {
	Set_Indicator(&bmHMI_Right, &bmHMI_Right_Lamp, 190, 136, status, 200);
}

void Set_Right_Warning(uint8_t status) {
	Set_Indicator(&bmHMI_Right, &bmHMI_Right_Warning, 4, 130, status, 200);
}

void Set_Right_Abs(uint8_t status) {
	Set_Indicator(&bmHMI_Right, &bmHMI_Right_Abs, 63, 135, status, 200);
}

void Set_Right_Battery(int8_t status) {
	GUI_CONST_STORAGE GUI_BITMAP *bmHMI_Right_Battery = (status > 20 ? &bmHMI_Right_Battery_Full : &bmHMI_Right_Battery_Low);
	Set_Indicator(&bmHMI_Right, bmHMI_Right_Battery, 195, 170, (status != -1), 200);
}
#endif
/*************************** End of file ****************************/
