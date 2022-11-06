#include "Weather.h"


Weather* Weather::main(String main){
    this->_main = main;

    return this;
}

Weather* Weather::icon(String icon)
{
    this->_icon = icon;

    return this;
}

Weather* Weather::temp(double temp)
{
    this->_temp = temp;

    return this;
}

Weather* Weather::feels_like(double feels_like)
{
    this->_feels_like = feels_like;

    return this;
}

Weather* Weather::wind_speed(double wind_speed)
{
    this->_wind_speed = wind_speed;

    return this;
}

Weather* Weather::humidity(uint8_t humidity)
{
    this->_humidity = humidity;

    return this;
}

Weather* Weather::pressure(uint16_t pressure)
{
    this->_pressure = pressure;

    return this;
}

Weather* Weather::sunrise(uint32_t sunrise)
{
    this->_sunrise = sunrise;

    return this;
}

Weather* Weather::sunset(uint32_t sunset)
{
    this->_sunset = sunset;

    return this;
}
