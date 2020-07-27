#include <gui/main_screen/mainView.hpp>

mainView::mainView() :
        tickCounter(0)
{
}

void mainView::setupScreen()
{
    mainViewBase::setupScreen();
}

void mainView::tearDownScreen()
{
    mainViewBase::tearDownScreen();
}

void mainView::handleTickEvent()
{
    tickCounter++;
}
