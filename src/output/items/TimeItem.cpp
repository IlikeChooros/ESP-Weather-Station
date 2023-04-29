#include "TimeItem.h"


void TimeItem::draw(bool forceDraw){
    if (!(redraw || forceDraw)){
        return;
    }

    String date = get_date_format(hourly);
    this->_tft->setCursor(this->x, this->y);
    this->_tft->setTextColor(this->bg_c);
    this->_tft->loadFont(this->font);
    this->_tft->print(prev_date);

    this->_tft->setTextColor(color);
    this->_tft->setCursor(x,y);
    this->_tft->print(date);
    prev_date = date;
    this->_tft->unloadFont();
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