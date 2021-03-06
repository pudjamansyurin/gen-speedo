#include <gui/dashboardscreen_screen/dashboardScreenPresenter.hpp>
#include <gui/dashboardscreen_screen/dashboardScreenView.hpp>

dashboardScreenPresenter::dashboardScreenPresenter(dashboardScreenView& v)
    : view(v) {}

void dashboardScreenPresenter::activate() {}

void dashboardScreenPresenter::deactivate() {}

void dashboardScreenPresenter::setSeinLeft(uint8_t value) {
  static uint8_t init = 1, _value;

  if (_value != value || init) {
    init = 0;
    _value = value;
    view.writeSein(1, value);
  }
}
void dashboardScreenPresenter::setSeinRight(uint8_t value) {
  static uint8_t init = 1, _value;

  if (_value != value || init) {
    init = 0;
    _value = value;
    view.writeSein(0, value);
  }
}
void dashboardScreenPresenter::setSpeed(uint8_t value) {
  static uint8_t init = 1, _value;

  if (_value != value || init) {
    init = 0;
    _value = value;
    view.writeSpeed(value * 100 / MCU_SPEED_MAX_KPH);
  }
}
void dashboardScreenPresenter::setDiscur(uint8_t value) {
  static uint8_t init = 1;
  static uint32_t _value;

  if (_value != value || init) {
    init = 0;
    _value = value;
    view.writeDiscur(value * 100 / MCU_DISCUR_MAX);
  }
}
void dashboardScreenPresenter::setState(int8_t value) {
  static uint8_t init = 1;
  static int8_t _value;

  if (_value != value || init) {
    init = 0;
    _value = value;
    view.writeState(value);
  }
}
void dashboardScreenPresenter::setBmsState(uint8_t value) {
  static uint8_t init = 1, _value;

  if (_value != value || init) {
    init = 0;
    _value = value;
    view.writeBmsState(value);
  }
}
void dashboardScreenPresenter::setMcuState(uint8_t value) {
  static uint8_t init = 1, _value;

  if (_value != value || init) {
    init = 0;
    _value = value;
    view.writeMcuState(value);
  }
}
void dashboardScreenPresenter::setScanningState(uint8_t value) {
  static uint8_t init = 1, _value;

  if (_value != value || init) {
    init = 0;
    _value = value;
    view.writeScanningState(value);
  }
}
void dashboardScreenPresenter::setCanState(uint8_t value) {
  static uint8_t init = 1, _value;

  if (_value != value || init) {
    init = 0;
    _value = value;
    view.writeCanState(value);
  }
}
void dashboardScreenPresenter::setBattery(uint8_t percent) {
  static uint8_t init = 1, _percent;

  if (_percent != percent || init) {
    init = 0;
    _percent = percent;
    view.writeBattery(percent);
  }
}
void dashboardScreenPresenter::setSignal(uint8_t percent) {
  static uint8_t init = 1, _percent;

  if (_percent != percent || init) {
    init = 0;
    _percent = percent;
    view.writeSignal(percent);
  }
}
void dashboardScreenPresenter::setIndicator(uint8_t index) {
  static uint8_t init = 1, _index;

  if (_index != index || init) {
    init = 0;
    _index = index;
    view.writeIndicator(index);
  }
}
void dashboardScreenPresenter::setDriveMode(uint8_t index) {
  static uint8_t init = 1, _index;

  if (_index != index || init) {
    init = 0;
    _index = index;
    view.writeDriveMode(index);
    // touchgfx_printf("D = %d\n", index);
  }
}
void dashboardScreenPresenter::setTripMode(uint8_t index) {
  static uint8_t init = 1, _index;

  if (_index != index || init) {
    init = 0;
    _index = index;
    view.writeTripMode(index);
    // touchgfx_printf("T = %d\n", index);
  }
}
void dashboardScreenPresenter::setTripValue(uint16_t value) {
  static uint8_t init = 1;
  static uint16_t _value;

  if (_value != value || init) {
    init = 0;
    _value = value;
    view.writeTripValue(value);
  }
}
void dashboardScreenPresenter::setPredictionMode(uint8_t index,
                                                 uint16_t value) {
  static uint8_t init = 1, _index;

  if (_index != index || init) {
    init = 0;
    _index = index;
    view.writePredictionMode(index);
    view.writePredictionValue(value);
  }

  static uint8_t initVal = 1;
  static uint16_t _value;

  if (_value != value || initVal) {
    initVal = 0;
    _value = value;
    view.writePredictionValue(value);
  }
}
void dashboardScreenPresenter::setModeSelector(uint8_t mode) {
  static uint8_t init = 1, _mode;

  if (_mode != mode || init) {
    init = 0;
    _mode = mode;
    view.writeModeSelector(mode);
  }
}
void dashboardScreenPresenter::setModeSession(uint8_t state) {
  static uint8_t init = 1, _state;

  if (_state != state || init) {
    init = 0;
    _state = state;
    view.writeModeVisible(state);
  }
}

uint8_t dashboardScreenPresenter::getIndicatorState(uint8_t index) {
  return model->readIndicatorState(index);
}
uint8_t dashboardScreenPresenter::getCurrentIndicator() {
  return model->readCurrentIndicator();
}
