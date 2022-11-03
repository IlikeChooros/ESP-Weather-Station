#ifndef ICON_DRAWER_H
#define ICON_DRAWER_H

#include <Arduino.h>
#include <TFT_eSPI.h> 
#include <SPI.h>

#include "drawCloud.h"

#define SUNNY 0xF4E3
#define CLOUDY 0xB5B6
#define LIGHT_DARK_CLOUDS 0xA534
#define MIDDLE_DARK_CLOUDS 0x8C71
#define ALMOST_DARK_CLOUDS 0x7BEF
#define DARK_CLOUDS 0x632C
#define WATER 0x051D

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

class Moon: public Icon
{
    public:
    Moon(TFT_eSPI *_tft, uint16_t x, uint16_t y, uint8_t size, uint16_t background_color):Icon(_tft,x,y,size,background_color){}
    void draw();
};

class FewCloudsDay: public Icon
{
    public:
    FewCloudsDay(TFT_eSPI *_tft, uint16_t x, uint16_t y, uint8_t size, uint16_t background_color):Icon(_tft,x,y,size,background_color){}
    void draw();
};

class FewCloudsNight: public Icon
{
    public:
    FewCloudsNight(TFT_eSPI *_tft, uint16_t x, uint16_t y, uint8_t size, uint16_t background_color):Icon(_tft,x,y,size,background_color){}
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

class BigRain: public Icon
{
    void draw_droplet(uint16_t x, uint16_t y, uint16_t size);
    public:
    BigRain(TFT_eSPI *_tft, uint16_t x, uint16_t y, uint8_t size, uint16_t background_color):Icon(_tft,x,y,size,background_color){}
    void draw();
};

#endif