#line 1 "c:\\Users\\pawel\\arduino\\ESP-Weather-Station\\src\\output\\items\\TimeItem.h"
#ifndef TIME_ITEM_H
#define TIME_ITEM_H

#include "WeatherItem.h"

class TimeItem: public WeatherItem
{
    bool redraw;
    bool hourly;

    String prev_date;
    uint8_t font;
    uint8_t text_size;
    uint64_t unix;
    uint16_t color;

    String 
    get_weekday();

    String 
    get_hour_format();

    String 
    get_date_format(bool hourFormat);
    
    public:
    TimeItem(
        TFT_eSPI *_tft, 
        uint16_t x, 
        uint16_t y, 
        uint16_t background_color, 
        uint16_t color, 
        uint8_t font,
        uint8_t text_size, 
        uint64_t unix, 
        bool hourly
    ): WeatherItem(_tft,x,y,background_color)
    {
        this->font = font;
        this->text_size = text_size;
        this->unix = unix;
        this->color = color;
        this->hourly = hourly;
        prev_date = "";
    }

    void 
    draw(bool forceDraw);

    void
    setWeather(Weather* weather);
};


#endif