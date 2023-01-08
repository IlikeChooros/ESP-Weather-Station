#ifndef WIFI_LIST_SCREEN_H
#define WIFI_LIST_SCREEN_H

#include "TFT_eSPI.h"
#include "SPI.h"
#include "Arduino.h"
#include <WiFi.h>

#include "../items/WiFiListItem.h"

#define HEIGHT 30
#define WIDTH 280
#define OFFSET 5

class WiFiListScreen
{
    bool scroll;
    WiFiListItem** wifis;
    TouchButton** buttons;
    uint8_t number_of_networks;
    TFT_eSPI* tft;
    uint16_t bg_c;
    public:
    WiFiListScreen(TFT_eSPI* tft, uint16_t bg_c);
    TouchButton** scan(void(*)(void));
    void draw();
    bool get_scroll();
    uint8_t get_number_of_networks();
    void clear_buttons();
};

#endif