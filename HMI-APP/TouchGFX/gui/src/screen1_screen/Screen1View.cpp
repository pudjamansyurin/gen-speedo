#include <gui/screen1_screen/Screen1View.hpp>

//static collection_t COL = {
//        .report = {
//                .mode = { "RANGE", "AVG" },
//                .unit = { "KM", "KM/KWH" },
//        },
//        .drive = {
//                .mode = { "ECONOMIC", "SPORT", "PERSONAL", "STANDARD" }
//        }
//};

Screen1View::Screen1View() :
        ticker(0),
        _tripValue(0),
        _engineValue(0),
        _batteryValue(0),
        _signalValue(0),
        _speedValue(0)
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
        seinRight.setVisible(!seinRight.isVisible());
        seinLeft.invalidate();
        seinRight.invalidate();
    }
    if(ticker % 50 == 0) {
        if(_batteryValue > 99) {
            _batteryValue = 0;
        } else  {
            _batteryValue++;
        }

        Unicode::snprintf(batteryValueBuffer, BATTERYVALUE_SIZE, "%3d", _batteryValue);
        batteryValue.invalidate();
    }
    if(ticker % 30 == 0) {
        if(_signalValue > 99) {
            _signalValue = 0;
        } else  {
            _signalValue++;
        }

        Unicode::snprintf(signalValueBuffer, SIGNALVALUE_SIZE, "%3d", _signalValue);
        signalValue.invalidate();
    }
    if(ticker % 10 == 0) {
        if(_tripValue > 999999) {
            _tripValue = 0;
        } else  {
            _tripValue++;
        }

        Unicode::snprintf(tripValueBuffer, TRIPVALUE_SIZE, "%06d", _tripValue);
        tripValue.invalidate();
    }

    if(ticker % 40 == 0) {
        if(_speedValue > 140) {
            _speedValue = 0;
        } else  {
            _speedValue++;
        }
    }
    if(ticker % 2 == 0) {
        if(_engineValue > 9000) {
            _engineValue = 0;
        } else  {
            _engineValue+=50;
        }
    }
}
