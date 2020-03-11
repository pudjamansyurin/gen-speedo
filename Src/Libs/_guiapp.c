/*
 * _gui.c
 *
 *  Created on: Oct 21, 2019
 *      Author: Puja
 */

/* Includes ------------------------------------------------------------------*/
#include "_guiapp.h"

/* External variable */
extern IWDG_HandleTypeDef hiwdg;
extern db_t DB;
extern guiapp_t GAPP;

/* Functions prototypes --------------------------------------------------------*/
static void RunBootAnimation(void);
static void BootOverlay(guiapp_t *GA);

/* Main task ------------------------------------------------------------------*/
void GUI_MainTask(void) {
  /* USER CODE BEGIN GUI_MainTask */
  extern collection_t COL;
  latch_t TMP = { 0 };
  uint32_t notifValue;
  BaseType_t xResult;

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
  RunBootAnimation();

  // Draw the layer 0 background
  GUI_SelectLayer(0);
  GUI_DrawBitmap(GAPP.background, 0, 0);
  GUI_Delay(500);

  // Make layer 1 transparent
  GUI_SelectLayer(1);
  GUI_SetBkColor(GUI_TRANSPARENT);
  GUI_Clear();
  GUI_SetBkColor(GUI_BLACK);

  TMP.init = 1;

  while (1) {
    // Feed the dog
    HAL_IWDG_Refresh(&hiwdg);

    if (!TMP.init) {
      // check if has new can message
      xResult = xTaskNotifyWait(0x00, ULONG_MAX, &notifValue, pdMS_TO_TICKS(500));
      // if not receive any CAN message
      if (xResult == pdFALSE) {
        TMP.init = 1;
      }
    }

    // init hook
    if (TMP.init) {
      // reset data to default
      Reset_Database();
      // set back-light ON
      _SetBacklight(1);
    }

#if USE_HMI_LEFT
    // Sein Left
    LEFT_Sein(&TMP);
    // Finger
    LEFT_Finger(&TMP);
    // Mirror
    LEFT_Mirror(&TMP);

    // Others
    if (TMP.init
        || TMP.db.hmi1.mode.trip.sel != DB.hmi1.mode.trip.sel
        || TMP.db.hmi1.mode.trip.val != DB.hmi1.mode.trip.val
        || TMP.db.vcu.odometer != DB.vcu.odometer
        || TMP.db.mcu.rpm != DB.mcu.rpm
        || TMP.db.hmi1.status.keyless != DB.hmi1.status.keyless
        || TMP.flag.mode.trip != (DB.hmi1.mode.sel == SW_M_TRIP && DB.hmi1.mode.hide)) {

      // Set Color
      GUI_SetColor(0xFFC0C0C0);
      // Clear Left HMI
      GUI_MEMDEV_Select(hMem);
      GUI_DrawBitmapEx(GAPP.background, COL.x, COL.y - COL.r, COL.x, COL.y - COL.r, 1000, 1000);

      // Mode Trip
      LEFT_ModeTrip(&TMP);
      // Odometer
      LEFT_Odometer(&TMP);
      // Keyless
      LEFT_Keyless(&TMP);
      // RPM Needle
      LEFT_Needle(&TMP, &COL);

      // Print result to LCD
      GUI_MEMDEV_Select(0);
      GUI_MEMDEV_CopyToLCD(hMem);
    }

#else
    // Sein Right
    RIGHT_Sein(&TMP);
    // Warning
    RIGHT_Warning(&TMP);
    // ABS
    RIGHT_ABS(&TMP);
    // Temperature
    RIGHT_Temperature(&TMP);
    // Lamp
    RIGHT_Lamp(&TMP);

    // Set Color
    GUI_SetColor(0xFFC0C0C0);
    // Speed
    RIGHT_Speed(&TMP);
    // Battery
    RIGHT_Battery(&TMP);
    // Signal
    RIGHT_Signal(&TMP);
    // Mode Report
    RIGHT_ModeReport(&TMP);
    // Mode Drive
    RIGHT_ModeDrive(&TMP)
#endif

    TMP.init = 0;
  }
  /* USER CODE END GUI_MainTask */
}

// Functions list
static void RunBootAnimation(void) {
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
/*************************** End of file ****************************/
