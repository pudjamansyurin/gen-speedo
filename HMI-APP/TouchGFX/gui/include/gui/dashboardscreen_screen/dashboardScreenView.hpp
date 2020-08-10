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

    virtual void handleTickEvent();
    virtual void driveWheelUpdateItem(driveWheelContainer& item, int16_t itemIndex);
    virtual void indicatorWheelUpdateItem(indicatorWheelContainer& item, int16_t itemIndex);
protected:
    uint32_t ticker;
	uint8_t indicatorItem;
	uint16_t indicatorList[INDICATOR_MAX];
};

#endif // DASHBOARDVIEW_HPP
