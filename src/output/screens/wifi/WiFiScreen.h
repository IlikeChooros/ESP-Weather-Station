#ifndef WIFI_SCREEN_H
#define WIFI_SCREEN_H

#include <EEPROM.h>
#include <WiFi.h>
#include "Arduino.h"
#include "TFT_eSPI.h"
#include "SPI.h"

#include "../../../data_structures/Point.h"
#include "../../items/memory/ReadMem.h"
#include "../../../custom_font/fonts.h"

class WiFiScreen
{
public:
    explicit 
    WiFiScreen(
        TFT_eSPI* tft, 
        uint16_t bg_c
    );

    virtual void 
    draw(bool forceDraw) = 0;

    virtual void 
    draw(String wifi_name) = 0;

    virtual String 
    get_str() = 0;

    virtual void 
    check(Point* pos) = 0;

    virtual void 
    scan() = 0;

    virtual void 
    clear_buttons() = 0;

    virtual bool 
    change() = 0;

    virtual bool 
    load_main() = 0;

    virtual void 
    init() = 0;

protected:

    bool 
    draw_connecting_to_wifi(
        String wifi_name, 
        char* ssid, 
        char* pass
    );

    uint16_t bg_c;
    TFT_eSPI* tft;
};

#endif