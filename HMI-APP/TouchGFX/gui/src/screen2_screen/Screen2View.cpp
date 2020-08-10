#include <gui/screen2_screen/Screen2View.hpp>

Screen2View::Screen2View() : 
    ticker(0)
{

}

void Screen2View::setupScreen()
{
    Screen2ViewBase::setupScreen();
}

void Screen2View::tearDownScreen()
{
    Screen2ViewBase::tearDownScreen();
}


void Screen2View::handleTickEvent() {
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