#include <gui/dashboardscreen_screen/dashboardScreenView.hpp>
#include <touchgfx/Color.hpp>
#include "BitmapDatabase.hpp"

touchgfx::Container *modeContainer[SW_M_MAX+1];
uint8_t modeSelected = SW_M_DRIVE;
uint8_t modeVisible = 1;

uint8_t iconImageSwiper = 0;
uint8_t tripModeSwiper = 0;
uint8_t driveModeSwiper = 0;
uint8_t reportModeSwiper = 0;
touchgfx::TextAreaWithOneWildcard *pReportValueText;
touchgfx::Unicode::UnicodeChar *pReportValueTextBuffer;

position_t pos;
icon_t prev, next;

drive_t M_DRIVE;
trip_t M_TRIP;


dashboardScreenView::dashboardScreenView() : 
	ticker(0), 
	iconAssets {
		BITMAP_MAINREVERSE_ID,
		BITMAP_MAINGO_ID,
        BITMAP_BRAKESYSTEMALERT_ID,
        BITMAP_SMARTPHONEMIRRORINGSTATUS_ID,
        BITMAP_HIGHBEAMACTIVATED_ID,
        BITMAP_ELECTRONICERRORMESSAGE_ID,
        BITMAP_COOLANTTEMPERATUREWARNING_ID,
        BITMAP_FINGERSCANLOGINSTATUS_ID,
        BITMAP_KEYLESSIGNITIONKEYDETECTION_ID,
		BITMAP_BATTERYDRAINOUT_ID,
	}
{
	pos.prev.x = 0 - prevIconContainer.getWidth() - 200;
	pos.prev.y = iconContainer.getHeight() / 5;
	pos.current.x = (iconContainer.getWidth() - prevIconContainer.getWidth()) / 2;
	pos.current.y = (iconContainer.getHeight() - prevIconContainer.getHeight()) / 2;
	pos.next.x = iconContainer.getWidth() - prevIconContainer.getWidth() + 200;
	pos.next.y = iconContainer.getHeight() / 5;
	
	modeContainer[SW_M_TRIP] = &tripModeContainer;
	modeContainer[SW_M_DRIVE] = &driveModeContainer;
	modeContainer[SW_M_REPORT] = &reportModeContainer;	
		
	M_DRIVE.color[0] = Color::getColorFrom24BitRGB(255, 255, 0);
	M_DRIVE.color[1] = Color::getColorFrom24BitRGB(0, 255, 0);
	M_DRIVE.color[2] = Color::getColorFrom24BitRGB(255, 0, 0);
	M_DRIVE.color[3] = Color::getColorFrom24BitRGB(0, 255, 255);
	touchgfx::Unicode::strncpy(M_DRIVE.mode[0], "ECONOMIC", NEXTDRIVEMODETEXT_SIZE);
	touchgfx::Unicode::strncpy(M_DRIVE.mode[1], "STANDARD", NEXTDRIVEMODETEXT_SIZE);
	touchgfx::Unicode::strncpy(M_DRIVE.mode[2], "SPORT", NEXTDRIVEMODETEXT_SIZE);
	touchgfx::Unicode::strncpy(M_DRIVE.mode[3], "PERFORMANCE", NEXTDRIVEMODETEXT_SIZE);
	
	touchgfx::Unicode::strncpy(M_TRIP.mode[0], "ODO", NEXTTRIPMODETEXT_SIZE);
	touchgfx::Unicode::strncpy(M_TRIP.mode[1], "TRIP A", NEXTTRIPMODETEXT_SIZE);
	touchgfx::Unicode::strncpy(M_TRIP.mode[2], "TRIP B", NEXTTRIPMODETEXT_SIZE);
	
}

void dashboardScreenView::setupScreen()
{
    dashboardScreenViewBase::setupScreen();
}

void dashboardScreenView::tearDownScreen()
{
    dashboardScreenViewBase::tearDownScreen();
}

void dashboardScreenView::handleTickEvent()
{	
	uint8_t curIndicator = presenter->getCurrentIndicator();
	
	if(next.container != NULL) {
		if (!next.container->isRunning()){
			ticker++;
			
			if (curIndicator == INDICATOR_LOWBAT ||
				curIndicator == INDICATOR_WARNING
			) {
				if (ticker % 15 == 0) {
					next.container->setVisible(!next.container->isVisible());
					next.container->invalidate();
				}
			}
			
			if (curIndicator == INDICATOR_FINGER ||
				curIndicator == INDICATOR_MIRRORING ||
				curIndicator == INDICATOR_KEYLESS
			) {
				if (ticker == 40) {
					next.container->setVisible(false);
					next.container->invalidate();
				}
				if (ticker == 60) {
					next.container->setVisible(true);
					next.container->invalidate();
				}
			}				
		} else {
			ticker = 0;
			
			if (!next.container->isVisible()) {
				next.container->setVisible(true);
			}
		}
	}
}
	
void dashboardScreenView::writeModeSelector(uint8_t mode)
{
	for (uint8_t i=0; i<=SW_M_MAX; i++) {
		if (i == mode) {
			modeSelected = mode;
		} else {
			modeContainer[i]->setVisible(true);
			modeContainer[i]->invalidate();
		}
	}
}
void dashboardScreenView::writeModeVisible(uint8_t state)
{
	modeContainer[modeSelected]->setVisible(state);
	modeContainer[modeSelected]->invalidate();
}

void dashboardScreenView::writeSein(uint8_t leftSide, uint8_t state)
{
    MoveAnimator< Image > *sein;
	
	sein = leftSide ? &seinLeft : &seinRight;
	
	if (!sein->isVisible() && state){
		sein->setVisible(true);
		sein->startMoveAnimation(0, 0, 20, EasingEquations::linearEaseOut, EasingEquations::linearEaseOut);
		sein->invalidate();
	} 
	
	if (sein->isVisible() && !state) {
		sein->setVisible(false);
		sein->setXY(80 * (leftSide ? 1 : -1), 0);
		sein->invalidate();
	}
}

void dashboardScreenView::writeSpeed(uint8_t percent)
{
	speedProgress.setValue(percent);
	speedProgress.invalidate();
}

void dashboardScreenView::writeEngineRotation(uint8_t percent)
{
	engineProgress.setValue(percent);
	engineProgress.invalidate();
}

void dashboardScreenView::writeBattery(uint8_t percent)
{
	Unicode::snprintf(batteryValueBuffer, BATTERYVALUE_SIZE, "%3d", percent);
	batteryValue.invalidate();
}

void dashboardScreenView::writeSignal(uint8_t percent)
{
	Unicode::snprintf(signalValueBuffer, SIGNALVALUE_SIZE, "%3d", percent);
	signalValue.invalidate();
}

void dashboardScreenView::writeIndicator(uint8_t index)
{			
	prev.container = iconImageSwiper ? &prevIconContainer : &nextIconContainer;
	prev.image = iconImageSwiper ? &prevIconImage : &nextIconImage;
	next.container = iconImageSwiper ? &nextIconContainer : &prevIconContainer;
	next.image = iconImageSwiper ? &nextIconImage : &prevIconImage;
	
	next.image->setBitmap(Bitmap(iconAssets[index]));
	next.image->setXY(
		(next.container->getWidth() - next.image->getWidth()) / 2,
		(next.container->getHeight() - next.image->getHeight()) / 2
	);
	
	next.container->setXY(pos.next.x, pos.next.y);
	next.container->startMoveAnimation(
		pos.current.x, pos.current.y, 20, 
		EasingEquations::linearEaseOut, EasingEquations::linearEaseOut
	);
	next.container->invalidate();
		
    prev.container->startMoveAnimation(
		pos.prev.x, pos.prev.y, 20, 
		EasingEquations::linearEaseOut, EasingEquations::linearEaseOut
	);
	prev.container->invalidate();
	
	iconImageSwiper = !iconImageSwiper;
}

void dashboardScreenView::writeDriveMode(uint8_t index)
{
	MoveAnimator< touchgfx::TextAreaWithOneWildcard > *prevText = driveModeSwiper ? &prevDriveModeText : &nextDriveModeText;
	MoveAnimator< touchgfx::TextAreaWithOneWildcard > *nextText = driveModeSwiper ? &nextDriveModeText : &prevDriveModeText;
	Unicode::UnicodeChar *nextBuffer = driveModeSwiper ? nextDriveModeTextBuffer : prevDriveModeTextBuffer;
		
	touchgfx::Unicode::snprintf(nextBuffer, NEXTDRIVEMODETEXT_SIZE, "%s", M_DRIVE.mode[index]);
	nextText->setColor(M_DRIVE.color[index]);
	
	nextText->setXY(0, 0 - driveModeContainer.getHeight());
	nextText->startMoveAnimation(
		0, 0, 20, 
		EasingEquations::linearEaseOut, EasingEquations::linearEaseOut
	);
	nextText->invalidate();
		
	prevText->startMoveAnimation(
		0, driveModeContainer.getHeight(), 20, 
		EasingEquations::linearEaseOut, EasingEquations::linearEaseOut
	);
	prevText->invalidate();
	
	driveModeSwiper = !driveModeSwiper;	
}

void dashboardScreenView::writeTripMode(uint8_t index)
{
	MoveAnimator< touchgfx::TextAreaWithOneWildcard > *prevText = tripModeSwiper ? &prevTripModeText : &nextTripModeText;
	MoveAnimator< touchgfx::TextAreaWithOneWildcard > *nextText = tripModeSwiper ? &nextTripModeText : &prevTripModeText;
	Unicode::UnicodeChar *nextBuffer = tripModeSwiper ? nextTripModeTextBuffer : prevTripModeTextBuffer;
		
	touchgfx::Unicode::snprintf(nextBuffer, NEXTTRIPMODETEXT_SIZE, "%s", M_TRIP.mode[index]);
	
	nextText->setXY(0, 0 - tripModeContainer.getHeight());
	nextText->startMoveAnimation(
		0, 0, 20, 
		EasingEquations::linearEaseOut, EasingEquations::linearEaseOut
	);
	nextText->invalidate();
		
	prevText->startMoveAnimation(
		0, tripModeContainer.getHeight(), 20, 
		EasingEquations::linearEaseOut, EasingEquations::linearEaseOut
	);
	prevText->invalidate();
	
	tripModeSwiper = !tripModeSwiper;	
}

void dashboardScreenView::writeTripValue(uint32_t value)
{
	Unicode::snprintf(tripValueBuffer, TRIPVALUE_SIZE, "%06d", value);
	tripValue.invalidate();
}

void dashboardScreenView::writeReportMode(uint8_t index)
{
	MoveAnimator< touchgfx::Container > *prevContainer = reportModeSwiper ? &prevReportModeContainer : &nextReportModeContainer;
	MoveAnimator< touchgfx::Container > *nextContainer = reportModeSwiper ? &nextReportModeContainer : &prevReportModeContainer;
	pReportValueText = reportModeSwiper ? &nextReportValueText : &prevReportValueText;
	pReportValueTextBuffer = reportModeSwiper ? nextReportValueTextBuffer : prevReportValueTextBuffer;
	
	nextContainer->setXY(0, 0 - reportModeContainer.getHeight());
	nextContainer->startMoveAnimation(
		0, 0, 20, 
		EasingEquations::linearEaseOut, EasingEquations::linearEaseOut
	);
	nextContainer->invalidate();
		
	prevContainer->startMoveAnimation(
		0, reportModeContainer.getHeight(), 20, 
		EasingEquations::linearEaseOut, EasingEquations::linearEaseOut
	);
	prevContainer->invalidate();
	
	reportModeSwiper = !reportModeSwiper;
}

void dashboardScreenView::writeReportValue(uint16_t value)
{
	if (pReportValueTextBuffer != NULL) {
		Unicode::snprintf(pReportValueTextBuffer, NEXTREPORTVALUETEXT_SIZE, "%03d", value);
		pReportValueText->invalidate();
	}
}