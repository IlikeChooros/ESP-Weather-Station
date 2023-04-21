#line 1 "c:\\Users\\pawel\\arduino\\ESP-Weather-Station\\src\\output\\items\\wifi\\WiFiStrenghtItem.h"
#ifndef WIFI_STRENGHT_ITEM_H
#define WIFI_STRENGHT_ITEM_H

#include "../../icons/Icons.h"

class WiFiStrenghtItem
{
    TFT_eSPI *tft;

    uint16_t x;
    uint16_t y;
    uint8_t size;
    uint16_t background_color;

    int8_t strenght;

    Icon* 
    matchIcon();

    public:
    WiFiStrenghtItem(
        TFT_eSPI *tft, 
        uint16_t x, 
        uint16_t y, 
        uint8_t size, 
        uint16_t background_color
    ): tft(tft), x(x), y(y), size(size), 
    background_color(background_color) {}
    /**
     * @brief Based on the strenght of connected WiFi, the colour will change
     * 
     * @param strenght 
     */
    void 
    draw(int8_t strenght);
};

#endif