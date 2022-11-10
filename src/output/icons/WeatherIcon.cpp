 #include "WeatherIcon.h"

Icon* WeatherIcon::iconMatcher()
{
    switch (_icon)
    {
        case 1:
            if (this->_day)
            {
                return new Sun(_tft, x, y, size, bg_c); // 01d
            }
            return new Moon(_tft, x, y, size, bg_c); // 01n
        case 2:
            if (this->_day)
            {
                return new FewCloudsDay(_tft, x, y, size, bg_c);  // 02d
            }
            return new FewCloudsNight(_tft, x, y, size, bg_c);  // 02n
        case 3:
            if(this->_day)
            {
                return new CloudsDay(_tft, x, y, size, bg_c);  // 03d
            }
            return new CloudsNight(_tft, x, y, size, bg_c);  // 03n
        case 4:
            return new ManyClouds(_tft, x, y, size, bg_c);  // 4d/n
        case 9:
            return new Rain(_tft, x, y, size, bg_c);  // 9 d/n
        case 10:
                return new BigRain(_tft, x, y, size, bg_c); 
        case 13:
            return new Snow(_tft, x, y, size, bg_c);  // 13 d/n
        default:
            if(this->_day)
            {
                return new MistDay(_tft, x, y, size, bg_c); 
            }
            return new MistNight(_tft, x, y, size, bg_c); 
    }
}

void WeatherIcon::setWeather(Weather* weather) 
{
    bool day = weather->_icon[2] == 'd';
    uint8_t int_icon = weather->_icon.toInt();

    this->_redraw = this->_icon != int_icon || this->_day != day;
    this->_day = day;
    this->_icon = int_icon;
}

void WeatherIcon::draw(bool forceDraw)
{
    if (!forceDraw && !this->_redraw)
    {
        return;
    }

    Icon* icon = iconMatcher();
    icon->draw();
    delete icon;
}