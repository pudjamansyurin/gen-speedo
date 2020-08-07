/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/screen2_screen/Screen2ViewBase.hpp>
#include <touchgfx/Color.hpp>
#include "BitmapDatabase.hpp"

Screen2ViewBase::Screen2ViewBase()
{

    box1.setPosition(0, 0, 800, 480);
    box1.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));

    mainLogo.setXY(300, 140);
    mainLogo.setBitmap(touchgfx::Bitmap(BITMAP_ICON_ID));
    mainLogo.setWidth(200);
    mainLogo.setHeight(230);
    mainLogo.setBitmapPosition(0.000f, 0.000f);
    mainLogo.setScale(1.000f);
    mainLogo.setCameraDistance(1000.000f);
    mainLogo.setOrigo(100.000f, 115.000f, 1000.000f);
    mainLogo.setCamera(100.000f, 115.000f);
    mainLogo.updateAngles(0.000f, 0.000f, 0.000f);
    mainLogo.setRenderingAlgorithm(touchgfx::TextureMapper::BILINEAR_INTERPOLATION);

    add(box1);
    add(mainLogo);
}

void Screen2ViewBase::setupScreen()
{

}

void Screen2ViewBase::switchScreen()
{
    //Interaction1
    //When switchScreen is called change screen to Screen1
    //Go to Screen1 with screen transition towards South
    application().gotoScreen1ScreenSlideTransitionSouth();
}
