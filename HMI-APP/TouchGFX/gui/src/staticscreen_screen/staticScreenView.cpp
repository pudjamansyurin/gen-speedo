#include <gui/staticscreen_screen/staticScreenView.hpp>

staticScreenView::staticScreenView() : ticker(0), colored(true)
{

}

void staticScreenView::setupScreen()
{
    staticScreenViewBase::setupScreen();
}

void staticScreenView::tearDownScreen()
{
    staticScreenViewBase::tearDownScreen();
}

void staticScreenView::handleTickEvent() {
    ticker++;

    if ((ticker / 60) > 20) {
    	ticker = 0;
    	colored = !colored;

    	imageColor.setVisible(colored);
    	imageBlack.setVisible(!colored);
    	imageColor.invalidate();
    	imageBlack.invalidate();
    }
}
