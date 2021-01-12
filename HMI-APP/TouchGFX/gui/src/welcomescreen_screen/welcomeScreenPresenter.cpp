#include <gui/welcomescreen_screen/welcomeScreenView.hpp>
#include <gui/welcomescreen_screen/welcomeScreenPresenter.hpp>

#if !defined(SIMULATOR) || defined(LCD_TESTING)
extern "C"
{
#include "Libs/_utils.h"
}
#endif

welcomeScreenPresenter::welcomeScreenPresenter(welcomeScreenView& v)
: view(v)
{

}

void welcomeScreenPresenter::activate()
{
#if !defined(SIMULATOR) || defined(LCD_TESTING)
  _DelayMS(1000);
  _LcdPower(1);
#endif
}

void welcomeScreenPresenter::deactivate()
{

}
