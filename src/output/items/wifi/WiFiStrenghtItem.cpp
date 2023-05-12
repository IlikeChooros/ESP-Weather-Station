#include "WiFiStrenghtItem.h"

WiFiStrenghtItem::
WiFiStrenghtItem(
    TFT_eSPI *tft, 
    uint16_t x, 
    uint16_t y, 
    uint8_t size, 
    uint16_t background_color
): tft(tft), x(x), y(y), size(size), 
background_color(background_color) {}

void 
WiFiStrenghtItem::
draw(int8_t strenght){
    this->strenght = strenght;

    Icon* icon = matchIcon();
    icon->draw();
    delete icon;
}

Icon* 
WiFiStrenghtItem::
matchIcon(){
    // strenght (-25 to 0)
    if (strenght > -25){
        return new WiFiIconSuperStrong(tft,x,y,size,background_color);
    }
    // strenght (-50 to -25)
    else if(strenght > - 50){
        return new WiFiIconStrong(tft,x,y,size,background_color);
    }
    // strenght (-75 to -50)
    else if (strenght > -75){
        return new WiFiIconMedium(tft,x,y,size,background_color);
    }
    // strenght (-128 to -75)
    else {
        return new WiFiIconWeak(tft,x,y,size,background_color);
    }
}