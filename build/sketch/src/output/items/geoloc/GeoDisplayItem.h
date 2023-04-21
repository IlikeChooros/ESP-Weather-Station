#line 1 "c:\\Users\\pawel\\arduino\\ESP-Weather-Station\\src\\output\\items\\geoloc\\GeoDisplayItem.h"
#pragma once

#include "../../../weather_client/WeatherClient.h"
#include "TFT_eSPI.h"
#include "SPI.h"

class GeoDisplayItem
{
    TFT_eSPI* tft;
    City_info info;

    uint16_t x;
    uint16_t y;
    uint16_t w;
    uint16_t h;

public:
    GeoDisplayItem(
        TFT_eSPI* tft,
        City_info& city_info,
        uint16_t x,
        uint16_t y,
        uint16_t w,
        uint16_t h
    );

    void
    draw();
};