#ifndef ICON_DRAWER_H
#define ICON_DRAWER_H

#include <Arduino.h>
#include <TFT_eSPI.h> 
#include <SPI.h>

#define SUNNY 0xF4E3
#define CLOUDY 0x9CF3

class Icon
{
    public:
    explicit Icon(TFT_eSPI *_tft, uint16_t x, uint16_t y, uint8_t size, uint16_t background_color);
    virtual void draw() = 0;

    protected:
    TFT_eSPI *_tft;
    uint16_t x;
    uint16_t y;
    uint8_t size;
    uint16_t background_color;
};

class Sunny: public Icon
{
    public:
    Sunny(TFT_eSPI *_tft, uint16_t x, uint16_t y, uint8_t size, uint16_t background_color):Icon(_tft,x,y,size,background_color){}
    void draw();
};

class Cloudy: public Icon
{
    public:
    Cloudy(TFT_eSPI *_tft, uint16_t x, uint16_t y, uint8_t size, uint16_t background_color):Icon(_tft,x,y,size,background_color){}
    void draw();
};


#endif