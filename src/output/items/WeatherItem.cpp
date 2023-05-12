#include "WeatherItem.h"

WeatherItem::WeatherItem(TFT_eSPI *tft, uint16_t x, uint16_t y, uint16_t background_color){
    this->x = x;
    this->y = y;
    this->_tft = tft;
    this->bg_c = background_color;
}

