#include "CurrentWeatherScreen.h"


CurrentWeatherScreen::CurrentWeatherScreen(TFT_eSPI * tft)
{
    this->_tft = tft;


    // Temp range from 40+ to 30- (C)
    text_colors = new uint16_t [TEMP_RANGE];


    HSV* hsv = new HSV;

    hsv->hue = 0;
    hsv->satrutaion = 83;
    hsv->value = 100;

    uint8_t itr = 250 / TEMP_RANGE;

    for (uint8_t t = TEMP_RANGE-1;t>=0; t--)
    {
        text_colors[t] = HSV_RGB(*hsv);
        hsv->hue += itr;
    }

}

void CurrentWeatherScreen::draw(Weather* weather, uint16_t bg_c)
{
    configTime(0, 3600, NTP_SERVER);
    Icon* icon = iconMatcher(weather, _tft, 10,10, 150, bg_c);
    icon->draw();

    // Fonts: 1,4,6,7,8

    _tft->setCursor(140,20);
    //_tft->setTextColor(TFT_WHITE);
    _tft->setTextFont(4);
    _tft->setTextSize(2);

    uint16_t temp = (int16_t)weather->_feels_like + 30;
    temp = temp > 70 ? 70 : temp;
    temp = temp < 0 ? 0: temp;
    _tft->setTextColor(text_colors[temp]);

    _tft->println(String(weather->_feels_like) + " C");


    temp = (int16_t)weather->_temp + 30;
    temp = temp > 70 ? 70 : temp;
    temp = temp < 0 ? 0: temp;
    _tft->setTextColor(text_colors[temp]);
    _tft->setTextSize(1);
    _tft->setCursor(150, 70);
    _tft->println(String(weather->_temp)+" C");


    _tft->println("");

    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        _tft->print("ERROR");
    }
    else{
        _tft->println(&timeinfo, "%H:%M %d-%m-%Y");
    }


}