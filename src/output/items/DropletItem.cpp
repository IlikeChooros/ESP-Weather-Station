#include "DropletItem.h"

DropletItem::
DropletItem(
    TFT_eSPI *_tft, 
    uint16_t x, 
    uint16_t y, 
    uint8_t size, 
    uint16_t background_color
): WeatherItem(_tft,x,y,background_color),
size(size), pop(0){}

void 
DropletItem::
draw(bool forceDraw){
    if (!forceDraw && !redraw){
        return;
    }

    Icon* icon = matchIcon();
    icon->draw();
    delete icon;
}

void 
DropletItem::
setWeather(Weather* weather){
    redraw = pop != uint16_t(100 * weather->_pop);
    pop = uint16_t(100 * weather->_pop);

    idx_icon = (uint8_t)(floorf(pop / 25));
}

Icon* 
DropletItem::matchIcon(){
    switch (idx_icon)
    {
        case NO_RAIN:
            return new Droplet_0(_tft, x,y, size, bg_c);
        case UNLIKELY_RAIN:
            return new Droplet_30(_tft,x,y,size,bg_c);
        case PROBABLY_RAIN:
            return new Droplet_50(_tft,x,y,size,bg_c);
        case LIKELY_RAIN:
            return new Droplet_70(_tft,x,y,size,bg_c);
        default:
            return new Droplet_100(_tft,x,y,size,bg_c);
    }
}