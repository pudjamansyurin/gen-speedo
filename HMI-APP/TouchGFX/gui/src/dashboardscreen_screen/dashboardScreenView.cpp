#include <gui/dashboardscreen_screen/dashboardScreenView.hpp>

dashboardScreenView::dashboardScreenView()
{
	
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

void dashboardScreenView::indicatorWheelUpdateItem(indicatorWheelContainer& item, int16_t itemIndex)
{
    item.updateImage(itemIndex);
}

void dashboardScreenView::tripWheelUpdateItem(tripWheelContainer& item, int16_t itemIndex) 
{
    item.updateText(itemIndex);
}

void dashboardScreenView::reportWheelUpdateItem(reportWheelContainer& item, int16_t itemIndex)
{
    item.updateText(itemIndex);
}

void dashboardScreenView::setIndicator(uint8_t index)
{
	indicatorWheel.animateToItem(index, 0);
	indicatorWheel.invalidate();
}

void dashboardScreenView::setSein(uint8_t leftSide, uint8_t state)
{
    touchgfx::MoveAnimator< touchgfx::Image > *sein;
	
	sein = leftSide ? &seinLeft : &seinRight;
	
	if(!sein->isVisible()){
		sein->setVisible(true);
		sein->startMoveAnimation(0, 0, 20, EasingEquations::linearEaseOut, EasingEquations::linearEaseOut);
		sein->invalidate();
	} else {
		sein->setVisible(false);
		sein->setXY(80 * (leftSide ? 1 : -1), 0);
		sein->invalidate();
	}
}

void dashboardScreenView::setSpeed(uint8_t percent)
{
	speedProgress.setValue(percent);
	speedProgress.invalidate();
}

void dashboardScreenView::setEngineRotation(uint8_t percent)
{
	engineProgress.setValue(percent);
	engineProgress.invalidate();
}

void dashboardScreenView::setBattery(uint8_t percent)
{
	Unicode::snprintf(batteryValueBuffer, BATTERYVALUE_SIZE, "%3d", percent);
	batteryValue.invalidate();
}

void dashboardScreenView::setSignal(uint8_t percent)
{
	Unicode::snprintf(signalValueBuffer, SIGNALVALUE_SIZE, "%3d", percent);
	signalValue.invalidate();
}

void dashboardScreenView::setDriveMode(uint8_t index)
{
	driveWheel.animateToItem(index, 0);
	driveWheel.invalidate();
}

void dashboardScreenView::setTripMode(uint8_t index)
{
	tripWheel.animateToItem(index, 0);
	tripWheel.invalidate();
}

void dashboardScreenView::setTripValue(uint32_t value)
{
	Unicode::snprintf(tripValueBuffer, TRIPVALUE_SIZE, "%06d", value);
	tripValue.invalidate();
}

void dashboardScreenView::setReportMode(uint8_t index)
{
	reportValue.setX(index ? 362 : 423);
	reportValue.invalidate();
	reportWheel.animateToItem(index);
	reportWheel.invalidate();
}

void dashboardScreenView::setReportValue(uint16_t value)
{
	Unicode::snprintf(reportValueBuffer, REPORTVALUE_SIZE, "%03d", value);
	reportValue.invalidate();
}