#include "WiFiStrenghtItem.h"

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
    // strenght (-35 to 0)
    if (strenght > -35){
        return new WiFiIconSuperStrong(tft,x,y,size,background_color);
    }
    // strenght (-55 to -35)
    else if(strenght > - 55){
        return new WiFiIconStrong(tft,x,y,size,background_color);
    }
    // strenght (-75 to -55)
    else if (strenght > -85){
        return new WiFiIconMedium(tft,x,y,size,background_color);
    }
    // strenght (-128 to -55)
    else {
        return new WiFiIconWeak(tft,x,y,size,background_color);
    }
}