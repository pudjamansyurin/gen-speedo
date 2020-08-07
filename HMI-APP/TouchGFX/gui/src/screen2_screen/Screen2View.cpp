#include <gui/screen2_screen/Screen2View.hpp>
#include <math.h>

Screen2View::Screen2View() : 
    ticker(0.0f)
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
    ticker += 0.0174f;
	
	if((ticker*ticker*ticker) < (M_PI * 20)) {
		mainLogo.updateAngles(0.000f, (ticker*ticker*ticker) , 0.000f);
		mainLogo.setAlpha(ticker*50 >= 0xFF ? 0xFF : ticker*50);
		mainLogo.invalidate();
	} 
	else if((ticker*ticker*ticker) < (M_PI*40)) {
		mainLogo.updateAngles(0.000f, 0.000f , 0.000f);
		mainLogo.invalidate();		
	} else {
		switchScreen();
	}
}