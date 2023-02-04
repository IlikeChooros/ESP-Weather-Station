#ifndef WIFI_LIST_ITEM_H
#define WIFI_LIST_ITEM_H

#include "Arduino.h"
#include "TFT_eSPI.h"
#include "SPI.h"

#include "../../../input/TouchButton.h"

#include "WiFiStrenghtItem.h"

#define BUTTON_BG 0x52AA

class WiFiListItem: public TouchButton
{
    TFT_eSPI* tft;

    String ssid;
    int8_t strenght;

    uint16_t bg_c;

    bool password_saved;

    public:
    WiFiListItem(
        TFT_eSPI* tft, 
        int16_t x, 
        int16_t y, 
        int16_t width, 
        int16_t height, 
        String ssid, 
        bool password_saved,
        int8_t strenght, 
        uint16_t bg_c
    ): TouchButton(x,y,width,height),
    tft(tft), ssid(ssid), password_saved(password_saved),
    strenght(strenght), bg_c(bg_c)
    {}

    void 
    draw(bool forceDraw);

    int8_t 
    get_strenght();

    bool 
    is_saved();

    String 
    get_ssid();

    void on_touch()
    {
        return;
    }
};

#endif