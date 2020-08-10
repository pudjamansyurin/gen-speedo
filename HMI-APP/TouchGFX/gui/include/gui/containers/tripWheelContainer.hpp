#ifndef TRIPWHEELCONTAINER_HPP
#define TRIPWHEELCONTAINER_HPP

#include <gui_generated/containers/tripWheelContainerBase.hpp>

typedef struct {
	touchgfx::Unicode::UnicodeChar mode[SW_M_TRIP_MAX+1][7];
} trip_t;

class tripWheelContainer : public tripWheelContainerBase
{
public:
    tripWheelContainer();
    virtual ~tripWheelContainer() {}

    virtual void initialize();
	void updateText(uint8_t index);
protected:
};

#endif // TRIPWHEELCONTAINER_HPP
