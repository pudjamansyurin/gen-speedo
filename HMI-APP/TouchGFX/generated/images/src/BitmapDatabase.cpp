// 4.16.1 0x50ad6218
// Generated by imageconverter. Please, do not edit!

#include <BitmapDatabase.hpp>
#include <touchgfx/Bitmap.hpp>

extern const unsigned char image_rev1_1[]; // BITMAP_REV1_1_ID = 0, Size: 800x480 pixels
extern const unsigned char image_rev1_1_extra_data[];
extern const unsigned char image_rev1_2[]; // BITMAP_REV1_2_ID = 1, Size: 800x480 pixels
extern const unsigned char image_rev1_2_extra_data[];

const touchgfx::Bitmap::BitmapData bitmap_database[] =
{
    { image_rev1_1, image_rev1_1_extra_data, 800, 480, 0, 0, 800, (uint8_t)(touchgfx::Bitmap::L8) >> 3, 480, (uint8_t)(touchgfx::Bitmap::L8) & 0x7 },
    { image_rev1_2, image_rev1_2_extra_data, 800, 480, 0, 0, 800, (uint8_t)(touchgfx::Bitmap::L8) >> 3, 480, (uint8_t)(touchgfx::Bitmap::L8) & 0x7 }
};

namespace BitmapDatabase
{
const touchgfx::Bitmap::BitmapData* getInstance()
{
    return bitmap_database;
}

uint16_t getInstanceSize()
{
    return (uint16_t)(sizeof(bitmap_database) / sizeof(touchgfx::Bitmap::BitmapData));
}
}
