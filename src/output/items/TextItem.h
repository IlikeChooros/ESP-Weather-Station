#ifndef TEXT_ITEM_H
#define TEXT_ITEM_H

#include "WeatherItem.h"
#include "../../data_structures/Hsv_to_rgb.h"

class TextItem: public WeatherItem
{   
    public:
    TextItem(
        TFT_eSPI *_tft, 
        uint16_t x, 
        uint16_t y, 
        String font,
        uint16_t color,
        const char* format, 
        uint16_t background_color
    );

    virtual void 
    draw(bool forceDraw);

    protected:
    int16_t _data;
    bool redraw;
    uint16_t color;
    String font;
    const char* format;
    int16_t text_width;
};

class TextTemp: public TextItem
{
    public:
    TextTemp(TFT_eSPI *_tft, uint16_t x, uint16_t y, String font, uint16_t color ,const char* format, uint16_t background_color);
    void setWeather(Weather* weather);
    void draw(bool);
};

class TextFeelsLike: public TextItem
{
    public:
    TextFeelsLike(TFT_eSPI *_tft, uint16_t x, uint16_t y, String font, uint16_t color ,const char* format, uint16_t background_color);
    void setWeather(Weather* weather);
    void draw(bool);
};

class TextWind: public TextItem
{
    public:
    TextWind(TFT_eSPI *_tft, uint16_t x, uint16_t y, String font, uint16_t color ,const char* format, uint16_t background_color);
    void setWeather(Weather* weather);
};

class TextPressure: public TextItem
{
    public:
    TextPressure(TFT_eSPI *_tft, uint16_t x, uint16_t y, String font, uint16_t color ,const char* format, uint16_t background_color);
    void setWeather(Weather* weather);
};

class TextPop: public TextItem
{
    public:
    TextPop(TFT_eSPI *_tft, uint16_t x, uint16_t y, String font, uint16_t color ,const char* format, uint16_t background_color);
    void setWeather(Weather* weather);
};

#endif