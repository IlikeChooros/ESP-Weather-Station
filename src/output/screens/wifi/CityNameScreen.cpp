#include "CityNameScreen.h"

bool 
CityNameScreen::
draw_get(String city_name)
{
    tft->fillRect(40, 40, 240, 160, TFT_BLACK);
    tft->drawRect(40, 40, 240, 160, TFT_WHITE);

    tft->setTextColor(TFT_DARKGREY);
    tft->setTextSize(2);
    tft->drawCentreString("Getting "+city_name, 160, 60, 2);
    tft->drawCentreString("coordinates...", 160, 100, 2);

    if(!wclient->_init_(city_name))
    {
        tft->setTextColor(TFT_RED);
        tft->drawCentreString("Failed, try again.", 160, 130, 2);
        delay(1000);
        tft->fillScreen(bg_c);
        draw();
        return false;
    }
    return true;
}