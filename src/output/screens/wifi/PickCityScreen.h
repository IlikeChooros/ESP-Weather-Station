#pragma once

#include "../../items/geoloc/GeoLocItem.h"

class
PickCityScreen
{
    TFT_eSPI* tft;
    uint16_t bg_c;
public:
    PickCityScreen(
        TFT_eSPI* tft,
        uint16_t bg_c
    );


};