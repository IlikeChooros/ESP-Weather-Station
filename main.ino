#include "calibrate/calibrate_data.h"
#include "data_structures/Point.h"
#include "output/Coordinate_system.h"

TFT_eSPI tft = TFT_eSPI();

uint16_t touch_x,
         touch_y;

bool touch_pressed = false;

Coordinate_system s(&tft);

void setup()
{
    Serial.begin(921600);

    tft.init();
    tft.setRotation(1);
    tft.setTouch(calData);

    tft.fillScreen(TFT_BLACK);
}


void loop()
{
    touch_pressed = tft.getTouch(&touch_x, &touch_y);

    if (touch_pressed)
    {
        tft.fillCircle(touch_x, touch_y,3, TFT_GOLD);
    }
}