/*
 * _gui.c
 *
 *  Created on: Oct 21, 2019
 *      Author: Puja
 */

/* Includes ------------------------------------------------------------------*/
#include "Libs/_guiapp.h"
#include "Drivers/_stemwin.h"
#if USE_HMI_LEFT
#include "Libs/_guiapp_left.h"
#else
#include "Libs/_guiapp_right.h"
#endif

/* External variables --------------------------------------------------------*/
extern display_t DISPLAY;
extern osEventFlagsId_t GlobalEventHandle;

/* Private Functions prototypes ----------------------------------------------*/
static void BootAnimation(void);
static void RefreshLayer(void);

/* GUI Thread ----------------------------------------------------------------*/
void StartDisplayTask(void *argument) {
	/* USER CODE BEGIN GUI_MainTask */
	uint32_t notif;

	// Wait until ManagerTask done
	osEventFlagsWait(GlobalEventHandle, EVENT_READY, osFlagsNoClear, osWaitForever);

	// Initialize
	osDelay(1000);
	BootAnimation();
	osDelay(500);
	RefreshLayer();

	// Infinitive loop
	while (1) {
		// Check if it needs update
		notif = osThreadFlagsWait(EVT_MASK, osFlagsWaitAny, pdMS_TO_TICKS(500));
		if (!_RTOS_ValidThreadFlag(notif) || !(notif & EVT_DISPLAY_UPDATE)) {
			_ResetSystem();
		}
		LOG_StrLn("GUI:Refresh");

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

/* Public Functions ----------------------------------------------------------*/
void GUI_ClearRectangle(GUI_RECT *rect) {
	GUI_ClearRect(rect->x0, rect->y0, rect->x1, rect->y1);
}

void GUI_IconMem(uint16_t x, uint16_t y, const GUI_BITMAP *fg, uint8_t show, uint8_t alpha) {
	// create & select MEMDEV
	GUI_SelectLayer(1);
	GUI_MEMDEV_Handle hMem = GUI_MEMDEV_Create(x, y, x + fg->XSize, y + fg->XSize);
	GUI_MEMDEV_Select(hMem);

	// draw background
	GUI_Icon(x, y, fg, show, alpha);

	// Print result & delete MEMDEV
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_CopyToLCD(hMem);
	GUI_MEMDEV_Delete(hMem);
}

void GUI_Icon(uint16_t x, uint16_t y, const GUI_BITMAP *fg, uint8_t show, uint8_t alpha) {
	GUI_RECT pRect = { x, y, x + fg->XSize, y + fg->YSize };

	// draw background
	GUI_SetClipRect(&pRect);
	GUI_DrawBitmapEx(DISPLAY.background, x, y, x, y, 1000, 1000);
	GUI_SetClipRect(NULL);

	// draw indicator image
	if (show) {
		GUI_SetAlpha(alpha);
		GUI_DrawBitmap(fg, x, y);
		GUI_SetAlpha(255);
	}
}

/* Private Functions ---------------------------------------------------------*/
static void BootAnimation(void) {
	// Draw overlay in layer 1 to hide non-animated components
	GUI_SelectLayer(0);
	GUI_DrawBitmap(DISPLAY.background, 0, 0);
	GUI_SetColor(GUI_BLACK);
	GUI_FillPolygon(DISPLAY.overlay.points, DISPLAY.overlay.count, 0, 0);

	// Fill layer 1 with black, then erase it with animation
	GUI_SelectLayer(1);
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	GUI_SetColor(GUI_TRANSPARENT);
#if USE_HMI_LEFT
	LEFT_Animation();
#else
	RIGHT_Animation();
#endif
	// end of booting animation
}

static void RefreshLayer(void) {
	// Draw the layer 0 (background)
	GUI_SelectLayer(0);
	GUI_DrawBitmap(DISPLAY.background, 0, 0);

	// Drawing at layer 1
	GUI_SelectLayer(1);
}

/*************************** End of file ****************************/
