/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef DRIVEWHEELCONTAINERBASE_HPP
#define DRIVEWHEELCONTAINERBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>

class driveWheelContainerBase : public touchgfx::Container
{
public:
    driveWheelContainerBase();
    virtual ~driveWheelContainerBase() {}
    virtual void initialize();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::TextAreaWithOneWildcard driveMode;

    /*
     * Wildcard Buffers
     */
    static const uint16_t DRIVEMODE_SIZE = 12;
    touchgfx::Unicode::UnicodeChar driveModeBuffer[DRIVEMODE_SIZE];

private:

};

#endif // DRIVEWHEELCONTAINERBASE_HPP