#ifndef ICON_MATCHER_H
#define ICON_MATCHER_H

#include "icons/IconDrawer.h"
#include "weather_client/WeatherClient.h"

#include <TFT_eSPI.h> 
#include <SPI.h>


inline Icon* iconMatcher(Weather* weather, TFT_eSPI *_tft, uint16_t x, uint16_t y, uint8_t size, uint16_t background_color)
{
    String s = weather->_icon;

    if (s=="01d")
    {
        return new Sun(_tft, x, y, size, background_color);
    }

    if (s == "01n")
    {
        return new Moon(_tft, x, y, size, background_color);
    }

    if (s == "02d")
    {
        return new FewCloudsDay(_tft, x, y, size, background_color);
    }

    if (s == "02n")
    {
        return new FewCloudsNight(_tft, x, y, size, background_color);
    }

    if (s == "03d" || s == "04d" || s == "03n" || s == "04n")
    {
        return new ManyClouds(_tft, x, y, size, background_color);
    }

    if (s == "09d" || s == "09n")
    {
        return new Rain(_tft, x, y, size, background_color);
    }

    if (s == "10d" || s == "10n")
    {
        return new BigRain(_tft, x, y, size, background_color);
    }

    if (s == "11d" || s == "11n")
    {
        return new Storm(_tft, x, y, size, background_color);
    }

    if (s == "13d" || s == "13n")
    {
        return new Snow(_tft, x, y, size, background_color);
    }

    if (s == "50d")
    {
        return new MistDay(_tft, x, y, size, background_color);
    }

    else{
        return new MistNight(_tft, x, y, size, background_color);
    }
}

#endif