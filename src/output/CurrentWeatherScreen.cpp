#include "CurrentWeatherScreen.h"

void CurrentWeatherScreen::draw(Weather* weather, bool forceDraw)
{
    configTime(3600, 0, NTP_SERVER);
    
    for (uint8_t i = 0; i<NUMBER_OF_WEATHER_ITEMS;i++)
    {
        weather_items[i]
        ->setWeather(weather);
        weather_items[i]
        ->draw(forceDraw);
    }

    // Fonts: 1,2,4,6,7,8
    refresh();
}

void CurrentWeatherScreen::refresh()
{
    _tft->fillRect(0,0,320,96,bg_c);
    _tft->setTextFont(4);
    _tft->setTextSize(1);
    _tft->setTextColor(TFT_WHITE);

    _tft->setCursor(40,10);
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        _tft->print("ERROR");
    }
    else{
        _tft->println(&timeinfo, "%A -%e %b. %Y");
        _tft->setTextFont(6);
        _tft->setCursor(95,45);
        _tft->print(&timeinfo, "%H:%M");
    }
}

