#ifndef CURRENT_WEATHER_SCREEN_H
#define CURRENT_WEATHER_SCREEN_H

#include "WeatherItem.h"
#include "icons/WeatherIcon.h"
#include "icons/WindIcon.h"
#include "icons/Icons.h"
#include "../weather_client/Weather.h"
#include "../data_structures/Hsv_to_rgb.h"

#define NTP_SERVER "pool.ntp.org"
#define TEMP_RANGE 70
#define DEGREE char(96)
#define NUMBER_OF_WEATHER_ITEMS 2

class CurrentWeatherScreen
{
    uint16_t* text_colors;
    TFT_eSPI * _tft;

    WeatherItem** weather_items;

    uint16_t _bg_c;

    int16_t convert_to_idx(int16_t temp);
    public:
    CurrentWeatherScreen(TFT_eSPI * tft, uint16_t bg_c);
    void draw(Weather* weather);
};


#endif