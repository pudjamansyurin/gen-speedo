/*
 * _gui.c
 *
 *  Created on: Oct 21, 2019
 *      Author: Puja
 */

/* Includes ------------------------------------------------------------------*/
#include "_guiapp.h"

/* External variables --------------------------------------------------------*/
extern db_t DB;
extern collection_t COL;
extern guiapp_t GAPP;
extern osEventFlagsId_t GlobalEventHandle;

/* Functions prototypes ------------------------------------------------------*/
static void BootOverlay(void);
static void BootAnimation(void);

/* Functions -----------------------------------------------------------------*/
void StartDisplayTask(void *argument) {
	/* USER CODE BEGIN GUI_MainTask */
	uint32_t notifValue;

	// wait until ManagerTask done
	osEventFlagsWait(GlobalEventHandle, EVENT_READY, osFlagsNoClear,
	osWaitForever);

	// create MEMDEV on layer 1
#if USE_HMI_LEFT
	GUI_SelectLayer(1);
	GUI_MEMDEV_Handle hMem = GUI_MEMDEV_Create(
			COL.x,
			COL.y - COL.r,
			COL.x + COL.r + (COL.r * cos(_D2R(COL.max + 180))) + 5 - COL.x + 25,
			COL.y + COL.h + 5 - (COL.y - COL.r));
#endif

	// Booting
	BootOverlay();
	BootAnimation();

	// Draw the layer 0 (background)
	GUI_SelectLayer(0);
	GUI_DrawBitmap(GAPP.background, 0, 0);
	GUI_Delay(500);

	// Drawing at layer 1
	GUI_SelectLayer(1);

	// Infinitive loop
	while (1) {
		LOG_StrLn("GUI:Refresh");

		// check if has new CAN message
		if (xTaskNotifyWait(EVT_DISPLAY_UPDATE, ULONG_MAX, &notifValue, pdMS_TO_TICKS(500)) == pdFALSE) {
			Reset_Database();
		}

#if USE_HMI_LEFT
		// Icon only
		LEFT_Sein();
		LEFT_Finger();
		LEFT_Mirror();

		// MEMDEV: Redraw background
		GUI_MEMDEV_Select(hMem);
		GUI_DrawBitmapEx(GAPP.background, COL.x, COL.y - COL.r, COL.x, COL.y - COL.r, 1000, 1000);

		// Icon + Text
		LEFT_Keyless();
		LEFT_ModeTrip();
		LEFT_Odometer();
		LEFT_Needle();

		// MEMDEV: Print result to LCD
		GUI_MEMDEV_Select(0);
		GUI_MEMDEV_CopyToLCD(hMem);
#else
		// Icon only
		RIGHT_Sein();
		RIGHT_Warning();
		RIGHT_ABS();
		RIGHT_Overheat();
		RIGHT_Lamp();

		// Icon + Text
		RIGHT_Speed();
		RIGHT_Battery();
		RIGHT_Signal();
		RIGHT_ModeReport();
		RIGHT_ModeDrive();
#endif
	}
	/* USER CODE END GUI_MainTask */
}

static void BootOverlay() {
	// Make layer 1 transparent
	GUI_SelectLayer(1);
	GUI_SetBkColor(GUI_TRANSPARENT);
	GUI_Clear();

	// Give overlay on indicators at layer 1
	GUI_SelectLayer(0);
	GUI_DrawBitmap(GAPP.background, 0, 0);

	// overlay for first booting
	GUI_SetColor(GUI_BLACK);
	GUI_FillPolygon(GAPP.overlay.points, GAPP.overlay.count, 0, 0);
}

static void BootAnimation(void) {
	// start of booting animation
	GUI_SelectLayer(1);
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	// start of circular booting animation
	GUI_SetColor(GUI_TRANSPARENT);

#if USE_HMI_LEFT
	LEFT_Animation();
#else
	RIGHT_Animation();
#endif
	// end of booting animation
}

/*************************** End of file ****************************/
