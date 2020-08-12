#ifndef DASHBOARDVIEW_HPP
#define DASHBOARDVIEW_HPP

#include <gui_generated/dashboardscreen_screen/dashboardScreenViewBase.hpp>
#include <gui/dashboardscreen_screen/dashboardScreenPresenter.hpp>

class dashboardScreenView : public dashboardScreenViewBase
{
public:
    dashboardScreenView();
    virtual ~dashboardScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void driveWheelUpdateItem(driveWheelContainer& item, int16_t itemIndex);
    virtual void indicatorWheelUpdateItem(indicatorWheelContainer& item, int16_t itemIndex);
    virtual void tripWheelUpdateItem(tripWheelContainer& item, int16_t itemIndex);
    virtual void reportWheelUpdateItem(reportWheelContainer& item, int16_t itemIndex);	
	
    virtual void setIndicator(uint8_t index);
	virtual void setSein(uint8_t leftSide, uint8_t state);
	virtual void setSpeed(uint8_t percent);
	virtual void setEngineRotation(uint8_t percent);
	virtual void setBattery(uint8_t percent);
	virtual void setSignal(uint8_t percent);
	virtual void setDriveMode(uint8_t index);
	virtual void setTripMode(uint8_t index);
	virtual void setTripValue(uint32_t value);
	virtual void setReportMode(uint8_t index);
	virtual void setReportValue(uint16_t value);
protected:
};

#endif // DASHBOARDVIEW_HPP
