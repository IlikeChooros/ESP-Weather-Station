#ifndef WIFI_SCREEN_H
#define WIFI_SCREEN_H

#include <EEPROM.h>
#include <WiFi.h>
#include "Arduino.h"
#include "TFT_eSPI.h"
#include "SPI.h"

#include "../../../data_structures/Point.h"

#ifndef EEPROM_SIZE
#define EEPROM_SIZE 512
#endif

#define MAX_PASSWORD_LENGHT 31
#define MAX_SSID_LENGHT 26 


class WiFiScreen
{
public:
    explicit 
    WiFiScreen(
        TFT_eSPI* tft, 
        int16_t bg_c
    );

    virtual void 
    draw() = 0;

    virtual void 
    draw(
        String wifi_name
    ) = 0;

    virtual String 
    get_str() = 0;

    virtual void 
    check(
        Point* pos
    ) = 0;

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

    int16_t bg_c;
    TFT_eSPI* tft;
};

#endif