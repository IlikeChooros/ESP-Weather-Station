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

    int16_t convert_to_idx(int16_t temp);
    public:
    CurrentWeatherScreen(TFT_eSPI * tft);
    void draw_main_screen(Weather* weather, uint16_t background_color);
    void draw_desc(Weather* weather, uint16_t background_color);
};


#endif