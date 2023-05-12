#ifndef TIME_ITEM_H
#define TIME_ITEM_H

#include "WeatherItem.h"

class TimeItem: public WeatherItem
{
    bool redraw;
    bool hourly;

    String prev_date;
    String font;
    uint64_t unix;
    uint16_t color;

    int16_t width;
    int16_t height;

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
        String font,
        uint64_t unix, 
        bool hourly
    );

    void 
    draw(bool forceDraw);

    void
    setWeather(Weather* weather);
};


#endif