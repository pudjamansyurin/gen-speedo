#include <gui/screen1_screen/Screen1View.hpp>
#include <math.h>

// 1 rpm = (pi/4)/7000;
static const float piRpm = M_PI_2 / 7000;

Screen1View::Screen1View() :
    ticker(0),
    odometer(0),
    tripmeter(0),
    rpmmeter(0)
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
    if(ticker % 50 == 0) {
        keylessKey.setVisible(!keylessKey.isVisible());
        keylessKey.invalidate();
    }
    if(ticker % 40 == 0) {
        mirrorPhone.setVisible(!mirrorPhone.isVisible());
        mirrorPhone.invalidate();
    }
    if(ticker % 30 == 0) {
        fingerScan.setVisible(!fingerScan.isVisible());
        fingerScan.invalidate();
    }
    if(ticker % 10 == 0) {
        if(odometer > 99999) {
            odometer = 0;
        } else  {
            odometer++;
        }

        Unicode::snprintf(odomValueBuffer, ODOMVALUE_SIZE, "%05d", odometer);
        odomValue.invalidate();
    }
    if(ticker % 3 == 0) {
        if(tripmeter > 99999) {
            tripmeter = 0;
        } else  {
            tripmeter++;
        }
        Unicode::snprintf(tripValueBuffer, TRIPVALUE_SIZE, "%05d", tripmeter);
        tripValue.invalidate();
    }
    if(ticker % 2 == 0) {
        if(rpmmeter > 9000) {
            rpmmeter = 0;
        } else  {
            rpmmeter+=50;
        }
        speedoMeter.updateAngles(0.000f, 0.000f, (piRpm * rpmmeter) - M_PI_2);
        speedoMeter.invalidate();
    }
}
