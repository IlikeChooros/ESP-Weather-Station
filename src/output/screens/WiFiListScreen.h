#ifndef WIFI_LIST_SCREEN_H
#define WIFI_LIST_SCREEN_H

#include <WiFi.h>

#include "../items/WiFiListItem.h"
#include "WiFiScreen.h"

#define HEIGHT 30
#define WIDTH 280
#define OFFSET 5

class WiFiListScreen: public WiFiScreen
{
    bool scroll;
    TouchButton** wifis;
    uint8_t number_of_networks;
    public:
    WiFiListScreen(TFT_eSPI* tft, uint16_t bg_c): WiFiScreen(tft, bg_c){
        WiFi.mode(WIFI_STA);
        WiFi.disconnect();
    }
    void scan(void(*)(void));
    void draw();
    void check(int16_t* pos);
    void clear_buttons();
};

#endif