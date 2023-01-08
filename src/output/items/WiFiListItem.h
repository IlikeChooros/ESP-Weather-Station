#ifndef WIFI_LIST_ITEM_H
#define WIFI_LIST_ITEM_H

#include "Arduino.h"
#include "TFT_eSPI.h"
#include "SPI.h"

#include "../../input/TouchButton.h"

#define BUTTON_BG 0x52AA

class WiFiListItem: public TouchButton
{
    TFT_eSPI* tft;

    String ssid;
    int8_t strenght;

    uint16_t bg_c;

    public:
    WiFiListItem(TFT_eSPI* tft, int16_t x, int16_t y, int16_t width, int16_t height, String ssid, int8_t strenght, uint16_t bg_c): TouchButton(x,y,width,height)
    {
        this->tft = tft;
        this->ssid = ssid;
        this->bg_c = bg_c;
        this->strenght = strenght;
    }
    void draw();
    int16_t get_int();
    String get_str()
    {
        return "";
    }
};

#endif