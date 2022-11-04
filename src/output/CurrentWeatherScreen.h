#ifndef CURRENT_WEATHER_SCREEN_H
#define CURRENT_WEATHER_SCREEN_H

#include "iconMatcher.h"
#include "icons/IconDrawer.h"
#include "weather_client/Weather.h"
#include "../data_structures/Hsv_to_rgb.h"

#define NTP_SERVER "pool.ntp.org"
#define TEMP_RANGE 70

class CurrentWeatherScreen
{
    uint16_t* text_colors;
    TFT_eSPI * _tft;
    public:
    CurrentWeatherScreen(TFT_eSPI * tft);
    void draw(Weather* weather, uint16_t background_color);
};


#endif