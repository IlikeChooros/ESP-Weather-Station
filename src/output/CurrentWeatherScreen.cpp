#include "CurrentWeatherScreen.h"


CurrentWeatherScreen::CurrentWeatherScreen(TFT_eSPI * tft)
{
    this->_tft = tft;
}

void CurrentWeatherScreen::draw(Weather* weather, uint16_t bg_c)
{
    Icon* icon = iconMatcher(weather, _tft, 10,10, 150, bg_c);
    icon->draw();

    // Fonts: 1,4,6,7,8

    _tft->setCursor(150,20);
    //_tft->setTextColor(TFT_WHITE);
    _tft->setTextFont(4);
    _tft->setTextSize(2);

    _tft->println(String(weather->_feels_like) + " C");

    _tft->setTextSize(1);
    _tft->setCursor(150, 70);
    _tft->println(String(weather->_temp)+" C");


    _tft->println("");
    // dt conversion
    configTime(3600, 3600, NTP_SERVER);
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        _tft->print("ERROR");
    }
    else{
        _tft->println(&timeinfo, "%H:%M %d-%m-%Y");
    }


}