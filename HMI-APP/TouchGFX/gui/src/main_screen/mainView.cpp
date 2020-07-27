#include <gui/main_screen/mainView.hpp>

mainView::mainView() :
        tickCounter(0)
{
}

void mainView::setupScreen()
{
    mainViewBase::setupScreen();
    digitalHours = digitalClock.getCurrentHour();
    digitalMinutes = digitalClock.getCurrentMinute();
    digitalSeconds = digitalClock.getCurrentSecond();

    analogHours = analogClock.getCurrentHour();
    analogMinutes = analogClock.getCurrentMinute();
    analogSeconds = analogClock.getCurrentSecond();
}

void mainView::tearDownScreen()
{
    mainViewBase::tearDownScreen();
}

void mainView::handleTickEvent()
{
    tickCounter++;

    if (tickCounter % 60 == 0)
            {
        if (++digitalSeconds >= 60)
                {
            digitalSeconds = 0;
            if (++digitalMinutes >= 60)
                    {
                digitalMinutes = 0;
                if (++digitalHours >= 24)
                        {
                    digitalHours = 0;
                }
            }
        }

        if (++analogSeconds >= 60)
                {
            analogSeconds = 0;
            if (++analogMinutes >= 60)
                    {
                analogMinutes = 0;
                if (++analogHours >= 24)
                        {
                    analogHours = 0;
                }
            }
        }

        // Update the clocks
        digitalClock.setTime24Hour(digitalHours, digitalMinutes, digitalSeconds);
        analogClock.setTime24Hour(analogHours, analogMinutes, analogSeconds);
    }
}
