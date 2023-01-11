#ifndef WIFI_STRENGHT_ITEM_H
#define WIFI_STRENGHT_ITEM_H

#include "../icons/Icons.h"

class WiFiStrenghtItem
{
    TFT_eSPI *tft;

    uint16_t x;
    uint16_t y;
    uint8_t size;
    uint16_t background_color;

    int8_t strenght;

    Icon* matchIcon();
    public:
    WiFiStrenghtItem(TFT_eSPI *tft, uint16_t x, uint16_t y, uint8_t size, uint16_t background_color);
    void draw(int8_t strenght);
};

#endif