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

    virtual void indicatorWheelUpdateItem(indicatorWheelContainer& item, int16_t itemIndex);
    virtual void driveWheelUpdateItem(driveWheelContainer& item, int16_t itemIndex);
    virtual void tripWheelUpdateItem(tripWheelContainer& item, int16_t itemIndex);
    virtual void reportWheelUpdateItem(reportWheelContainer& item, int16_t itemIndex);	
	
	virtual void writeSein(uint8_t leftSide, uint8_t state);
	virtual void writeSpeed(uint8_t percent);
	virtual void writeEngineRotation(uint8_t percent);
	virtual void writeBattery(uint8_t percent);
	virtual void writeSignal(uint8_t percent);
    virtual void writeIndicator(uint8_t index);
	virtual void writeDriveMode(uint8_t index);
	virtual void writeTripMode(uint8_t index);
	virtual void writeTripValue(uint32_t value);
	virtual void writeReportMode(uint8_t index);
	virtual void writeReportValue(uint16_t value);
protected:
};

#endif // DASHBOARDVIEW_HPP
