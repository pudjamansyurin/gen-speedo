#include <gui/welcomescreen_screen/welcomeScreenView.hpp>

static uint8_t alpha;

welcomeScreenView::welcomeScreenView()
	: ticker(0)
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
	genMotor.setAlpha(alpha);
	genMotor.invalidate();
}

void welcomeScreenView::handleTickEvent() {
	// increment the ticker
	if(ticker < 200) {
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
