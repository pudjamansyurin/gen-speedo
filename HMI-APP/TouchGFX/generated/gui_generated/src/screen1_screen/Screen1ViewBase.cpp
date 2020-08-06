/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include "BitmapDatabase.hpp"

Screen1ViewBase::Screen1ViewBase()
{

    touchgfx::CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);

    frame.setPosition(0, 0, 800, 480);

    background.setPosition(-1, -1, 800, 480);
    background.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    frame.add(background);

    tripUnit.setXY(292, 114);
    tripUnit.setColor(touchgfx::Color::getColorFrom24BitRGB(128, 128, 128));
    tripUnit.setLinespacing(0);
    tripUnit.setTypedText(touchgfx::TypedText(T_SINGLEUSEID1));
    frame.add(tripUnit);

    signalPercent.setXY(485, 61);
    signalPercent.setColor(touchgfx::Color::getColorFrom24BitRGB(179, 179, 179));
    signalPercent.setLinespacing(0);
    signalPercent.setTypedText(touchgfx::TypedText(T_SINGLEUSEID9));
    frame.add(signalPercent);

    batteryPercent.setXY(377, 61);
    batteryPercent.setColor(touchgfx::Color::getColorFrom24BitRGB(179, 179, 179));
    batteryPercent.setLinespacing(0);
    batteryPercent.setTypedText(touchgfx::TypedText(T_SINGLEUSEID10));
    frame.add(batteryPercent);

    signalIcon.setXY(412, 62);
    signalIcon.setBitmap(touchgfx::Bitmap(BITMAP_SIGNALICON_ID));
    frame.add(signalIcon);

    batteryIcon.setXY(302, 63);
    batteryIcon.setBitmap(touchgfx::Bitmap(BITMAP_BATTERYICON_ID));
    frame.add(batteryIcon);

    backgroundRight.setXY(556, 54);
    backgroundRight.setBitmap(touchgfx::Bitmap(BITMAP_BACKGROUNDRIGHT_ID));
    frame.add(backgroundRight);

    backgroundLeft.setXY(0, 54);
    backgroundLeft.setBitmap(touchgfx::Bitmap(BITMAP_BACKGROUNDLEFT_ID));
    frame.add(backgroundLeft);

    tripContainer.setXY(364, 98);
    tripContainer.setBitmap(touchgfx::Bitmap(BITMAP_TRIPCONTAINER_ID));
    frame.add(tripContainer);

    modeContainer.setXY(277, 364);
    modeContainer.setBitmap(touchgfx::Bitmap(BITMAP_MODECONTAINER_ID));
    frame.add(modeContainer);

    indicator.setPosition(274, 114, 250, 250);

    batteryLow.setXY(24, 67);
    batteryLow.setVisible(false);
    batteryLow.setBitmap(touchgfx::Bitmap(BITMAP_BATTERYDRAINOUT_ID));
    indicator.add(batteryLow);

    brakeAlert.setXY(28, 48);
    brakeAlert.setVisible(false);
    brakeAlert.setBitmap(touchgfx::Bitmap(BITMAP_BRAKESYSTEMALERT_ID));
    indicator.add(brakeAlert);

    temperatureWarning.setXY(52, 71);
    temperatureWarning.setVisible(false);
    temperatureWarning.setBitmap(touchgfx::Bitmap(BITMAP_COOLANTTEMPERATUREWARNING_ID));
    indicator.add(temperatureWarning);

    errorMessage.setXY(52, 63);
    errorMessage.setVisible(false);
    errorMessage.setBitmap(touchgfx::Bitmap(BITMAP_ELECTRONICERRORMESSAGE_ID));
    indicator.add(errorMessage);

    fingerScan.setXY(55, 50);
    fingerScan.setVisible(false);
    fingerScan.setBitmap(touchgfx::Bitmap(BITMAP_FINGERSCANLOGINSTATUS_ID));
    indicator.add(fingerScan);

    beamActivated.setXY(33, 64);
    beamActivated.setVisible(false);
    beamActivated.setBitmap(touchgfx::Bitmap(BITMAP_HIGHBEAMACTIVATED_ID));
    indicator.add(beamActivated);

    keylessKey.setXY(34, 55);
    keylessKey.setVisible(false);
    keylessKey.setBitmap(touchgfx::Bitmap(BITMAP_KEYLESSIGNITIONKEYDETECTION_ID));
    indicator.add(keylessKey);

    phoneMirroring.setXY(33, 63);
    phoneMirroring.setVisible(false);
    phoneMirroring.setBitmap(touchgfx::Bitmap(BITMAP_SMARTPHONEMIRRORINGSTATUS_ID));
    indicator.add(phoneMirroring);

    mainGo.setXY(21, 86);
    mainGo.setBitmap(touchgfx::Bitmap(BITMAP_MAINGO_ID));
    indicator.add(mainGo);

    mainReverse.setXY(76, 86);
    mainReverse.setVisible(false);
    mainReverse.setBitmap(touchgfx::Bitmap(BITMAP_MAINREVERSE_ID));
    indicator.add(mainReverse);

    circleLeft.setPosition(-126, 124, 2, 2);
    circleLeft.setCenter(40, 40);
    circleLeft.setRadius(40);
    circleLeft.setLineWidth(0);
    circleLeft.setArc(0, 360);
    circleLeftPainter.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    circleLeft.setPainter(circleLeftPainter);
    indicator.add(circleLeft);

    circleRight.setPosition(376, 124, 2, 2);
    circleRight.setCenter(40, 40);
    circleRight.setRadius(40);
    circleRight.setLineWidth(0);
    circleRight.setArc(0, 360);
    circleRightPainter.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    circleRight.setPainter(circleRightPainter);
    indicator.add(circleRight);

    leftBar.setPosition(105, 57, 137, 0);

    speedLevel.setXY(0, 0);
    speedLevel.setBitmap(touchgfx::Bitmap(BITMAP_SPEEDLEVEL_ID));
    leftBar.add(speedLevel);

    reportValue.setPosition(361, 406, 151, 18);
    reportValue.setColor(touchgfx::Color::getColorFrom24BitRGB(179, 179, 179));
    reportValue.setLinespacing(0);
    Unicode::snprintf(reportValueBuffer, REPORTVALUE_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID17).getText());
    reportValue.setWildcard(reportValueBuffer);
    reportValue.setTypedText(touchgfx::TypedText(T_SINGLEUSEID8));

    reportMode.setXY(285, 406);
    reportMode.setColor(touchgfx::Color::getColorFrom24BitRGB(179, 179, 179));
    reportMode.setLinespacing(0);
    Unicode::snprintf(reportModeBuffer, REPORTMODE_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID16).getText());
    reportMode.setWildcard(reportModeBuffer);
    reportMode.resizeToCurrentText();
    reportMode.setTypedText(touchgfx::TypedText(T_SINGLEUSEID7));

    driveMode.setPosition(288, 369, 222, 19);
    driveMode.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 255, 0));
    driveMode.setLinespacing(0);
    Unicode::snprintf(driveModeBuffer, DRIVEMODE_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID15).getText());
    driveMode.setWildcard(driveModeBuffer);
    driveMode.setTypedText(touchgfx::TypedText(T_SINGLEUSEID2));

    tripValue.setPosition(374, 102, 119, 20);
    tripValue.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    tripValue.setLinespacing(0);
    Unicode::snprintf(tripValueBuffer, TRIPVALUE_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID11).getText());
    tripValue.setWildcard(tripValueBuffer);
    tripValue.setTypedText(touchgfx::TypedText(T_SINGLEUSEID3));

    tripMode.setPosition(269, 93, 79, 20);
    tripMode.setColor(touchgfx::Color::getColorFrom24BitRGB(128, 128, 128));
    tripMode.setLinespacing(0);
    Unicode::snprintf(tripModeBuffer, TRIPMODE_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID14).getText());
    tripMode.setWildcard(tripModeBuffer);
    tripMode.setTypedText(touchgfx::TypedText(T_SINGLEUSEID6));

    signalValue.setPosition(443, 61, 39, 20);
    signalValue.setColor(touchgfx::Color::getColorFrom24BitRGB(179, 179, 179));
    signalValue.setLinespacing(0);
    Unicode::snprintf(signalValueBuffer, SIGNALVALUE_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID13).getText());
    signalValue.setWildcard(signalValueBuffer);
    signalValue.setTypedText(touchgfx::TypedText(T_SINGLEUSEID4));

    batteryValue.setPosition(335, 61, 39, 20);
    batteryValue.setColor(touchgfx::Color::getColorFrom24BitRGB(179, 179, 179));
    batteryValue.setLinespacing(0);
    Unicode::snprintf(batteryValueBuffer, BATTERYVALUE_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID12).getText());
    batteryValue.setWildcard(batteryValueBuffer);
    batteryValue.setTypedText(touchgfx::TypedText(T_SINGLEUSEID5));

    engineRotation.setXY(558, 57);
    engineRotation.setBitmap(touchgfx::Bitmap(BITMAP_ENGINEROTATIONFLIPPED_ID));

    seinLeft.setXY(152, 67);
    seinLeft.setBitmap(touchgfx::Bitmap(BITMAP_SEINLEFT_ID));

    seinRight.setXY(567, 67);
    seinRight.setBitmap(touchgfx::Bitmap(BITMAP_SEINRIGHTFLIPPED_ID));

    add(frame);
    add(indicator);
    add(leftBar);
    add(reportValue);
    add(reportMode);
    add(driveMode);
    add(tripValue);
    add(tripMode);
    add(signalValue);
    add(batteryValue);
    add(engineRotation);
    add(seinLeft);
    add(seinRight);
}

void Screen1ViewBase::setupScreen()
{

}
