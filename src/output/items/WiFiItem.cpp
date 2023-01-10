#include "WiFiItem.h"

WiFiItem::WiFiItem(TFT_eSPI *tft, uint16_t x, uint16_t y, uint8_t size, uint16_t background_color)
{
    this->tft = tft;
    this->x = x;
    this->y = y;
    this->size = size;
    this->background_color = background_color;

    this->idx = STRONG_WIFI;
    this->prev_idx = STRONG_WIFI;
}

void WiFiItem::draw(bool forceDraw)
{
    Icon* icon = matchIcon();
    if (!forceDraw && prev_idx == idx)
    {
        delete icon;
        return;
    }

    tft->fillRect(x,y,1.2f*size,1.2f*size, background_color);
    icon->draw();
    delete icon;
}

Icon* WiFiItem::matchIcon()
{
    int8_t strenght = WiFi.RSSI();
    prev_idx = idx;
    

    if (WiFi.status() != WL_CONNECTED)
    {
        idx = LOST_WIFI;
        return new WiFiIconLost(tft, x, y, size, background_color);
    }

    // strenght (-45 to 0)
    if (strenght > -45)
    {
        idx = STRONG_WIFI;
        return new WiFiIconStrong(tft, x, y, size, background_color);
    }
    // strenght (-75 to -45)
    else if (strenght > -75)
    {
        idx = MEDIUM_WIFI;
        return new WiFiIconMedium(tft, x, y, size, background_color);
    }

    // strenght (-75 to -128)
    else
    {
        idx = WEAK_WIFI;
        return new WiFiIconWeak(tft, x, y, size, background_color);
    }
}