#ifndef ICON_DRAWER_H
#define ICON_DRAWER_H

#include <Arduino.h>
#include <TFT_eSPI.h> 
#include <SPI.h>

#define SUNNY 0xF4E3
#define CLOUDY 0x94B2
#define LIGHT_DARK_CLOUDS 0x7BCF
#define MIDDLE_DARK_CLOUDS 0x632C
#define DARK_CLOUDS 0x4208
#define WATER 0x033B

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

class Sun: public Icon
{
    public:
    Sun(TFT_eSPI *_tft, uint16_t x, uint16_t y, uint8_t size, uint16_t background_color):Icon(_tft,x,y,size,background_color){}
    void draw();
};

class Clouds: public Icon
{
    public:
    Clouds(TFT_eSPI *_tft, uint16_t x, uint16_t y, uint8_t size, uint16_t background_color):Icon(_tft,x,y,size,background_color){}
    void draw();
};

class ManyClouds:public Icon
{
    void draw_cloud(uint16_t x, uint16_t y, uint16_t size, uint16_t color);
    public:
    ManyClouds(TFT_eSPI *_tft, uint16_t x, uint16_t y, uint8_t size, uint16_t background_color):Icon(_tft,x,y,size,background_color){}
    void draw();
};

class Storm: public Icon
{
    public:
    Storm(TFT_eSPI *_tft, uint16_t x, uint16_t y, uint8_t size, uint16_t background_color):Icon(_tft,x,y,size,background_color){}
    void draw();
};

class Rain: public Icon
{
    void draw_droplet(uint16_t x, uint16_t y, uint16_t size);
    public:
    Rain(TFT_eSPI *_tft, uint16_t x, uint16_t y, uint8_t size, uint16_t background_color):Icon(_tft,x,y,size,background_color){}
    void draw();
};

#endif