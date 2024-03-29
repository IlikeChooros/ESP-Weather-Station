#include "TimeItem.h"

TimeItem::
TimeItem(
    TFT_eSPI *_tft, 
    uint16_t x, 
    uint16_t y, 
    uint16_t background_color, 
    uint16_t color, 
    String font,
    uint64_t unix, 
    bool hourly
): WeatherItem(_tft,x,y,background_color),
font(font), unix(unix), color(color), 
hourly(hourly), prev_date(""), width(1), height(WEATHER_HEIGHT+1) {}

void TimeItem::draw(bool forceDraw){
    if (!(redraw || forceDraw)){
        return;
    }

    String date = get_date_format(hourly);
    // clear previous data
    _tft->fillRect(x, y, width, height, bg_c);

    // print new data
    _tft->loadFont(font);
    _tft->setTextColor(color, bg_c);
    width = _tft->drawCentreString(date, x, y, 2);
    prev_date = date;
    _tft->unloadFont();
}

String TimeItem::get_date_format(bool hourFormat)
{
    if (hourFormat){
        return get_hour_format();
    }
    return get_weekday();
}

void TimeItem::setWeather(Weather* weather){
    redraw = unix != weather->_dt + weather->_timezone;
    this->unix = weather->_dt + weather->_timezone;
}

String TimeItem::get_hour_format(){
    uint32_t time = unix % (24 * 60 * 60);
    uint8_t hour = time / 3600,
            min = (time % 3600) / 60;
            
    String hour_format = String(hour) + ":";
    hour_format += min < 10 ? "0" + String(min) : String(min);

    return hour_format;
}

String TimeItem::get_weekday(){
    String weekdays[7] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
    float days = this->unix/24;
    days /= 3600;
    return weekdays[((uint32_t)days+3)%7];    
}