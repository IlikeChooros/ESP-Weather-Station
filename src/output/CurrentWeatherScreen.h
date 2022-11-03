#ifndef CURRENT_WEATHER_SCREEN_H
#define CURRENT_WEATHER_SCREEN_H

#include "iconMatcher.h"
#include "icons/IconDrawer.h"
#include "weather_client/Weather.h"

#define NTP_SERVER "pool.ntp.org"

class CurrentWeatherScreen
{
    TFT_eSPI * _tft;
    public:
    CurrentWeatherScreen(TFT_eSPI * tft);
    void draw(Weather* weather, uint16_t background_color);
};


#endif