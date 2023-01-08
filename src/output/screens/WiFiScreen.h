#ifndef WIFI_SCREEN_H
#define WIFI_SCREEN_H

#include "Arduino.h"
#include "TFT_eSPI.h"
#include "SPI.h"

class WiFiScreen
{
    public:
    explicit WiFiScreen(TFT_eSPI* tft, int16_t bg_c);
    virtual void draw() = 0;
    virtual void check(int16_t* pos) = 0;
    virtual void scan(void(*)(void)) = 0;
    virtual void clear_buttons() = 0;

    protected:
    int16_t bg_c;
    TFT_eSPI* tft;
};

#endif