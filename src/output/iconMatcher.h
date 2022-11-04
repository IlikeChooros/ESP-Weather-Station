#ifndef ICON_MATCHER_H
#define ICON_MATCHER_H

#include "icons/IconDrawer.h"
#include "weather_client/WeatherClient.h"

#include <TFT_eSPI.h> 
#include <SPI.h>


inline Icon* iconMatcher(Weather* weather, TFT_eSPI *_tft, uint16_t x, uint16_t y, uint8_t size, uint16_t background_color)
{
    String s = weather->_icon;


    switch (s[1])
    {
        case '1':
            if (s[2] == 'd')
            {
                return new Sun(_tft, x, y, size, background_color); // 01d
            }
            return new Moon(_tft, x, y, size, background_color); // 01n
        case '2':
            if (s[2]=='d')
            {
                return new FewCloudsDay(_tft, x, y, size, background_color); // 02d
            }
            return new FewCloudsNight(_tft, x, y, size, background_color); // 02n
        case '3':
            if (s[0]=='0')
            {
                if(s[2]=='d')
                {
                    return new CloudsDay(_tft, x, y, size, background_color); // 03d
                }
                return new CloudsNight(_tft, x, y, size, background_color); // 03n
            }
            return new Snow(_tft, x, y, size, background_color); // 13 d/n
        case '4':
            return new ManyClouds(_tft, x, y, size, background_color); // 4d/n
        case '9':
            return new Rain(_tft, x, y, size, background_color); // 9 d/n
        case '0':
            if (s[0]=='1')
            {
                return new BigRain(_tft, x, y, size, background_color);
            } 
            if (s[2] == 'd')
            {
                return new MistDay(_tft, x, y, size, background_color);
            }
            return new MistNight(_tft, x, y, size, background_color);
    }

    // if (s == "02d")
    // {
    //     return new FewCloudsDay(_tft, x, y, size, background_color);
    // }

    // if (s == "02n")
    // {
    //     return new FewCloudsNight(_tft, x, y, size, background_color);
    // }

    // if (s == "03d")
    // {
    //     return new CloudsDay(_tft, x, y, size, background_color);
    // }

    // if (s == "03n")
    // {
    //     return new CloudsNight(_tft, x, y, size, background_color);
    // }

    // if ( s == "04n"|| s == "04d" )
    // {
    //     return new ManyClouds(_tft, x, y, size, background_color);
    // }

    // if (s == "09d" || s == "09n")
    // {
    //     return new Rain(_tft, x, y, size, background_color);
    // }

    // if (s == "10d" || s == "10n")
    // {
    //     return new BigRain(_tft, x, y, size, background_color);
    // }

    // if (s == "11d" || s == "11n")
    // {
    //     return new Storm(_tft, x, y, size, background_color);
    // }

    // if (s == "13d" || s == "13n")
    // {
    //     return new Snow(_tft, x, y, size, background_color);
    // }

    // if (s == "50d")
    // {
    //     return new MistDay(_tft, x, y, size, background_color);
    // }

    // else{
    //     return new MistNight(_tft, x, y, size, background_color);
    // }
}

#endif