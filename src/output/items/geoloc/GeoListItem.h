#pragma once

#include "GeoLocItem.h"

namespace
geoloc
{
    class GeoListItem
    {
        TFT_eSPI* tft;
        WeatherClient* wclient;
    public:
        GeoListItem(
            TFT_eSPI* tft,
            WeatherClient* wclient
        );

        void
        set_location(
            String location
        );

        void
        draw();

    };
    
}