#ifndef TEXT_ITEM_H
#define TEXT_ITEM_H

#include <Arduino.h>
#include <TFT_eSPI.h> 
#include <SPI.h>
#include "../weather_client/Weather.h"

class TextItem
{
    public:
    explicit TextItem(TFT_eSPI *_tft, uint16_t x, uint16_t y, uint8_t font, uint8_t text_size, String text, uint16_t background_color);
    virtual void draw() = 0;
    virtual void setWeather(Weather* weather) = 0;

    protected:
    TFT_eSPI *_tft;
    uint16_t x;
    uint16_t y;
    uint8_t font;
    uint8_t text_size;
    String text;
    uint16_t bg_c;
};


#endif