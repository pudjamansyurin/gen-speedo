#ifndef WELCOMEVIEW_HPP
#define WELCOMEVIEW_HPP

#include <gui_generated/welcomescreen_screen/welcomeScreenViewBase.hpp>
#include <gui/welcomescreen_screen/welcomeScreenPresenter.hpp>

class welcomeScreenView : public welcomeScreenViewBase
{
public:
    welcomeScreenView();
    virtual ~welcomeScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
	
    virtual void handleTickEvent();
	virtual void setLogoTransparency(uint8_t alpha);
protected:
    uint32_t ticker;
};

#endif // WELCOMEVIEW_HPP
