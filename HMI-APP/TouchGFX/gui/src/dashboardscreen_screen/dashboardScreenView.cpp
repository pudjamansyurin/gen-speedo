#include <gui/dashboardscreen_screen/dashboardScreenView.hpp>
#include <touchgfx/Color.hpp>

#include "BitmapDatabase.hpp"

touchgfx::Container *modeContainer[HBAR_M_MAX];
uint8_t modeSelected = HBAR_M_DRIVE;
uint8_t modeVisible = 1;
uint8_t animationSpeed = 10;

uint8_t iconImageSwiper = 0;
uint8_t tripModeSwiper = 0;
uint8_t driveModeSwiper = 0;
// uint8_t predictionModeSwiper = 0;

touchgfx::TextAreaWithOneWildcard *pReportValueText;
touchgfx::Unicode::UnicodeChar *pReportValueTextBuffer;

position_t posIndicator;
icon_t prevIndicator, nextIndicator;

drive_t M_DRIVE;
trip_t M_TRIP;
prediction_t M_PREDICTION;

dashboardScreenView::dashboardScreenView()
    : ticker(0),
      iconAssets{
          BITMAP_MAINREVERSE_ID,
          BITMAP_MAINGO_ID,
          BITMAP_NONE_ID,
          BITMAP_BRAKESYSTEMALERT_ID,
          BITMAP_SMARTPHONEMIRRORINGSTATUS_ID,
          BITMAP_HIGHBEAMACTIVATED_ID,
          BITMAP_ELECTRONICERRORMESSAGE_ID,
          BITMAP_COOLANTTEMPERATUREWARNING_ID,
          BITMAP_FINGERSCANLOGINSTATUS_ID,
          BITMAP_KEYLESSIGNITIONKEYDETECTION_ID,
          BITMAP_BATTERYDRAINOUT_ID,
      } {
  posIndicator.prev.x = 0 - prevIconContainer.getWidth();
  posIndicator.prev.y = iconContainer.getHeight() / 5;
  posIndicator.current.x =
      (iconContainer.getWidth() - prevIconContainer.getWidth()) / 2;
  posIndicator.current.y =
      (iconContainer.getHeight() - prevIconContainer.getHeight()) / 2;
  posIndicator.next.x =
      iconContainer.getWidth();  // - prevIconContainer.getWidth();
  posIndicator.next.y = iconContainer.getHeight() / 5;

  modeContainer[HBAR_M_TRIP] = &tripModeContainer;
  modeContainer[HBAR_M_DRIVE] = &driveModeContainer;
  modeContainer[HBAR_M_PREDICTION] = &reportModeContainer;

  M_DRIVE.color[HBAR_M_DRIVE_ECONOMY] =
      Color::getColorFrom24BitRGB(255, 255, 0);
  M_DRIVE.color[HBAR_M_DRIVE_STANDARD] = Color::getColorFrom24BitRGB(0, 255, 0);
  M_DRIVE.color[HBAR_M_DRIVE_SPORT] = Color::getColorFrom24BitRGB(255, 0, 0);

  touchgfx::Unicode::strncpy(M_DRIVE.mode[HBAR_M_DRIVE_ECONOMY], "ECONOMIC",
                             NEXTDRIVEMODETEXT_SIZE);
  touchgfx::Unicode::strncpy(M_DRIVE.mode[HBAR_M_DRIVE_STANDARD], "STANDARD",
                             NEXTDRIVEMODETEXT_SIZE);
  touchgfx::Unicode::strncpy(M_DRIVE.mode[HBAR_M_DRIVE_SPORT], "SPORT",
                             NEXTDRIVEMODETEXT_SIZE);

  touchgfx::Unicode::strncpy(M_TRIP.mode[HBAR_M_TRIP_A], "TRIP A",
                             NEXTTRIPMODETEXT_SIZE);
  touchgfx::Unicode::strncpy(M_TRIP.mode[HBAR_M_TRIP_B], "TRIP B",
                             NEXTTRIPMODETEXT_SIZE);
  touchgfx::Unicode::strncpy(M_TRIP.mode[HBAR_M_TRIP_ODO], "ODO",
                             NEXTTRIPMODETEXT_SIZE);

  M_PREDICTION.pValueText[HBAR_M_PREDICTION_RANGE] = &prevReportValueText;
  M_PREDICTION.pValueText[HBAR_M_PREDICTION_EFFICIENCY] =
      &nextReportValueText;
  M_PREDICTION.pValueTextBuffer[HBAR_M_PREDICTION_RANGE] =
      prevReportValueTextBuffer;
  M_PREDICTION.pValueTextBuffer[HBAR_M_PREDICTION_EFFICIENCY] =
      nextReportValueTextBuffer;
}

void dashboardScreenView::setupScreen() {
  dashboardScreenViewBase::setupScreen();
}

void dashboardScreenView::tearDownScreen() {
  dashboardScreenViewBase::tearDownScreen();
}

void dashboardScreenView::handleTickEvent() {
  uint8_t curIndicator = presenter->getCurrentIndicator();

  if (nextIndicator.container != NULL) {
    if (!nextIndicator.container->isMoveAnimationRunning()) {
      ticker++;

      if (curIndicator == INDICATOR_LOWBAT ||
          curIndicator == INDICATOR_WARNING) {
        if (ticker % 10 == 0) {
          nextIndicator.container->setVisible(
              !nextIndicator.container->isVisible());
          nextIndicator.container->invalidate();
        }
      }

      if (curIndicator == INDICATOR_FINGER ||
          curIndicator == INDICATOR_MIRRORING ||
          curIndicator == INDICATOR_UNREMOTE) {
        if (ticker == 45) {
          nextIndicator.container->setVisible(false);
          nextIndicator.container->invalidate();
        }
        if (ticker == 55) {
          nextIndicator.container->setVisible(true);
          nextIndicator.container->invalidate();
        }
      }
    } else {
      ticker = 0;

      if (!nextIndicator.container->isVisible()) {
        nextIndicator.container->setVisible(true);
        nextIndicator.container->invalidate();
      }
    }
  }
}

void dashboardScreenView::writeModeSelector(uint8_t mode) {
  for (uint8_t i = 0; i < HBAR_M_MAX; i++) {
    if (i == mode)
      modeSelected = mode;
    else {
      modeContainer[i]->setVisible(true);
      modeContainer[i]->invalidate();
    }
  }
}
void dashboardScreenView::writeModeVisible(uint8_t state) {
  modeContainer[modeSelected]->setVisible(state);
  modeContainer[modeSelected]->invalidate();
}

void dashboardScreenView::writeSein(uint8_t leftSide, uint8_t state) {
  Image *sein = leftSide ? &seinLeft : &seinRight;

  sein->setVisible(state);
  sein->invalidate();
}

void dashboardScreenView::writeSpeed(uint8_t percent) {
  speedProgress.setValue(percent);
  speedProgress.invalidate();
}

void dashboardScreenView::writeDiscur(uint8_t percent) {
  discurProgress.setValue(percent);
  discurProgress.invalidate();
}

void dashboardScreenView::writeState(int8_t value) {
  Unicode::snprintf(stateValueBuffer, STATEVALUE_SIZE, "%1d", value);
  stateValue.invalidate();
}

void dashboardScreenView::writeBmsState(uint8_t value) {
  Unicode::snprintf(bmsValueBuffer, BMSVALUE_SIZE, "%1d", value);
  bmsValue.invalidate();
}

void dashboardScreenView::writeMcuState(uint8_t value) {
  Unicode::snprintf(mcuValueBuffer, MCUVALUE_SIZE, "%1d", value);
  mcuValue.invalidate();
}

void dashboardScreenView::writeScanningState(uint8_t value) {
  uint8_t show = value & 0x01;
  uint8_t error = value & 0x02;
  uint16_t color = BITMAP_FINGERSCANLOGINSTATUSMINI_ID;

  if (error) color = BITMAP_FINGERSCANLOGINSTATUSMINIRED_ID;

  scanningIcon.setVisible(show);
  scanningIcon.setBitmap(Bitmap(color));
  scanningIcon.invalidate();
}

void dashboardScreenView::writeCanState(uint8_t value) {
  canState.setVisible(!value);
  canState.invalidate();
}

void dashboardScreenView::writeBattery(uint8_t percent) {
  Unicode::snprintf(batteryValueBuffer, BATTERYVALUE_SIZE, "%3d", percent);
  batteryValue.invalidate();
}

void dashboardScreenView::writeSignal(uint8_t percent) {
  Unicode::snprintf(signalValueBuffer, SIGNALVALUE_SIZE, "%3d", percent);
  signalValue.invalidate();
}

void dashboardScreenView::writeIndicator(uint8_t index) {
  prevIndicator.container =
      iconImageSwiper ? &prevIconContainer : &nextIconContainer;
  prevIndicator.image = iconImageSwiper ? &prevIconImage : &nextIconImage;
  nextIndicator.container =
      iconImageSwiper ? &nextIconContainer : &prevIconContainer;
  nextIndicator.image = iconImageSwiper ? &nextIconImage : &prevIconImage;

  nextIndicator.image->setBitmap(Bitmap(iconAssets[index]));
  nextIndicator.image->setXY(
      (nextIndicator.container->getWidth() - nextIndicator.image->getWidth()) /
          2,
      (nextIndicator.container->getHeight() -
       nextIndicator.image->getHeight()) /
          2);

  //	nextIndicator.container->setXY(posIndicator.current.x,
  // posIndicator.current.y);
  nextIndicator.container->setXY(posIndicator.next.x, posIndicator.next.y);
  nextIndicator.container->startMoveAnimation(
      posIndicator.current.x, posIndicator.current.y, animationSpeed,
      EasingEquations::linearEaseOut, EasingEquations::linearEaseOut);

  prevIndicator.container->setVisible(true);
  //	prevIndicator.container->setXY(posIndicator.prev.x,
  // posIndicator.prev.y);
  prevIndicator.container->startMoveAnimation(
      posIndicator.prev.x, posIndicator.prev.y, animationSpeed,
      EasingEquations::linearEaseOut, EasingEquations::linearEaseOut);

  nextIndicator.container->invalidate();
  prevIndicator.container->invalidate();

  iconImageSwiper = !iconImageSwiper;
}

void dashboardScreenView::writeDriveMode(uint8_t index) {
  MoveAnimator<touchgfx::TextAreaWithOneWildcard> *prevText =
      driveModeSwiper ? &prevDriveModeText : &nextDriveModeText;
  MoveAnimator<touchgfx::TextAreaWithOneWildcard> *nextText =
      driveModeSwiper ? &nextDriveModeText : &prevDriveModeText;
  Unicode::UnicodeChar *nextBuffer =
      driveModeSwiper ? nextDriveModeTextBuffer : prevDriveModeTextBuffer;

  touchgfx::Unicode::snprintf(nextBuffer, NEXTDRIVEMODETEXT_SIZE, "%s",
                              M_DRIVE.mode[index]);
  nextText->setColor(M_DRIVE.color[index]);

  nextText->setXY(0, 0 - driveModeContainer.getHeight());
  nextText->startMoveAnimation(0, 0, animationSpeed,
                               EasingEquations::linearEaseOut,
                               EasingEquations::linearEaseOut);
  nextText->invalidate();

  prevText->startMoveAnimation(0, driveModeContainer.getHeight(),
                               animationSpeed, EasingEquations::linearEaseOut,
                               EasingEquations::linearEaseOut);
  prevText->invalidate();

  driveModeSwiper = !driveModeSwiper;
}

void dashboardScreenView::writeTripMode(uint8_t index) {
  MoveAnimator<touchgfx::TextAreaWithOneWildcard> *prevText =
      tripModeSwiper ? &prevTripModeText : &nextTripModeText;
  MoveAnimator<touchgfx::TextAreaWithOneWildcard> *nextText =
      tripModeSwiper ? &nextTripModeText : &prevTripModeText;
  Unicode::UnicodeChar *nextBuffer =
      tripModeSwiper ? nextTripModeTextBuffer : prevTripModeTextBuffer;

  touchgfx::Unicode::snprintf(nextBuffer, NEXTTRIPMODETEXT_SIZE, "%s",
                              M_TRIP.mode[index]);

  nextText->setXY(0, 0 - tripModeContainer.getHeight());
  nextText->startMoveAnimation(0, 0, animationSpeed,
                               EasingEquations::linearEaseOut,
                               EasingEquations::linearEaseOut);
  nextText->invalidate();

  prevText->startMoveAnimation(0, tripModeContainer.getHeight(), animationSpeed,
                               EasingEquations::linearEaseOut,
                               EasingEquations::linearEaseOut);
  prevText->invalidate();

  tripModeSwiper = !tripModeSwiper;
}

void dashboardScreenView::writeTripValue(uint16_t value) {
  Unicode::snprintf(tripValueBuffer, TRIPVALUE_SIZE, "%06d", value);
  tripValue.invalidate();
}

void dashboardScreenView::writePredictionMode(uint8_t index) {
  MoveAnimator<touchgfx::Container> *prevContainer =
      index ? &prevReportModeContainer : &nextReportModeContainer;
  MoveAnimator<touchgfx::Container> *nextContainer =
      index ? &nextReportModeContainer : &prevReportModeContainer;

  pReportValueText = M_PREDICTION.pValueText[index];
  pReportValueTextBuffer = M_PREDICTION.pValueTextBuffer[index];

  nextContainer->setXY(0, 0 - reportModeContainer.getHeight());
  nextContainer->startMoveAnimation(0, 0, animationSpeed,
                                    EasingEquations::linearEaseOut,
                                    EasingEquations::linearEaseOut);
  nextContainer->invalidate();

  prevContainer->startMoveAnimation(
      0, reportModeContainer.getHeight(), animationSpeed,
      EasingEquations::linearEaseOut, EasingEquations::linearEaseOut);
  prevContainer->invalidate();

  //  predictionModeSwiper = !predictionModeSwiper;
}

void dashboardScreenView::writePredictionValue(uint16_t value) {
  if (pReportValueTextBuffer != NULL) {
    Unicode::snprintf(pReportValueTextBuffer, NEXTREPORTVALUETEXT_SIZE,
                      "%03d", value);
    pReportValueText->invalidate();
  }
}
