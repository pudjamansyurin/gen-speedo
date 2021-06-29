#ifndef DASHBOARDVIEW_HPP
#define DASHBOARDVIEW_HPP

#include <gui/dashboardscreen_screen/dashboardScreenPresenter.hpp>
#include <gui_generated/dashboardscreen_screen/dashboardScreenViewBase.hpp>

#if !defined(SIMULATOR)
#include "_defs.h"
#endif

typedef struct {
  Unicode::UnicodeChar mode[HBAR_M_DRIVE_MAX][12];
  colortype color[HBAR_M_DRIVE_MAX];
} drive_t;

typedef struct {
  touchgfx::Unicode::UnicodeChar mode[HBAR_M_TRIP_MAX][7];
} trip_t;

typedef struct {
  touchgfx::TextAreaWithOneWildcard *pValueText[HBAR_M_PREDICTION_MAX];
  touchgfx::Unicode::UnicodeChar *pValueTextBuffer[HBAR_M_PREDICTION_MAX];
} prediction_t;

typedef struct {
  Image *image;
  MoveAnimator<Container> *container;
} icon_t;

typedef struct {
  int16_t x;
  int16_t y;
} coordinate_t;

typedef struct {
  coordinate_t prev;
  coordinate_t current;
  coordinate_t next;
} position_t;

class dashboardScreenView : public dashboardScreenViewBase {
 public:
  dashboardScreenView();
  virtual ~dashboardScreenView() {}
  virtual void setupScreen();
  virtual void tearDownScreen();

  virtual void handleTickEvent();

  virtual void writeSein(uint8_t leftSide, uint8_t state);
  virtual void writeSpeed(uint8_t percent);
  virtual void writeDiscur(uint8_t percent);
  virtual void writeState(int8_t value);
  virtual void writeBmsState(uint8_t value);
  virtual void writeMcuState(uint8_t value);
  virtual void writeScanningState(uint8_t value);
  virtual void writeCanState(uint8_t value);
  virtual void writeBattery(uint8_t percent);
  virtual void writeSignal(uint8_t percent);
  virtual void writeIndicator(uint8_t index);
  virtual void writeDriveMode(uint8_t index);
  virtual void writeTripMode(uint8_t index);
  virtual void writeTripValue(uint16_t value);
  virtual void writePredictionMode(uint8_t index);
  virtual void writePredictionValue(uint16_t value);

  virtual void writeModeSelector(uint8_t mode);
  virtual void writeModeVisible(uint8_t state);

 protected:
  uint32_t ticker;
  uint16_t iconAssets[INDICATOR_MAX + 1];
};

#endif  // DASHBOARDVIEW_HPP
