#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

typedef struct {
    struct {
        char mode[2][6];
        char unit[2][11];
    } report;
    struct {
        char mode[4][9];
    } drive;
} collection_t;

class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleTickEvent();
protected:
    uint32_t ticker;
    uint32_t _tripValue;
    uint32_t _engineValue;
    uint8_t _batteryValue;
    uint8_t _signalValue;
    uint8_t _speedValue;
};

#endif // SCREEN1VIEW_HPP
