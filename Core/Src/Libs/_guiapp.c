/*
 * _gui.c
 *
 *  Created on: Oct 21, 2019
 *      Author: Puja
 */

/* Includes ------------------------------------------------------------------*/
#include "_guiapp.h"

/* External variables --------------------------------------------------------*/
extern IWDG_HandleTypeDef hiwdg;
extern db_t DB;
extern guiapp_t GAPP;
extern collection_t COL;

/* Functions prototypes ------------------------------------------------------*/
static void BootOverlay(guiapp_t *GA);
static void BootAnimation(void);

/* Functions -----------------------------------------------------------------*/
void GUI_MainTask(void) {
  /* USER CODE BEGIN GUI_MainTask */
  latch_t TMP = { 0 };
  uint32_t notifValue;
  BaseType_t xResult;

  // reset first
  Reset_Database();
  _SetBacklight(1);
  TMP.reset = 1;

#if USE_HMI_LEFT
  // create MEMDEV on layer 1
  GUI_SelectLayer(1);
  GUI_MEMDEV_Handle hMem = GUI_MEMDEV_Create(
      COL.x,
      COL.y - COL.r,
      COL.x + COL.r + (COL.r * cos(_D2R(COL.max + 180))) + 5 - COL.x + 25,
      COL.y + COL.h + 5 - (COL.y - COL.r));
#endif

  // Set overlay on all indicator on boot
  BootOverlay(&GAPP);
  // Run booting animation on start
  BootAnimation();
  // Draw the layer 0 (background)
  GUI_SelectLayer(0);
  GUI_DrawBitmap(GAPP.background, 0, 0);
  GUI_Delay(500);
  // Make layer 1 transparent
  GUI_SelectLayer(1);
  GUI_SetBkColor(GUI_TRANSPARENT);
  GUI_Clear();
  GUI_SetBkColor(GUI_BLACK);

  // Infinitive loop
  while (1) {
    // Feed the dog
    HAL_IWDG_Refresh(&hiwdg);
    LOG_StrLn("GUI:Refresh");

    // check if has new CAN message
    xResult = xTaskNotifyWait(0x00, ULONG_MAX, &notifValue, pdMS_TO_TICKS(500));
    // if not receive any CAN message
    if (xResult == pdFALSE) {
      // reset
      Reset_Database();
      _SetBacklight(1);

      TMP.reset = 1;
    } else {
      TMP.reset = 0;
    }

#if USE_HMI_LEFT
    LEFT_Sein(&TMP);
    LEFT_Finger(&TMP);
    LEFT_Mirror(&TMP);

    // Others
    if (LEFT_NeedUpdate(&TMP)) {
      // Clear Left HMI
      GUI_MEMDEV_Select(hMem);
      GUI_DrawBitmapEx(GAPP.background, COL.x, COL.y - COL.r, COL.x, COL.y - COL.r, 1000, 1000);

      // Set Color
      GUI_SetColor(0xFFC0C0C0);
      LEFT_ModeTrip(&TMP);
      LEFT_Odometer(&TMP);
      LEFT_Keyless(&TMP);
      LEFT_Needle(&TMP, &COL);

      // Print result to LCD
      GUI_MEMDEV_Select(0);
      GUI_MEMDEV_CopyToLCD(hMem);
    }

#else
    RIGHT_Sein(&TMP);
    RIGHT_Warning(&TMP);
    RIGHT_ABS(&TMP);
    RIGHT_Temperature(&TMP);
    RIGHT_Lamp(&TMP);

    // Set Color
    GUI_SetColor(0xFFC0C0C0);
    RIGHT_Speed(&TMP);
    RIGHT_Battery(&TMP);
    RIGHT_Signal(&TMP);
    RIGHT_ModeReport(&TMP);
    RIGHT_ModeDrive(&TMP);
#endif
  }
  /* USER CODE END GUI_MainTask */
}

static void BootOverlay(guiapp_t *GA) {
  // Make layer 1 transparent
  GUI_SelectLayer(1);
  GUI_SetBkColor(GUI_TRANSPARENT);
  GUI_Clear();

  // Give overlay on indicators at layer 1
  GUI_SelectLayer(0);
  GUI_DrawBitmap(GA->background, 0, 0);

  // overlay for first booting
  GUI_SetColor(GUI_BLACK);
  GUI_FillPolygon(GA->overlay.points, GA->overlay.count, 0, 0);
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
