#include <gui/screen1_screen/Screen1View.hpp>

Screen1View::Screen1View() :
    ticker(0),
    odometer(0)
{

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::handleTickEvent() {
    ticker++;

    if(ticker % 60 == 0) {
        seinLeft.setVisible(!seinLeft.isVisible());
        seinLeft.invalidate();
    }
    else if(ticker % 50 == 0) {
        keylessKey.setVisible(!keylessKey.isVisible());
        keylessKey.invalidate();
    }
    else if(ticker % 40 == 0) {
        mirrorPhone.setVisible(!mirrorPhone.isVisible());
        mirrorPhone.invalidate();
    }
    else if(ticker % 30 == 0) {
        fingerScan.setVisible(!fingerScan.isVisible());
        fingerScan.invalidate();
    }
    else if(ticker % 10 == 0) {
        odometer++;
    }
}
