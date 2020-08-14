#include <gui/dashboardscreen_screen/dashboardScreenView.hpp>
#include "BitmapDatabase.hpp"

position_t pos;
icon_t prev, next;
uint8_t iconImage = 0;
uint8_t modeVisible = 1;
touchgfx::Box *modeBox;

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
}

void dashboardScreenView::setupScreen()
{
    dashboardScreenViewBase::setupScreen();
}

void dashboardScreenView::tearDownScreen()
{
    dashboardScreenViewBase::tearDownScreen();
}

void dashboardScreenView::driveWheelUpdateItem(driveWheelContainer& item, int16_t itemIndex)
{
    item.updateText(itemIndex);
}

void dashboardScreenView::tripWheelUpdateItem(tripWheelContainer& item, int16_t itemIndex) 
{
    item.updateText(itemIndex);
}

void dashboardScreenView::reportWheelUpdateItem(reportWheelContainer& item, int16_t itemIndex)
{
    item.updateText(itemIndex);
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
	switch (mode) {
		case SW_M_DRIVE  : 
			modeBox = &driveWheelBox; 
			tripWheelBox.setVisible(false);
			tripWheelBox.invalidate();
			reportWheelBox.setVisible(false);
			reportWheelBox.invalidate();
			break;
		case SW_M_TRIP 	 : 
			modeBox = &tripWheelBox; 
			driveWheelBox.setVisible(false);
			driveWheelBox.invalidate();
			reportWheelBox.setVisible(false);
			reportWheelBox.invalidate();
			break;
		case SW_M_REPORT : 
			modeBox = &reportWheelBox; 
			tripWheelBox.setVisible(false);
			tripWheelBox.invalidate();
			driveWheelBox.setVisible(false);
			driveWheelBox.invalidate();
			break;		
		default: 
			break;
	}
}
void dashboardScreenView::writeModeVisible(uint8_t state)
{
	if (modeBox != NULL) {
		modeBox->setVisible(state);
		modeBox->invalidate();
	}
}

void dashboardScreenView::writeSein(uint8_t leftSide, uint8_t state)
{
    touchgfx::MoveAnimator< touchgfx::Image > *sein;
	
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
	prev.container = iconImage ? &prevIconContainer : &nextIconContainer;
	prev.image = iconImage ? &prevIconImage : &nextIconImage;
	next.container = iconImage ? &nextIconContainer : &prevIconContainer;
	next.image = iconImage ? &nextIconImage : &prevIconImage;
	
	next.image->setBitmap(Bitmap(iconAssets[index]));
	next.image->setXY(
		(next.container->getWidth() - next.image->getWidth()) / 2,
		(next.container->getHeight() - next.image->getHeight()) / 2
	);
	next.image->invalidate();
	
	next.container->setXY(pos.next.x, pos.next.y);
	next.container->startMoveAnimation(
		pos.current.x, pos.current.y, 20, 
		touchgfx::EasingEquations::linearEaseOut, touchgfx::EasingEquations::linearEaseOut
	);
	next.container->invalidate();
		
    prev.container->startMoveAnimation(
		pos.prev.x, pos.prev.y, 20, 
		touchgfx::EasingEquations::linearEaseOut, touchgfx::EasingEquations::linearEaseOut
	);
	prev.container->invalidate();
	
	iconImage = !iconImage;
}

void dashboardScreenView::writeDriveMode(uint8_t index)
{
	driveWheel.animateToItem(index, 0);
	driveWheel.invalidate();
}

void dashboardScreenView::writeTripMode(uint8_t index)
{
	tripWheel.animateToItem(index, 0);
	tripWheel.invalidate();
}

void dashboardScreenView::writeTripValue(uint32_t value)
{
	Unicode::snprintf(tripValueBuffer, TRIPVALUE_SIZE, "%06d", value);
	tripValue.invalidate();
}

void dashboardScreenView::writeReportMode(uint8_t index)
{
	reportValue.setX(index ? 362 : 423);
	reportValue.invalidate();
	reportWheel.animateToItem(index, 0);
	reportWheel.invalidate();
}

void dashboardScreenView::writeReportValue(uint16_t value)
{
	Unicode::snprintf(reportValueBuffer, REPORTVALUE_SIZE, "%03d", value);
	reportValue.invalidate();
}