#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

class ModelListener
{
public:
  ModelListener() : model(0) {}

  virtual ~ModelListener() {}

  void bind(Model* m)
  {
    model = m;
  }

  virtual void setIndicator(uint8_t index) {};
  virtual void setSeinLeft(uint8_t state) {};
  virtual void setSeinRight(uint8_t state) {};
  virtual void setSpeed(uint8_t value) {};
  virtual void setDiscur(uint8_t value) {};
  virtual void setFps(uint8_t value) {};
  virtual void setState(int8_t value) {};
  virtual void setBmsState(uint8_t value) {};
  virtual void setMcuState(uint8_t value) {};
  virtual void setRegisteringState(uint8_t value) {};
  virtual void setBattery(uint8_t percent) {};
  virtual void setSignal(uint8_t percent) {};
  virtual void setDriveMode(uint8_t index) {};
  virtual void setTripMode(uint8_t index) {};
  virtual void setTripValue(uint16_t value) {};
  virtual void setReportMode(uint8_t index, uint16_t value) {};

  virtual void setModeSelector(uint8_t mode) {};
  virtual void setModeSession(uint8_t state) {};
protected:
  Model* model;
};

#endif // MODELLISTENER_HPP
