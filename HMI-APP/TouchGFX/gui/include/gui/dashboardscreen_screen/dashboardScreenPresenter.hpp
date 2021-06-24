#ifndef DASHBOARDSCREENPRESENTER_HPP
#define DASHBOARDSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class dashboardScreenView;

class dashboardScreenPresenter : public touchgfx::Presenter,
                                 public ModelListener {
 public:
  dashboardScreenPresenter(dashboardScreenView& v);

  /**
   * The activate function is called automatically when this screen is "switched
   * in" (ie. made active). Initialization logic can be placed here.
   */
  virtual void activate();

  /**
   * The deactivate function is called automatically when this screen is
   * "switched out" (ie. made inactive). Teardown functionality can be placed
   * here.
   */
  virtual void deactivate();

  virtual ~dashboardScreenPresenter(){};

  virtual void setSeinLeft(uint8_t state);
  virtual void setSeinRight(uint8_t state);
  virtual void setSpeed(uint8_t value);
  virtual void setDiscur(uint8_t value);
  virtual void setState(int8_t value);
  virtual void setBmsState(uint8_t value);
  virtual void setMcuState(uint8_t value);
  virtual void setScanningState(uint8_t value);
  virtual void setCanState(uint8_t value);
  virtual void setBattery(uint8_t percent);
  virtual void setSignal(uint8_t percent);
  virtual void setIndicator(uint8_t index);
  virtual void setDriveMode(uint8_t index);
  virtual void setTripMode(uint8_t index);
  virtual void setTripValue(uint16_t value);
  virtual void setPredictionMode(uint8_t index, uint16_t value);

  virtual void setModeSelector(uint8_t mode);
  virtual void setModeSession(uint8_t state);

  uint8_t getCurrentIndicator();
  virtual uint8_t getIndicatorState(uint8_t index);

 private:
  dashboardScreenPresenter();

  dashboardScreenView& view;
};

#endif  // DASHBOARDSCREENPRESENTER_HPP
