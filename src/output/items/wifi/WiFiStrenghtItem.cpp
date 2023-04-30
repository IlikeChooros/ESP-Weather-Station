#include "WiFiStrenghtItem.h"

void 
WiFiStrenghtItem::
draw(int8_t strenght)
{
    this->strenght = strenght;

    Icon* icon = matchIcon();
    icon->draw();
    delete icon;
}

Icon* 
WiFiStrenghtItem::
matchIcon()
{
    // strenght (-25 to 0)
    if (strenght > -25){
        return new WiFiIconSuperStrong(tft,x,y,size,background_color);
    }
    // strenght (-45 to -25)
    else if(strenght > - 45){
        return new WiFiIconStrong(tft,x,y,size,background_color);
    }
    // strenght (-75 to -45)
    else if (strenght > -75){
        return new WiFiIconMedium(tft,x,y,size,background_color);
    }
    else {
        return new WiFiIconWeak(tft,x,y,size,background_color);
    }
}