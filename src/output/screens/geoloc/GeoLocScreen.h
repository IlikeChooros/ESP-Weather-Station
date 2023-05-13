#pragma once

#include "../../items/geoloc/GeoLocItem.h"
#include "../../items/keypad/CustomButton.h"
#include "../../../input/TouchScreen.h"

class GeoLocScreen{
private:
    TFT_eSPI *tft;
    TFT_eSprite img;
    TouchScreen* ts;
    ScreenPointItem* sci;
    CustomButton* exit_button;
    CustomButton* enter_button;
    GeoLocItem* geoitem;

    uint16_t img_x;
public:
    GeoLocScreen(
        TFT_eSPI* tft,
        WeatherClient* wclient,
        TouchScreen* ts
    );

    ~GeoLocScreen();
    
    void
    draw(bool forceDraw);

    void
    set_location(const String& location);

    void
    check(void);

    bool
    is_picked(void);
};