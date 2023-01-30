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
    // strenght (-30 to 0)
    if (strenght > -45)
    {
        return new WiFiIconStrong(tft,x,y,size,background_color);
    }
    // strenght (-60 to -30)
    else if (strenght > -75)
    {
        return new WiFiIconMedium(tft,x,y,size,background_color);
    }
    else 
    {
        return new WiFiIconWeak(tft,x,y,size,background_color);
    }
}