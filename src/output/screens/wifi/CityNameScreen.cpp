#include "CityNameScreen.h"

bool
CityNameScreen::
load_main(){
    return this->load_main_;
}

bool
CityNameScreen::
change(){
    return this->change_;
}

bool 
CityNameScreen::
draw_get(String city_name, uint8_t idx)
{
    tft->fillRect(40, 40, 240, 160, TFT_BLACK);
    tft->drawRect(40, 40, 240, 160, TFT_WHITE);

    tft->setTextColor(TFT_LIGHTGREY);
    tft->setTextSize(2);
    tft->drawCentreString("Getting "+city_name, 160, 60, 2);
    tft->drawCentreString("coordinates...", 160, 100, 2);

    if(!wclient->_init_(city_name, idx)){
        tft->setTextColor(TFT_RED);
        tft->drawCentreString("Failed, try again.", 160, 130, 2);
        delay(1000);
        tft->fillScreen(bg_c);
        draw(true);
        return false;
    }
    return true;
}