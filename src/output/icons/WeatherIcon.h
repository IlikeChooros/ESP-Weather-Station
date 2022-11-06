#ifndef WEATHER_ICON_H
#define WEATHER_ICON_H

#include "Icons.h"
#include "../WeatherItem.h"

#include <TFT_eSPI.h> 
#include <SPI.h>

class WeatherIcon: public WeatherItem
{
    bool _day;
    uint8_t _icon;
    bool _redraw;


    Icon* iconMatcher();
    public:
    WeatherIcon(TFT_eSPI *tft, uint16_t x, uint16_t y, uint8_t size, uint16_t background_color): WeatherItem(tft,x,y,size,background_color){}
    void setWeather(Weather* weather);
    void draw();
};



#endif