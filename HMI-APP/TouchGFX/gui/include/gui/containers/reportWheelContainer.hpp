#ifndef REPORTWHEELCONTAINER_HPP
#define REPORTWHEELCONTAINER_HPP

#include <gui_generated/containers/reportWheelContainerBase.hpp>

typedef struct {
	touchgfx::Unicode::UnicodeChar mode[SW_M_REPORT_MAX+1][6];
	touchgfx::Unicode::UnicodeChar unit[SW_M_REPORT_MAX+1][11];
} report_t;

class reportWheelContainer : public reportWheelContainerBase
{
public:
    reportWheelContainer();
    virtual ~reportWheelContainer() {}

    virtual void initialize();
	void updateText(uint8_t index);
protected:
};

#endif // REPORTWHEELCONTAINER_HPP
