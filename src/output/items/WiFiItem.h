#ifndef WIFI_ITEM_H
#define WIFI_ITEM_H

#include "../icons/Icons.h"
#include <WiFi.h>

#define STRONG_WIFI 0
#define MEDIUM_WIFI 1
#define WEAK_WIFI 2
#define LOST_WIFI 3

class WiFiItem
{
    TFT_eSPI *tft;
    uint16_t x;
    uint16_t y;
    uint8_t size;
    uint16_t background_color;

    uint8_t prev_idx;
    uint8_t idx;

    Icon* matchIcon();
    public:
    WiFiItem(TFT_eSPI *_tft, uint16_t x, uint16_t y, uint8_t size, uint16_t background_color);
    void draw(bool forceDraw);
};

#endif