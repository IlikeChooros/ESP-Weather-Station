#ifndef WIFI_LIST_ITEM_H
#define WIFI_LIST_ITEM_H

#include "Arduino.h"
#include "TFT_eSPI.h"
#include "SPI.h"

#include "../../input/TouchButton.h"

#define BUTTON_BG 0x52AA

class WiFiListItem
{
    TFT_eSPI* tft;

    TouchButton* button;

    String ssid;
    int8_t strenght;

    int16_t x;
    int16_t y;
    int16_t width;
    int16_t height;

    uint16_t bg_c;

    public:
    WiFiListItem(TFT_eSPI* tft, int16_t x, int16_t y, int16_t width, int16_t height, String ssid, uint16_t bg_c);
    void draw();
    void set_strenght(int8_t strenght);
    TouchButton* get_button();
    int8_t get_strenght();
};

#endif