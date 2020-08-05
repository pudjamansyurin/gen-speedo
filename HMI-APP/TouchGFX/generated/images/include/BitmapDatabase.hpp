// Generated by imageconverter. Please, do not edit!

#ifndef BITMAPDATABASE_HPP
#define BITMAPDATABASE_HPP

#include <touchgfx/hal/Types.hpp>
#include <touchgfx/lcd/LCD.hpp>
#include <touchgfx/Bitmap.hpp>

const uint16_t BITMAP_BACKGROUNDLEFT_ID = 0;
const uint16_t BITMAP_BACKGROUNDRIGHT_ID = 1;
const uint16_t BITMAP_BATTERYICON_ID = 2;
const uint16_t BITMAP_ENGINEROTATION_ID = 3;
const uint16_t BITMAP_MODECONTAINER_ID = 4;
const uint16_t BITMAP_SIGNALICON_ID = 5;
const uint16_t BITMAP_SPEEDLEVEL_ID = 6;
const uint16_t BITMAP_TRIPCONTAINER_ID = 7;

namespace BitmapDatabase
{
const touchgfx::Bitmap::BitmapData* getInstance();
uint16_t getInstanceSize();
}

#endif
