#line 1 "c:\\Users\\pawel\\arduino\\ESP-Weather-Station\\src\\output\\icons\\WindIcon.h"
#pragma once

#include "Icons.h"
#include "../items/WeatherItem.h"

#include <TFT_eSPI.h> 
#include <SPI.h>

#define WEAK_WIND 0
#define WIND 1
#define STRONG_WIND 2

class WindIcon: public WeatherItem
{
    uint8_t _icon;
    bool _redraw;

    Icon* iconMatcher();
    public:
    WindIcon(
        TFT_eSPI *tft, 
        uint16_t x, 
        uint16_t y, 
        uint8_t size, 
        uint16_t background_color
    ): WeatherItem(tft,x,y,background_color)
    {this->size = size;}

    void 
    setWeather(Weather* weather);

    void 
    draw(bool forceDraw);
};
