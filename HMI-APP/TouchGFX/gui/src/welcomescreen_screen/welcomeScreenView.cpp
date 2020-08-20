#include <gui/welcomescreen_screen/welcomeScreenView.hpp>

#if !defined(SIMULATOR) || defined(LCD_TESTING)
extern "C"
{
    #include "Libs/_utils.h"
}
#endif

static uint8_t alpha;

welcomeScreenView::welcomeScreenView()
	: ticker(-10)
{

}

void welcomeScreenView::setupScreen()
{
    welcomeScreenViewBase::setupScreen();
}

void welcomeScreenView::tearDownScreen()
{
    welcomeScreenViewBase::tearDownScreen();
}

void welcomeScreenView::setLogoTransparency(uint8_t alpha)
{
    static uint8_t init = 1, _alpha;

    if (init || _alpha != alpha) {
        _alpha = alpha;
        init = 0;
        genMotor.setAlpha(alpha);
        genMotor.invalidate();
    }
}

void welcomeScreenView::handleTickEvent() {
	// increment the ticker
    if (ticker < 0) {
        ticker++;

#if !defined(SIMULATOR) || defined(LCD_TESTING)
        if (ticker == -5) {
            _LcdPower(1);
        }
#endif
    } else {
        if (ticker < 200) {
            ticker += 4;
        }
        else if(ticker < 350) {
            ticker += 4;
        }
        else {
            ticker += 25;
        }

        // calculate the alpha value
        if(ticker < 200){
            alpha = ticker;
        }
        else if (ticker < 350) {
            alpha = 400-ticker;
        }
        else if (ticker < 555) {
            alpha = ticker-300;
        }
        else if (ticker < 555+1000) {
            alpha = 255;
        } else {
            switchScreen();
            return;
        }

        setLogoTransparency(alpha);
    }
}
