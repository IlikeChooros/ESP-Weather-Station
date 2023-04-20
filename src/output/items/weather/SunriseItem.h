#pragma once

#include "../../icons/Icons.h"
#include "../WeatherItem.h"
#include "../../../data_structures/get_day.h"

class SunriseItem: public WeatherItem
{
    uint64_t prev_sunrise;
    bool redraw;
public:
    SunriseItem(
        TFT_eSPI *tft, 
        uint16_t x, 
        uint16_t y, 
        uint8_t size, 
        uint16_t background_color
    );
    
    void
    draw(bool);

    void
    setWeather(Weather*);
};


