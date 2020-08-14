#ifndef DASHBOARDVIEW_HPP
#define DASHBOARDVIEW_HPP

#include <gui_generated/dashboardscreen_screen/dashboardScreenViewBase.hpp>
#include <gui/dashboardscreen_screen/dashboardScreenPresenter.hpp>

typedef struct {
	touchgfx::Image *image;
	MoveAnimator< touchgfx::Container > *container;
} icon_t;

typedef struct {
	uint32_t x;
	uint32_t y;
} coordinate_t;

typedef struct {
	coordinate_t prev;
	coordinate_t current;
	coordinate_t next;
} position_t;

class dashboardScreenView : public dashboardScreenViewBase
{
public:
    dashboardScreenView();
    virtual ~dashboardScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
	
    virtual void handleTickEvent();

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
    uint32_t ticker;
	uint16_t iconAssets[INDICATOR_MAX + 1];
};

#endif // DASHBOARDVIEW_HPP
