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

/* Functions prototypes --------------------------------------------------------*/
void Set_Indikator(GUI_CONST_STORAGE GUI_BITMAP *bg, const GUI_RECT *pRect, GUI_CONST_STORAGE GUI_BITMAP *fg,
		uint16_t x, uint16_t y, uint8_t status, uint8_t alpha);
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
#endif

/* Main task ------------------------------------------------------------------*/
void GUI_MainTask(void) {
	/* USER CODE BEGIN GUI_MainTask */
	char str[20];
	uint8_t init = 1;
	uint16_t k;
	uint32_t ulNotifiedValue;

	extern modes_t DB_HMI_Mode;
	extern status_t DB_HMI_Status;
	status_t DB_HMI_Status_Old;
	modes_t DB_HMI_Mode_Old;

#if USE_HMI_LEFT
	const uint16_t x = 58, y = 161, r = 123, h = 7;
	const uint8_t max = 112;
	extern uint32_t DB_MCU_RPM;
	extern uint32_t DB_ECU_Odometer;
	uint32_t DB_MCU_RPM_Old;
	uint32_t DB_ECU_Odometer_Old;
#else
	const char Drive_Mode[4] = { 'E', 'S', 'C', 'P' };
	const char Timestamp_Days[7][4] = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };
	const char Timestamp_Months[12][4] = { "Jan", "Peb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nop",
			"Des" };
	extern uint8_t DB_ECU_Speed;
	extern timestamp_t DB_ECU_TimeStamp;
	extern uint8_t DB_MCU_Temperature;
	extern uint8_t DB_BMS_SoC;
	uint8_t DB_ECU_Speed_Old;
	timestamp_t DB_ECU_TimeStamp_Old;
	uint8_t DB_MCU_Temperature_Old;
	uint8_t DB_BMS_SoC_Old;
#endif

	// Start executing thing
	GUI_SelectLayer(1);
	GUI_SetBkColor(GUI_TRANSPARENT);
	GUI_Clear();

	GUI_SelectLayer(0);
#if USE_HMI_LEFT
	GUI_DrawBitmap(&bmHMI_Left, 0, 0);
	// @formatter:off
	const GUI_POINT aPoints[] = {
			{ 300, 66 },
			{ 257, 66 },
			{ 230, 39 },
			{ 144, 39 },
			{ 87, 66 },
			{ 39, 175 },
			{ 55, 205 },
			{ 215, 205 },
			{	250, 153 },
			{ 300, 153 }
	};
	// @formatter:on
#else
	GUI_DrawBitmap(&bmHMI_Right, 0, 0);
	// @formatter:off
	const GUI_POINT aPoints[] = {
			{ LCD_GetXSize() - 1 - 300, 66 },
			{ LCD_GetXSize() - 1 - 257, 66 },
			{ LCD_GetXSize() - 1 - 230, 39 },
			{	LCD_GetXSize() - 1 - 144, 39 },
			{ LCD_GetXSize() - 1 - 87, 66 },
			{ LCD_GetXSize() - 1 - 87, 66 },
			{ 273, 135 },
			{ 275, 140 },
			{	LCD_GetXSize() - 1 - 39, 175 },
			{ LCD_GetXSize() - 1 - 55, 205 },
			{ 150, 205 },
			{ 175, 180 },
			{ 170, 145 },
			{ 150, 128 },
			{ 120, 128 },
			{ 100, 150 },
			{ 100, 180 },
			{ 120, 205 },
			{ LCD_GetXSize() - 1 - 215, 205 },
			{ LCD_GetXSize() - 1 - 250, 153 },
			{	LCD_GetXSize() - 1 - 300, 153 }
	};
	// @formatter:on
#endif
	// overlay for first booting
	GUI_SetColor(GUI_BLACK);
	GUI_FillPolygon(aPoints, GUI_COUNTOF(aPoints), 0, 0);
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

	GUI_SelectLayer(0);
#if USE_HMI_LEFT
	GUI_DrawBitmap(&bmHMI_Left, 0, 0);
	GUI_RECT pRect_SubTrip = { 159, 84, 159 + 64, 84 + 24 };
	GUI_RECT pRect_TotalTrip = { 159, 107, 159 + 64, 107 + 24 };

	GUI_SelectLayer(1);
	GUI_MEMDEV_Handle hMem = GUI_MEMDEV_Create(x, y - r, x + r + (r * cos(D2R(max + 180))) + 5 - (x),
			y + h + 5 - (y - r));
#else
	GUI_DrawBitmap(&bmHMI_Right, 0, 0);
	GUI_RECT pRect_Speed = { 85, 79, 85 + 100, 79 + 41 };
	GUI_RECT pRect_Battery = { 227, 164, 227 + 35, 164 + 28 };
	GUI_RECT pRect_Range = { 235, 188, 235 + 20, 188 + 15 };
	GUI_RECT pRect_Temp = { 178, 132, 178 + 32, 132 + 22 };
	GUI_RECT pRect_Datetime = { 65, 48, 65 + 150, 48 + 16 };
	GUI_RECT pRect_Drive = { 126, 145, 126 + 26, 145 + 40 };
#endif
	GUI_Delay(500);

	GUI_SelectLayer(1);
	GUI_SetBkColor(GUI_TRANSPARENT);
	GUI_Clear();
	GUI_SetBkColor(GUI_BLACK);

	while (1) {
		if (!init) {
			// check if has new can message
			xTaskNotifyWait(0x00, ULONG_MAX, &ulNotifiedValue, portMAX_DELAY);
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

		// Keyless
		if (init || DB_HMI_Status_Old.keyless != DB_HMI_Status.keyless) {
			DB_HMI_Status_Old.keyless = DB_HMI_Status.keyless;
			Set_Left_Keyless(DB_HMI_Status.keyless);
		}

		// Others
		if (init || DB_HMI_Mode_Old.mode_trip != DB_HMI_Mode.mode_trip
				|| DB_HMI_Mode_Old.mode_trip_value != DB_HMI_Mode.mode_trip_value || DB_ECU_Odometer_Old != DB_ECU_Odometer
				|| DB_MCU_RPM_Old != DB_MCU_RPM) {

			// Set Color
			GUI_SetColor(0xFFC0C0C0);

			// Clear Left HMI
			GUI_MEMDEV_Select(hMem);
			GUI_DrawBitmapEx(&bmHMI_Left, x, y - r, x, y - r, 1000, 1000);

			// Mode Trip
			DB_HMI_Mode_Old.mode_trip = DB_HMI_Mode.mode_trip;
			Set_Left_Trip(DB_HMI_Mode.mode_trip);

			// Mode Trip Value
			DB_HMI_Mode_Old.mode_trip_value = DB_HMI_Mode.mode_trip_value;
			GUI_SetFont(&GUI_FontSquare721_BT23);
			sprintf(str, "%05u", (unsigned int) DB_HMI_Mode.mode_trip_value);
			GUI_DispStringInRectWrap(str, &pRect_SubTrip, GUI_TA_VCENTER | GUI_TA_RIGHT, GUI_WRAPMODE_NONE);

			// Odometer
			DB_ECU_Odometer_Old = DB_ECU_Odometer;
			GUI_SetFont(&GUI_FontSquare721_BT23);
			sprintf(str, "%05u", (unsigned int) DB_ECU_Odometer);
			GUI_DispStringInRectWrap(str, &pRect_TotalTrip, GUI_TA_VCENTER | GUI_TA_RIGHT, GUI_WRAPMODE_NONE);

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
			GUI_DispStringInRectWrap(str, &pRect_Speed, GUI_TA_VCENTER | GUI_TA_RIGHT, GUI_WRAPMODE_NONE);
		}

		// Battery Percentage
		if (init || DB_BMS_SoC_Old != DB_BMS_SoC) {
			DB_BMS_SoC_Old = DB_BMS_SoC;

			GUI_SetFont(&GUI_FontSquare721_BT31);
			sprintf(str, "%02u", DB_BMS_SoC);
			GUI_DispStringInRectWrap(str, &pRect_Battery, GUI_TA_VCENTER | GUI_TA_RIGHT, GUI_WRAPMODE_NONE);
		}

		// FIXME: i am should be glue with mode_report index
		// Mode Report
		if (init || DB_HMI_Mode_Old.mode_report_value != DB_HMI_Mode.mode_report_value) {
			DB_HMI_Mode_Old.mode_report_value = DB_HMI_Mode.mode_report_value;

			GUI_SetFont(&GUI_FontSquare721_BT17);
			sprintf(str, "%02u", DB_HMI_Mode.mode_report_value);
			GUI_DispStringInRectWrap(str, &pRect_Range, GUI_TA_VCENTER | GUI_TA_RIGHT, GUI_WRAPMODE_NONE);
		}

		// Temperature
		if (init || DB_MCU_Temperature_Old != DB_MCU_Temperature) {
			DB_MCU_Temperature_Old = DB_MCU_Temperature;

			GUI_SetFont(&GUI_FontSquare721_BT30);
			sprintf(str, "%02u", DB_MCU_Temperature);
			GUI_DispStringInRectWrap(str, &pRect_Temp, GUI_TA_VCENTER | GUI_TA_RIGHT, GUI_WRAPMODE_NONE);
		}

		// Datetime
		if (init || DB_ECU_TimeStamp_Old.time.Minutes != DB_ECU_TimeStamp.time.Minutes) {
			DB_ECU_TimeStamp_Old.time.Minutes = DB_ECU_TimeStamp.time.Minutes;

			GUI_SetFont(&GUI_FontSquare721_BT16);
			sprintf(str, "%3s, %3s %02d  %02d:%02d", Timestamp_Days[DB_ECU_TimeStamp.date.WeekDay - 1],
					Timestamp_Months[DB_ECU_TimeStamp.date.Month - 1], DB_ECU_TimeStamp.date.Date, DB_ECU_TimeStamp.time.Hours,
					DB_ECU_TimeStamp.time.Minutes);
			GUI_DispStringInRectWrap(str, &pRect_Datetime, GUI_TA_VCENTER | GUI_TA_RIGHT, GUI_WRAPMODE_NONE);
		}

		// Mode Drive
		if (init || DB_HMI_Mode_Old.mode_drive != DB_HMI_Mode.mode_drive) {
			DB_HMI_Mode_Old.mode_drive = DB_HMI_Mode.mode_drive;

			GUI_SetFont(&GUI_FontSquare721_Cn_BT62);
			sprintf(str, "%c", Drive_Mode[DB_HMI_Mode.mode_drive]);
			GUI_DispStringInRectWrap(str, &pRect_Drive, GUI_TA_VCENTER | GUI_TA_HCENTER, GUI_WRAPMODE_NONE);
		}
#endif

		init = 0;
	}
	/* USER CODE END GUI_MainTask */
}

void Set_Indikator(GUI_CONST_STORAGE GUI_BITMAP *bg, const GUI_RECT *pRect, GUI_CONST_STORAGE GUI_BITMAP *fg,
		uint16_t x, uint16_t y, uint8_t status, uint8_t alpha) {
	GUI_SetClipRect(pRect);
	GUI_DrawBitmapEx(bg, x, y, x, y, 1000, 1000);
	GUI_SetClipRect(NULL);
	if (status == 1) {
		GUI_SetAlpha(alpha);
		GUI_DrawBitmap(fg, x, y);
		GUI_SetAlpha(255);
	}
}

#if USE_HMI_LEFT

void Set_Left_Sein(uint8_t status) {
	const uint16_t x = 277, y = 82;
	const GUI_RECT pRect_Left_Sein = { x, y, x + bmHMI_Left_Sein.XSize, y + bmHMI_Left_Sein.YSize };

	Set_Indikator(&bmHMI_Left, &pRect_Left_Sein, &bmHMI_Left_Sein, x, y, status, 200);
}

void Set_Left_Finger(uint8_t status) {
	const uint16_t x = 294, y = 125;
	const GUI_RECT pRect_Left_Finger = { x, y, x + bmHMI_Left_Finger.XSize, y + bmHMI_Left_Finger.YSize };

	Set_Indikator(&bmHMI_Left, &pRect_Left_Finger, &bmHMI_Left_Finger, x, y, status, 200);
}

void Set_Left_Mirror(uint8_t status) {
	const uint16_t x = 261, y = 127;
	const GUI_RECT pRect_Left_Mirror = { x, y, x + bmHMI_Left_Mirror.XSize, y + bmHMI_Left_Mirror.YSize };

	Set_Indikator(&bmHMI_Left, &pRect_Left_Mirror, &bmHMI_Left_Mirror, x, y, status, 200);
}

void Set_Left_Keyless(uint8_t status) {
	const uint16_t x = 228, y = 131;
	const GUI_RECT pRect_Left_Keyless = { x, y, x + bmHMI_Left_Keyless.XSize, y + bmHMI_Left_Keyless.YSize };

	Set_Indikator(&bmHMI_Left, &pRect_Left_Keyless, &bmHMI_Left_Keyless, x, y, status, 200);
}

void Set_Left_Jarum(uint8_t deg, uint16_t x, uint16_t y, uint16_t r, uint16_t h, uint8_t max) {
	GUI_POINT aPoints_Jarum[] = { { (x + r) + (((h / 2) + 1) * cos(D2R(deg + 270))), (y + (h / 2) + 1)
			+ (((h / 2) + 1) * sin(D2R(deg + 270))) }, //atas
			{ (x + r) + (r * cos(D2R(deg + 180))), (y + (h / 2) + 1) + (r * sin(D2R(deg + 180))) }, //ujung
			{ (x + r) + (((h / 2) + 1) * cos(D2R(deg + 90))), (y + (h / 2) + 1) + (((h / 2) + 1) * sin(D2R(deg + 90))) } //bawah
	};

	GUI_SetColor(GUI_RED);
	GUI_AA_SetFactor(6);
	GUI_SetAlpha(205);
	GUI_AA_FillPolygon(aPoints_Jarum, GUI_COUNTOF(aPoints_Jarum), 0, 0);
	GUI_SetAlpha(255);
	GUI_AA_FillCircle(x + r, y + (h / 2) + 1, (h / 2) + 2);
	GUI_AA_SetFactor(1);
}

void Set_Left_Trip(switch_mode_trip_t mode_trip) {
	const uint16_t x = 131, y = 86;
	const GUI_RECT pRect_Left_Trip = { x, y, x + bmHMI_Left_Trip_A.XSize, y + bmHMI_Left_Trip_A.YSize };
	GUI_CONST_STORAGE GUI_BITMAP *pImage;

	// decide the image
	pImage = (mode_trip == SWITCH_MODE_TRIP_A ? &bmHMI_Left_Trip_A : &bmHMI_Left_Trip_B);

	Set_Indikator(&bmHMI_Left, &pRect_Left_Trip, pImage, x, y, 1, 254);
}

#else

void Set_Right_Sein(uint8_t status) {
	const uint16_t x = 20, y = 82;
	const GUI_RECT pRect_Right_Sein = { x, y, x + bmHMI_Right_Sein.XSize, y + bmHMI_Right_Sein.YSize };

	Set_Indikator(&bmHMI_Right, &pRect_Right_Sein, &bmHMI_Right_Sein, x, y, status, 200);
}

void Set_Right_Temp(uint8_t status) {
	const uint16_t x = 33, y = 131;
	const GUI_RECT pRect_Right_Temp = { x, y, x + bmHMI_Right_Temp.XSize, y + bmHMI_Right_Temp.YSize };

	Set_Indikator(&bmHMI_Right, &pRect_Right_Temp, &bmHMI_Right_Temp, x, y, status, 200);
}

void Set_Right_Lamp(uint8_t status) {
	const uint16_t x = 203, y = 72;
	const GUI_RECT pRect_Right_Lamp = { x, y, x + bmHMI_Right_Lamp.XSize, y + bmHMI_Right_Lamp.YSize };

	Set_Indikator(&bmHMI_Right, &pRect_Right_Lamp, &bmHMI_Right_Lamp, x, y, status, 200);
}

void Set_Right_Warning(uint8_t status) {
	const uint16_t x = 3, y = 130;
	const GUI_RECT pRect_Right_Warning = { x, y, x + bmHMI_Right_Warning.XSize, y + bmHMI_Right_Warning.YSize };

	Set_Indikator(&bmHMI_Right, &pRect_Right_Warning, &bmHMI_Right_Warning, x, y, status, 200);
}

void Set_Right_Abs(uint8_t status) {
	const uint16_t x = 64, y = 135;
	const GUI_RECT pRect_Right_Abs = { x, y, x + bmHMI_Right_Abs.XSize, y + bmHMI_Right_Abs.YSize };

	Set_Indikator(&bmHMI_Right, &pRect_Right_Abs, &bmHMI_Right_Abs, x, y, status, 200);
}
#endif
/*************************** End of file ****************************/
