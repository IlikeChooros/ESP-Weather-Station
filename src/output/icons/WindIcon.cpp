#include "WindIcon.h"

Icon* WindIcon::iconMatcher()
{
    switch(this->_icon)
    {
        case WEAK_WIND:
            return new WeakWind(_tft, x, y, size, bg_c);
        case WIND:
            return new Wind(_tft, x, y, size, bg_c);
        default:
            return new StrongWind(_tft, x, y, size, bg_c);
    }
}

void WindIcon::setWeather(Weather* weather) 
{
    uint8_t int_icon;

    if(weather->_wind_speed < 9)
    {
        int_icon = WEAK_WIND;
    }
    else if (weather->_wind_speed < 20)
    {
        int_icon = WIND;
    }
    else
    {
        int_icon = STRONG_WIND;
    }
    this->_redraw = this->_icon != int_icon;
    this->_icon = int_icon;
}

void WindIcon::draw(bool forceDraw)
{
    if (!forceDraw && !this->_redraw)
    {
        return;
    }

    Icon* icon = iconMatcher();
    icon->draw();
    delete icon;
}
