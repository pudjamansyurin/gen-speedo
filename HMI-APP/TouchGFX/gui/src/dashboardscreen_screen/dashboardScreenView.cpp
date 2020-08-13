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

void dashboardScreenView::indicatorWheelUpdateItem(indicatorWheelContainer& item, int16_t itemIndex)
{
	item.updateImage(itemIndex, presenter->getIndicatorSelected());
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

void dashboardScreenView::writeSein(uint8_t leftSide, uint8_t state)
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
	// touchgfx_printf("animateToItem %d\n", index);
	indicatorWheel.animateToItem(index, 0);
	indicatorWheel.invalidate();
	
    // indicatorImage.clearMoveAnimationEndedAction();
    // indicatorImage.startMoveAnimation(-100, -100, 60, touchgfx::EasingEquations::expoEaseOut, touchgfx::EasingEquations::expoEaseOut);
	// indicatorImage.startMoveAnimation(-100, -100, 60, touchgfx::EasingEquations::expoEaseIn, touchgfx::EasingEquations::expoEaseIn);

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