#ifndef WIFI_LIST_ITEM_H
#define WIFI_LIST_ITEM_H

#include "TFT_eSPI.h"

#include "../../../input/TouchButton.h"
#include "../text/TextWrapper.h"
#include "WiFiStrenghtItem.h"

#define BUTTON_BG 0x52AA

class WiFiListItem: public TouchButton
{
    TFT_eSPI* tft;

    String to_print;
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
    );

    void 
    draw(bool forceDraw);

    void
    set_save(bool);

    int8_t 
    get_strenght();

    bool 
    is_saved();

    String 
    get_ssid();

    void on_touch(){
        return;
    }
};

#endif