#include "SunsetItem.h"

SunsetItem::
SunsetItem(
    TFT_eSPI *tft, 
    uint16_t x, 
    uint16_t y, 
    uint8_t size, 
    uint16_t background_color
): WeatherItem(tft,x,y,background_color),
prev_sunset(0), redraw(false) {
    this->size = size;
}

void
SunsetItem::
draw(bool forceDraw){
    if (!(forceDraw || redraw)){
        return;
    }

    drawSunset(_tft, x, y, size, bg_c);
    HH_YY_date hours(prev_sunset);
    String to_print = String(hours.hour) + ":";
    to_print += hours.min < 10 ? "0" + String(hours.min) : String(hours.min);
    _tft->setTextColor(TFT_WHITE);
    _tft->setTextSize(1);
    _tft->drawString(to_print, x + size + 2, y + 0.2f*size, 2);
}

void
SunsetItem::
setWeather(Weather* weather){
    uint64_t sunset = weather->_sunset + weather->_timezone;
    redraw = sunset != prev_sunset;
    prev_sunset = sunset;
}