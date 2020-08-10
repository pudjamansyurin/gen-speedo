#include <gui/welcomescreen_screen/welcomeScreenView.hpp>

welcomeScreenView::welcomeScreenView() : 
    ticker(0)
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


void welcomeScreenView::handleTickEvent() {
	uint8_t alpha;
	
	// increment the ticker
	if(ticker < 200) {
		ticker += 3;
	}
	else if(ticker < 350) {
		ticker += 2;
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

	// trigger screen
	genMotor.setAlpha(alpha);
	genMotor.invalidate();
}