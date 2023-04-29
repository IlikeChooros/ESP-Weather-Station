#ifndef TEXT_ITEM_H
#define TEXT_ITEM_H

#include "WeatherItem.h"
#include "../../data_structures/Hsv_to_rgb.h"

class TextItem: public WeatherItem
{   
    String font;
    uint8_t text_size;
    const char* format;

    public:
    TextItem(
        TFT_eSPI *_tft, 
        uint16_t x, 
        uint16_t y, 
        String font,
        uint16_t color,
        const char* format, 
        uint16_t background_color
    ): WeatherItem(_tft,x,y,background_color),
    font(font), text_size(text_size), 
    format(format), color(color), prev_data(0)
    {}

    void 
    draw(bool forceDraw);

    protected:
    int16_t _data;
    int16_t prev_data;
    bool redraw;
    uint16_t color;
};

class TextTemp: public TextItem
{
    public:
    TextTemp(TFT_eSPI *_tft, uint16_t x, uint16_t y, String font, uint16_t color ,const char* format, uint16_t background_color): TextItem(_tft,x,y,font,color,format,background_color){}
    void setWeather(Weather* weather);
};

class TextWind: public TextItem
{
    public:
    TextWind(TFT_eSPI *_tft, uint16_t x, uint16_t y, String font, uint16_t color ,const char* format, uint16_t background_color): TextItem(_tft,x,y,font,color,format,background_color){}
    void setWeather(Weather* weather);
};

class TextPressure: public TextItem
{
    public:
    TextPressure(TFT_eSPI *_tft, uint16_t x, uint16_t y, String font, uint16_t color ,const char* format, uint16_t background_color): TextItem(_tft,x,y,font,color,format,background_color){}
    void setWeather(Weather* weather);
};


class TextFeelsLike: public TextItem
{
    public:
    TextFeelsLike(TFT_eSPI *_tft, uint16_t x, uint16_t y, String font, uint16_t color ,const char* format, uint16_t background_color): TextItem(_tft,x,y,font,color,format,background_color){}
    void setWeather(Weather* weather);
};

class TextPop: public TextItem
{
    public:
    TextPop(TFT_eSPI *_tft, uint16_t x, uint16_t y, String font, uint16_t color ,const char* format, uint16_t background_color): TextItem(_tft,x,y,font,color,format,background_color){}
    void setWeather(Weather* weather);
};

#endif