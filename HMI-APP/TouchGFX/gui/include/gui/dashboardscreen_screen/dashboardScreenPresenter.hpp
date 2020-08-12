#ifndef DASHBOARDSCREENPRESENTER_HPP
#define DASHBOARDSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class dashboardScreenView;

class dashboardScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    dashboardScreenPresenter(dashboardScreenView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~dashboardScreenPresenter() {};
	
    virtual void indicatorChanged(uint8_t index);
	virtual void seinChanged(uint8_t leftSide, uint8_t state);
	virtual void speedChanged(uint8_t value);
	virtual void engineRotationChanged(uint32_t value);
	virtual void batteryChanged(uint8_t percent);
	virtual void signalChanged(uint8_t percent);
	virtual void driveModeChanged(uint8_t index);
	virtual void tripModeChanged(uint8_t index);
	virtual void tripValueChanged(uint32_t value);
	virtual void reportModeChanged(uint8_t index);
	virtual void reportValueChanged(uint16_t value);
private:
    dashboardScreenPresenter();

    dashboardScreenView& view;
};

#endif // DASHBOARDSCREENPRESENTER_HPP
