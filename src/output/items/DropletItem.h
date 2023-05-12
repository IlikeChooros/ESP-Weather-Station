#ifndef DROPLET_ITEM_H
#define DROPLET_ITEM_H

#include "WeatherItem.h"
#include "../icons/Icons.h"

#define NO_RAIN 0
#define UNLIKELY_RAIN 1
#define PROBABLY_RAIN 2
#define LIKELY_RAIN 3
#define RAIN 4

class DropletItem: public WeatherItem
{
    bool redraw;
    uint8_t size;
    uint8_t pop;
    uint8_t idx_icon;

    Icon* 
    matchIcon();
    
public:
    DropletItem(
        TFT_eSPI *_tft, 
        uint16_t x, 
        uint16_t y, 
        uint8_t size, 
        uint16_t background_color
    );

    void 
    draw(bool forceDraw);

    void 
    setWeather(Weather* weather);
};


#endif