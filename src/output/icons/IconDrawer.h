#ifndef ICON_DRAWER_H
#define ICON_DRAWER_H

#include "drawings.h"

#define SUNNY 0xF4E3
#define MOON 0xE64D
#define CLOUDY 0xB5B6
#define LIGHT_DARK_CLOUDS 0xA534
#define MIDDLE_DARK_CLOUDS 0x8C71
#define ALMOST_DARK_CLOUDS 0x7BEF
#define DARK_CLOUDS 0x632C
#define WATER 0x051D
#define SNOW_FLAKE 0x8E7F
#define MIST 0xDEFB

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
    void draw_droplet(uint16_t ax, uint16_t ay,uint16_t bx, uint16_t by, uint16_t size);
    public:
    Rain(TFT_eSPI *_tft, uint16_t x, uint16_t y, uint8_t size, uint16_t background_color):Icon(_tft,x,y,size,background_color){}
    void draw();
};

class BigRain: public Icon
{
    public:
    BigRain(TFT_eSPI *_tft, uint16_t x, uint16_t y, uint8_t size, uint16_t background_color):Icon(_tft,x,y,size,background_color){}
    void draw();
};

class Snow: public Icon
{
    public:
    Snow(TFT_eSPI *_tft, uint16_t x, uint16_t y, uint8_t size, uint16_t background_color):Icon(_tft,x,y,size,background_color){}
    void draw();
};

class MistDay: public Icon
{
    public:
    MistDay(TFT_eSPI *_tft, uint16_t x, uint16_t y, uint8_t size, uint16_t background_color):Icon(_tft,x,y,size,background_color){}
    void draw();
};

class MistNight: public Icon
{
    public:
    MistNight(TFT_eSPI *_tft, uint16_t x, uint16_t y, uint8_t size, uint16_t background_color):Icon(_tft,x,y,size,background_color){}
    void draw();
};


#endif