#line 1 "c:\\Users\\pawel\\arduino\\ESP-Weather-Station\\src\\output\\items\\weather\\SunriseItem.cpp"
#include "SunriseItem.h"

SunriseItem::
SunriseItem(
    TFT_eSPI *tft, 
    uint16_t x, 
    uint16_t y, 
    uint8_t size, 
    uint16_t background_color
): WeatherItem(tft, x, y, background_color),
prev_sunrise(0), redraw(false) {
    this->size = size;
}

void
SunriseItem::
draw(bool forceDraw){
    if (!(forceDraw || redraw)){
        return;
    }

    drawSunrise(_tft, x, y, size, bg_c);
    HH_YY_date hours(prev_sunrise);
    String to_print = String(hours.hour) + ":";
    to_print += hours.min < 10 ? "0" + String(hours.min) : String(hours.min);
    _tft->setTextColor(TFT_WHITE);
    _tft->setTextSize(1);
    _tft->drawString(to_print, x + size + 2, y + 0.2f*size, 2);
}

void
SunriseItem::
setWeather(Weather* weather){
    uint64_t sunrise = weather->_sunrise + weather->_timezone;
    redraw = sunrise != prev_sunrise;
    prev_sunrise = sunrise;
}