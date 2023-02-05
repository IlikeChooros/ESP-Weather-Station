#pragma once

#include "../../items/geoloc/GeoLocItem.h"
#include "../../items/keypad/CustomButton.h"
#include "../../../input/TouchScreen.h"

class GeoLocScreen
{
    TFT_eSPI *tft;
    TouchScreen* ts;

    CustomButton** buttons;

    GeoLocItem* geoitem;

    void
    draw_window
    (bool forceDraw);

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
    set_location
    (String location);

    void
    check(void);

    bool
    is_picked(void);
};