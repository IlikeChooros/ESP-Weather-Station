#pragma once

#include "../../../weather_client/WeatherClient.h"
#include "../../../custom_font/fonts.h"
#include "../text/TextWrapper.h"
#include "TFT_eSPI.h"

class GeoDisplayItem
{
    TFT_eSPI* tft;
    City_info info;
    String to_print;

    uint16_t x;
    uint16_t y;
    uint16_t w;
    uint16_t h;
    uint16_t bg_c;

    bool state;
public:
    GeoDisplayItem(
        TFT_eSPI* tft,
        City_info& city_info,
        uint16_t x,
        uint16_t y,
        uint16_t bg_c
    );

    void
    draw();

    void
    clear();
};