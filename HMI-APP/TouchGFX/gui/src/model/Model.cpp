#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#if !defined(SIMULATOR) || defined(LCD_TESTING)
extern "C"
{
#include "Libs/_utils.h"
#include "Nodes/VCU.h"
#include "Nodes/HMI1.h"
#include "Nodes/BMS.h"
#include "Nodes/MCU.h"
}
#else
vcu_t VCU;
bms_t BMS;
mcu_t MCU;
hmi1_t HMI1;
#endif

Model::Model()
:
        modelListener(0), ticker(0), indicator(1), indicators { 0 }
{
#ifdef SIMULATOR
  generateRandomIndicators();

  HMI1.d.hbar.hide = 0;
  HMI1.d.hbar.sel = HBAR_M_DRIVE;
  HMI1.d.hbar.mode[HBAR_M_TRIP] = HBAR_M_TRIP_ODO;
  HMI1.d.hbar.mode[HBAR_M_DRIVE] = HBAR_M_DRIVE_STANDARD;
  HMI1.d.hbar.mode[HBAR_M_REPORT] = HBAR_M_REPORT_RANGE;
#endif
}

void Model::tick()
{
  ticker++;

#ifdef SIMULATOR
  if (ticker % 1 == 0) {
    if (VCU.d.speed >= MCU_SPEED_MAX)
      VCU.d.speed = 0;
    else
      VCU.d.speed += 5;

    MCU.d.rpm = VCU.d.speed * MCU_RPM_MAX / MCU_SPEED_MAX;
  }

  if (ticker % 10 == 0)
      HMI1.d.hbar.trip++;

  if (ticker % 15 == 0)
    HMI1.d.hbar.hide = !HMI1.d.hbar.hide;

  if (ticker % 20 == 0) {
    if (HMI1.d.hbar.report >= 255)
      HMI1.d.hbar.report = 0;
    else
      HMI1.d.hbar.report++;
  }

  if(ticker % 30 == 0) {
    if (VCU.d.signal >= 100)
      VCU.d.signal = 0;
    else
      VCU.d.signal++;
  }

  if (ticker % 50 == 0) {
    if (BMS.d.soc >= 100)
      BMS.d.soc = 0;
    else
      BMS.d.soc++;
  }

  if (ticker % 60 == 0) {
    uint8_t max = 0, *mode = NULL;

    HMI1.d.sein.left = !HMI1.d.sein.left;
    HMI1.d.sein.right = !HMI1.d.sein.right;

    switch (HMI1.d.hbar.sel) {
      case HBAR_M_TRIP :
        mode = &HMI1.d.hbar.mode[HBAR_M_TRIP];
        max = HBAR_M_TRIP_MAX - 1;
        break;
      case HBAR_M_DRIVE:
        mode = &HMI1.d.hbar.mode[HBAR_M_DRIVE];
        max = HBAR_M_DRIVE_MAX - 1;
        break;
      case HBAR_M_REPORT:
        mode = &HMI1.d.hbar.mode[HBAR_M_REPORT];
        max = HBAR_M_REPORT_MAX - 1;
        break;
      default:
        break;
    }

    if (*mode >= max)
      *mode = 0;
    else
      (*mode)++;
  }

  if (ticker % (60*2) == 0) {
    if (indicator >= INDICATOR_MAX)
      indicator = 0;
    else
      indicator++;
  }

  if (ticker % (60*3) == 0) {
    if (HMI1.d.hbar.sel >= HBAR_M_MAX)
      HMI1.d.hbar.sel = 0;
    else
      HMI1.d.hbar.sel++;
  }

  if (ticker % (60 * 60) == 0)
    generateRandomIndicators();

  switch (HMI1.d.hbar.sel) {
    case HBAR_M_TRIP :
      modelListener->setTripMode(HMI1.d.hbar.mode[HBAR_M_TRIP]);
      break;
    case HBAR_M_DRIVE:
      modelListener->setDriveMode(HMI1.d.hbar.mode[HBAR_M_DRIVE]);
      break;
    case HBAR_M_REPORT:
      modelListener->setReportMode(HMI1.d.hbar.mode[HBAR_M_REPORT]);
      break;
    default:
      break;
  }
#endif

  // write to LCD
  modelListener->setTripMode(HMI1.d.hbar.mode[HBAR_M_TRIP]);
  modelListener->setDriveMode(HMI1.d.hbar.mode[HBAR_M_DRIVE]);
  modelListener->setReportMode(HMI1.d.hbar.mode[HBAR_M_REPORT]);

  modelListener->setSpeed(VCU.d.speed);
  modelListener->setEngineRotation(MCU.d.rpm);

  modelListener->setTripValue(HMI1.d.hbar.trip);
  modelListener->setReportValue(HMI1.d.hbar.report);

  modelListener->setSignal(VCU.d.signal);
  modelListener->setBattery(BMS.d.soc);

  modelListener->setSeinLeft(HMI1.d.sein.left);
  modelListener->setSeinRight(HMI1.d.sein.right);

  modelListener->setIndicator(indicator);

  modelListener->setModeSelector(HMI1.d.hbar.sel);
  modelListener->setModeVisible(!HMI1.d.hbar.hide);

  if (ticker % (60 * 2) == 0)
    swipeIndicator();
}

uint8_t Model::readCurrentIndicator()
{
  return indicator;
}

uint8_t Model::readIndicatorState(uint8_t index)
{
  return indicators[index];
}

#ifdef SIMULATOR
void Model::generateRandomIndicators()
{
  HMI1.d.state.abs = rand() & 1;
  HMI1.d.state.mirroring = rand() & 1;
  HMI1.d.state.lamp = rand() & 1;
  HMI1.d.state.warning = rand() & 1;
  HMI1.d.state.overheat = rand() & 1;
  HMI1.d.state.unfinger = rand() & 1;
  HMI1.d.state.unremote = rand() & 1;
  HMI1.d.state.daylight = rand() & 1;
  HMI1.d.hbar.reverse = rand() & 1;
}
#endif

void Model::reloadIndicators()
{
  uint8_t errors = 0;

  indicators[INDICATOR_ABS] = HMI1.d.state.abs;
  indicators[INDICATOR_MIRRORING] = HMI1.d.state.mirroring;
  indicators[INDICATOR_LAMP] = HMI1.d.state.lamp;
  indicators[INDICATOR_WARNING] = HMI1.d.state.warning;
  indicators[INDICATOR_OVERHEAT] = HMI1.d.state.overheat;
  indicators[INDICATOR_FINGER] = HMI1.d.state.unfinger;
  indicators[INDICATOR_UNREMOTE] = HMI1.d.state.unremote;
  indicators[INDICATOR_LOWBAT] = BMS.d.soc < 20;

  for (uint8_t i = INDICATOR_GO; i < INDICATOR_MAX; ++i) {
    if (indicators[i]) {
      errors = 1;
      break;
    }
  }

  indicators[INDICATOR_REVERSE] = HMI1.d.hbar.reverse;
  indicators[INDICATOR_GO] = !HMI1.d.hbar.reverse && !errors;
}

void Model::swipeIndicator()
{
  uint8_t i, found = 0;

  // reload data
  reloadIndicators();

  // current -> up
  for (i = indicator + 1; i <= INDICATOR_MAX; i++) {
    if (indicators[i]) {
      found = 1;
      indicator = i;
      break;
    }
  }
  // down -> current
  if (!found) {
    for (i = 0; i <= indicator; i++) {
      if (indicators[i]) {
        found = 1;
        indicator = i;
        break;
      }
    }
  }
  // fall-back
  if (!found)
    indicator = INDICATOR_GO;
}

