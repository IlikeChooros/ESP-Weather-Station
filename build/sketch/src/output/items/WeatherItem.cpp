#line 1 "c:\\Users\\pawel\\arduino\\ESP-Weather-Station\\src\\output\\items\\WeatherItem.cpp"
#include "WeatherItem.h"

WeatherItem::WeatherItem(TFT_eSPI *tft, uint16_t x, uint16_t y, uint16_t background_color)
{
    this->x = x;
    this->y = y;
    this->_tft = tft;
    this->bg_c = background_color;
}

