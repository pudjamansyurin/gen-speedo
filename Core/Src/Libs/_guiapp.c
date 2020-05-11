/*
 * _gui.c
 *
 *  Created on: Oct 21, 2019
 *      Author: Puja
 */

/* Includes ------------------------------------------------------------------*/
#include "_guiapp.h"

/* External variables --------------------------------------------------------*/
extern display_t DISPLAY;
extern osEventFlagsId_t GlobalEventHandle;

/* Functions prototypes ------------------------------------------------------*/
static void BootOverlay(void);
static void BootAnimation(void);
static void StartDrawing(void);

/* Functions -----------------------------------------------------------------*/
void StartDisplayTask(void *argument) {
	/* USER CODE BEGIN GUI_MainTask */
	uint32_t notif;

	// wait until ManagerTask done
	osEventFlagsWait(GlobalEventHandle, EVENT_READY, osFlagsWaitAny | osFlagsNoClear, osWaitForever);

	// Booting
	BootOverlay();
	BootAnimation();
	StartDrawing();

	// Infinitive loop
	while (1) {
		LOG_StrLn("GUI:Refresh");

		// check if it needs update
		notif = osThreadFlagsWait(EVT_MASK, osFlagsWaitAny, pdMS_TO_TICKS(500));
		if (!_RTOS_ValidThreadFlag(notif) || !(notif & EVT_DISPLAY_UPDATE)) {
			_ResetSystem();
		}

#if USE_HMI_LEFT
		// Icon only
		LEFT_Sein();
		LEFT_Finger();
		LEFT_Mirror();

		// Use MEMDEV to handle multiple components
		LEFT_MemGroupEnter();
		{
			LEFT_Keyless();
			LEFT_ModeTrip();
			LEFT_Odometer();
			LEFT_Needle();
		}
		LEFT_MemGroupExit();
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

	// Draw overlay in layer 1 to hide non-animated components
	GUI_SelectLayer(0);
	GUI_DrawBitmap(DISPLAY.background, 0, 0);
	GUI_SetColor(GUI_BLACK);
	GUI_FillPolygon(DISPLAY.overlay.points, DISPLAY.overlay.count, 0, 0);
}

static void BootAnimation(void) {
	// Fill layer 1 with black, then erase it with animation
	GUI_SelectLayer(1);
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	GUI_SetColor(GUI_TRANSPARENT);

	// start of circular booting animation
#if USE_HMI_LEFT
	LEFT_Animation();
#else
	RIGHT_Animation();
#endif
	// end of booting animation
}

static void StartDrawing(void) {
	// Draw the layer 0 (background)
	GUI_SelectLayer(0);
	GUI_DrawBitmap(DISPLAY.background, 0, 0);
	GUI_Delay(500);

	// Drawing at layer 1
	GUI_SelectLayer(1);
}
/*************************** End of file ****************************/
