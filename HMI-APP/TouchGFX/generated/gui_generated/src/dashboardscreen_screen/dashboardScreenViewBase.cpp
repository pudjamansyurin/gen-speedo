/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/dashboardscreen_screen/dashboardScreenViewBase.hpp>
#include <touchgfx/Color.hpp>
#include "BitmapDatabase.hpp"
#include <texts/TextKeysAndLanguages.hpp>

dashboardScreenViewBase::dashboardScreenViewBase()
{

    __background.setPosition(0, 0, 800, 480);
    __background.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));

    background.setPosition(-1, -1, 800, 480);
    background.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));

    batteryLow.setXY(298, 181);
    batteryLow.setVisible(false);
    batteryLow.setBitmap(touchgfx::Bitmap(BITMAP_BATTERYDRAINOUT_ID));

    brakeAlert.setXY(302, 162);
    brakeAlert.setVisible(false);
    brakeAlert.setBitmap(touchgfx::Bitmap(BITMAP_BRAKESYSTEMALERT_ID));

    temperatureWarning.setXY(326, 184);
    temperatureWarning.setVisible(false);
    temperatureWarning.setBitmap(touchgfx::Bitmap(BITMAP_COOLANTTEMPERATUREWARNING_ID));

    errorMessage.setXY(326, 177);
    errorMessage.setVisible(false);
    errorMessage.setBitmap(touchgfx::Bitmap(BITMAP_ELECTRONICERRORMESSAGE_ID));

    fingerScan.setXY(329, 164);
    fingerScan.setVisible(false);
    fingerScan.setBitmap(touchgfx::Bitmap(BITMAP_FINGERSCANLOGINSTATUS_ID));

    keylessKey.setXY(308, 169);
    keylessKey.setVisible(false);
    keylessKey.setBitmap(touchgfx::Bitmap(BITMAP_KEYLESSIGNITIONKEYDETECTION_ID));

    beamActivated.setXY(307, 178);
    beamActivated.setVisible(false);
    beamActivated.setBitmap(touchgfx::Bitmap(BITMAP_HIGHBEAMACTIVATED_ID));

    mainGo.setXY(295, 200);
    mainGo.setVisible(false);
    mainGo.setBitmap(touchgfx::Bitmap(BITMAP_MAINGO_ID));

    mainReverse.setXY(350, 200);
    mainReverse.setVisible(false);
    mainReverse.setBitmap(touchgfx::Bitmap(BITMAP_MAINREVERSE_ID));

    phoneMirroring.setXY(307, 177);
    phoneMirroring.setVisible(false);
    phoneMirroring.setBitmap(touchgfx::Bitmap(BITMAP_SMARTPHONEMIRRORINGSTATUS_ID));

    iconContainer.setPosition(146, 132, 508, 230);

    prevIconContainer.setPosition(-230, 0, 230, 230);

    prevIconImage.setXY(9, 75);
    prevIconImage.setBitmap(touchgfx::Bitmap(BITMAP_MAINGO_ID));
    prevIconContainer.add(prevIconImage);
    iconContainer.add(prevIconContainer);

    nextIconContainer.setPosition(508, 0, 230, 230);

    nextIconImage.setXY(9, 75);
    nextIconImage.setBitmap(touchgfx::Bitmap(BITMAP_MAINGO_ID));
    nextIconContainer.add(nextIconImage);
    iconContainer.add(nextIconContainer);

    frameContainer.setPosition(0, 0, 800, 480);

    tripUnit.setXY(292, 114);
    tripUnit.setColor(touchgfx::Color::getColorFrom24BitRGB(128, 128, 128));
    tripUnit.setLinespacing(0);
    tripUnit.setTypedText(touchgfx::TypedText(T_SINGLEUSEID1));
    frameContainer.add(tripUnit);

    signalPercent.setXY(485, 61);
    signalPercent.setColor(touchgfx::Color::getColorFrom24BitRGB(179, 179, 179));
    signalPercent.setLinespacing(0);
    signalPercent.setTypedText(touchgfx::TypedText(T_SINGLEUSEID9));
    frameContainer.add(signalPercent);

    batteryPercent.setXY(377, 61);
    batteryPercent.setColor(touchgfx::Color::getColorFrom24BitRGB(179, 179, 179));
    batteryPercent.setLinespacing(0);
    batteryPercent.setTypedText(touchgfx::TypedText(T_SINGLEUSEID10));
    frameContainer.add(batteryPercent);

    signalIcon.setXY(412, 62);
    signalIcon.setBitmap(touchgfx::Bitmap(BITMAP_SIGNALICON_ID));
    frameContainer.add(signalIcon);

    batteryIcon.setXY(302, 63);
    batteryIcon.setBitmap(touchgfx::Bitmap(BITMAP_BATTERYICON_ID));
    frameContainer.add(batteryIcon);

    backgroundRight.setXY(556, 57);
    backgroundRight.setBitmap(touchgfx::Bitmap(BITMAP_BACKGROUNDRIGHT_ID));
    frameContainer.add(backgroundRight);

    backgroundLeft.setXY(0, 57);
    backgroundLeft.setBitmap(touchgfx::Bitmap(BITMAP_BACKGROUNDLEFT_ID));
    frameContainer.add(backgroundLeft);

    tripBox.setXY(364, 98);
    tripBox.setBitmap(touchgfx::Bitmap(BITMAP_TRIPCONTAINER_ID));
    frameContainer.add(tripBox);

    driveBox.setXY(277, 364);
    driveBox.setBitmap(touchgfx::Bitmap(BITMAP_MODECONTAINER_ID));
    frameContainer.add(driveBox);

    seinLeftContainer.setPosition(152, 67, 80, 355);

    seinLeft.setXY(0, 0);
    seinLeft.setBitmap(touchgfx::Bitmap(BITMAP_SEINLEFT_ID));
    seinLeftContainer.add(seinLeft);

    seinRightContainer.setPosition(567, 67, 80, 355);

    seinRight.setXY(0, 0);
    seinRight.setBitmap(touchgfx::Bitmap(BITMAP_SEINRIGHT_ID));
    seinRightContainer.add(seinRight);

    reportModeContainer.setPosition(285, 406, 227, 18);

    prevReportModeContainer.setPosition(0, 18, 227, 18);

    prevReportUnitText.setPosition(121, 0, 105, 18);
    prevReportUnitText.setColor(touchgfx::Color::getColorFrom24BitRGB(179, 179, 179));
    prevReportUnitText.setLinespacing(0);
    prevReportUnitText.setTypedText(touchgfx::TypedText(T_SINGLEUSEID40));
    prevReportModeContainer.add(prevReportUnitText);

    prevReportModeText.setXY(0, 0);
    prevReportModeText.setColor(touchgfx::Color::getColorFrom24BitRGB(179, 179, 179));
    prevReportModeText.setLinespacing(0);
    prevReportModeText.setTypedText(touchgfx::TypedText(T_SINGLEUSEID38));
    prevReportModeContainer.add(prevReportModeText);

    prevReportValueText.setPosition(137, 0, 50, 18);
    prevReportValueText.setColor(touchgfx::Color::getColorFrom24BitRGB(179, 179, 179));
    prevReportValueText.setLinespacing(0);
    Unicode::snprintf(prevReportValueTextBuffer, PREVREPORTVALUETEXT_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID46).getText());
    prevReportValueText.setWildcard(prevReportValueTextBuffer);
    prevReportValueText.setTypedText(touchgfx::TypedText(T_SINGLEUSEID45));
    prevReportModeContainer.add(prevReportValueText);
    reportModeContainer.add(prevReportModeContainer);

    nextReportModeContainer.setPosition(0, -18, 227, 18);

    nextReportUnitText.setPosition(121, 0, 105, 18);
    nextReportUnitText.setColor(touchgfx::Color::getColorFrom24BitRGB(179, 179, 179));
    nextReportUnitText.setLinespacing(0);
    nextReportUnitText.setTypedText(touchgfx::TypedText(T_SINGLEUSEID42));
    nextReportModeContainer.add(nextReportUnitText);

    nextReportModeText.setXY(0, 0);
    nextReportModeText.setColor(touchgfx::Color::getColorFrom24BitRGB(179, 179, 179));
    nextReportModeText.setLinespacing(0);
    nextReportModeText.setTypedText(touchgfx::TypedText(T_SINGLEUSEID44));
    nextReportModeContainer.add(nextReportModeText);

    nextReportValueText.setPosition(76, 0, 50, 18);
    nextReportValueText.setColor(touchgfx::Color::getColorFrom24BitRGB(179, 179, 179));
    nextReportValueText.setLinespacing(0);
    Unicode::snprintf(nextReportValueTextBuffer, NEXTREPORTVALUETEXT_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID29).getText());
    nextReportValueText.setWildcard(nextReportValueTextBuffer);
    nextReportValueText.setTypedText(touchgfx::TypedText(T_SINGLEUSEID28));
    nextReportModeContainer.add(nextReportValueText);
    reportModeContainer.add(nextReportModeContainer);

    driveModeContainer.setPosition(288, 369, 222, 19);

    prevDriveModeText.setPosition(0, 19, 222, 19);
    prevDriveModeText.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 255, 0));
    prevDriveModeText.setLinespacing(0);
    Unicode::snprintf(prevDriveModeTextBuffer, PREVDRIVEMODETEXT_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID31).getText());
    prevDriveModeText.setWildcard(prevDriveModeTextBuffer);
    prevDriveModeText.setTypedText(touchgfx::TypedText(T_SINGLEUSEID30));
    driveModeContainer.add(prevDriveModeText);

    nextDriveModeText.setPosition(0, -19, 222, 19);
    nextDriveModeText.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 255, 0));
    nextDriveModeText.setLinespacing(0);
    Unicode::snprintf(nextDriveModeTextBuffer, NEXTDRIVEMODETEXT_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID33).getText());
    nextDriveModeText.setWildcard(nextDriveModeTextBuffer);
    nextDriveModeText.setTypedText(touchgfx::TypedText(T_SINGLEUSEID32));
    driveModeContainer.add(nextDriveModeText);

    tripModeContainer.setPosition(269, 93, 79, 20);

    prevTripModeText.setPosition(0, 20, 79, 20);
    prevTripModeText.setColor(touchgfx::Color::getColorFrom24BitRGB(128, 128, 128));
    prevTripModeText.setLinespacing(0);
    Unicode::snprintf(prevTripModeTextBuffer, PREVTRIPMODETEXT_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID37).getText());
    prevTripModeText.setWildcard(prevTripModeTextBuffer);
    prevTripModeText.setTypedText(touchgfx::TypedText(T_SINGLEUSEID36));
    tripModeContainer.add(prevTripModeText);

    nextTripModeText.setPosition(0, -20, 79, 20);
    nextTripModeText.setColor(touchgfx::Color::getColorFrom24BitRGB(128, 128, 128));
    nextTripModeText.setLinespacing(0);
    Unicode::snprintf(nextTripModeTextBuffer, NEXTTRIPMODETEXT_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID35).getText());
    nextTripModeText.setWildcard(nextTripModeTextBuffer);
    nextTripModeText.setTypedText(touchgfx::TypedText(T_SINGLEUSEID34));
    tripModeContainer.add(nextTripModeText);

    tripValue.setPosition(374, 102, 119, 20);
    tripValue.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    tripValue.setLinespacing(0);
    Unicode::snprintf(tripValueBuffer, TRIPVALUE_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID11).getText());
    tripValue.setWildcard(tripValueBuffer);
    tripValue.setTypedText(touchgfx::TypedText(T_SINGLEUSEID3));

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

    fpsValue.setPosition(5, 5, 95, 18);
    fpsValue.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    fpsValue.setLinespacing(0);
    Unicode::snprintf(fpsValueBuffer, FPSVALUE_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID48).getText());
    fpsValue.setWildcard(fpsValueBuffer);
    fpsValue.setTypedText(touchgfx::TypedText(T_SINGLEUSEID47));

    discurProgress.setXY(558, 57);
    discurProgress.setProgressIndicatorPosition(0, 0, 137, 366);
    discurProgress.setRange(0, 100);
    discurProgress.setDirection(touchgfx::AbstractDirectionProgress::UP);
    discurProgress.setBitmap(BITMAP_PROGRESSRIGHT_ID);
    discurProgress.setValue(100);
    discurProgress.setAnchorAtZero(true);

    speedProgress.setXY(105, 57);
    speedProgress.setProgressIndicatorPosition(0, 0, 137, 366);
    speedProgress.setRange(0, 100);
    speedProgress.setDirection(touchgfx::AbstractDirectionProgress::UP);
    speedProgress.setBitmap(BITMAP_PROGRESSLEFT_ID);
    speedProgress.setValue(100);
    speedProgress.setAnchorAtZero(true);

    add(__background);
    add(background);
    add(batteryLow);
    add(brakeAlert);
    add(temperatureWarning);
    add(errorMessage);
    add(fingerScan);
    add(keylessKey);
    add(beamActivated);
    add(mainGo);
    add(mainReverse);
    add(phoneMirroring);
    add(iconContainer);
    add(frameContainer);
    add(seinLeftContainer);
    add(seinRightContainer);
    add(reportModeContainer);
    add(driveModeContainer);
    add(tripModeContainer);
    add(tripValue);
    add(signalValue);
    add(batteryValue);
    add(fpsValue);
    add(discurProgress);
    add(speedProgress);
}

void dashboardScreenViewBase::setupScreen()
{

}
