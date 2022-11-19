#ifndef CURRENT_WEATHER_SCREEN_H
#define CURRENT_WEATHER_SCREEN_H

#include "MainScreen.h"
#include "WeatherItem.h"
#include "TextItem.h"
#include "icons/WeatherIcon.h"
#include "icons/WindIcon.h"
#include "icons/Icons.h"
#include "../weather_client/Weather.h"
#include "../data_structures/Hsv_to_rgb.h"

#define NTP_SERVER "pool.ntp.org"
#define DEGREE '`'
#define NUMBER_OF_WEATHER_ITEMS 6

class CurrentWeatherScreen: public MainScreen
{
    WeatherItem** weather_items;

    public:
    CurrentWeatherScreen(TFT_eSPI * tft, uint16_t bg_c): MainScreen(tft,bg_c){
        set_text_colors();

        weather_items = new WeatherItem*[NUMBER_OF_WEATHER_ITEMS] {
            new WeatherIcon(this->_tft,185,30, 125, bg_c),
            new WindIcon(this->_tft, 5, 105, 20, bg_c),
            new TextTemp(this->_tft, 30, 30, 4, 2, TFT_WHITE, "%d `C" , bg_c),
            new TextFeelsLike(this->_tft, 35, 80, 2, 1, TFT_WHITE,"Feels like: %d `C", bg_c),
            new TextWind(this->_tft, 30, 105, 4, 1, 0x77F2, "%d km/h", bg_c),
            new TextPressure(this->_tft, 30, 130, 4, 1, 0xB41F, "%d hPa", bg_c)
        };
    }
    void draw(Weather* weather, bool forceDraw);
    void draw(Forecast* forecast, bool forceDraw)
    {
        return;
    }
};


#endif