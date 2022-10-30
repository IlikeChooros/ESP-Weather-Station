#include "src/calibrate/calibrate_data.h"
#include "src/data_structures/Point.h"
#include "src/output/Coordinate_system.h"

TFT_eSPI tft = TFT_eSPI();

Point touch_point;

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
    touch_pressed = tft.getTouch(&touch_point.x, &touch_point.y);

    if (touch_pressed)
    {
        tft.fillCircle(touch_point.x, touch_point.y,3, TFT_GOLD);
    }
}