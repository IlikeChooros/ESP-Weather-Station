#include "WiFiStrenghtItem.h"


WiFiStrenghtItem::WiFiStrenghtItem(TFT_eSPI *tft, uint16_t x, uint16_t y, uint8_t size, uint16_t background_color)
{
    this->tft = tft;
    this->x = x;
    this->y = y;
    this->size = size;
    this->background_color = background_color;
}

void WiFiStrenghtItem::draw(int8_t strenght)
{
    this->strenght = strenght;

    Icon* icon = matchIcon();
    icon->draw();
    delete icon;
}

Icon* WiFiStrenghtItem::matchIcon()
{
    // strenght (-30 to 0)
    if (strenght > -45)
    {
        return new WiFiStrenghtStrong(tft,x,y,size,background_color);
    }
    // strenght (-60 to -30)
    else if (strenght > -75)
    {
        return new WiFiStrenghtMedium(tft,x,y,size,background_color);
    }
    else 
    {
        return new WiFiStrenghtWeak(tft,x,y,size,background_color);
    }
}