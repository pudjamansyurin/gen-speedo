#ifndef DRIVEWHEELCONTAINER_HPP
#define DRIVEWHEELCONTAINER_HPP

#include <gui_generated/containers/driveWheelContainerBase.hpp>

typedef struct {
	Unicode::UnicodeChar mode[SW_M_DRIVE_MAX+1][12];
	colortype color[SW_M_DRIVE_MAX+1];
} drive_t;

class driveWheelContainer : public driveWheelContainerBase
{
public:
    driveWheelContainer();
    virtual ~driveWheelContainer() {}

    virtual void initialize();
	void updateText(uint8_t index);
protected:
};

#endif // DRIVEWHEELCONTAINER_HPP
