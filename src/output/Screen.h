#ifndef SCREEN_H
#define SCREEN_H

#include <TFT_eSPI.h> 
#include <SPI.h>
#include <Arduino.h>

class Screen
{
    public:
    Screen(TFT_eSPI* tft, uint16_t bg_c);
    virtual void draw();

    protected:
    TFT_eSPI* _tft;
    uint16_t bg_c;
};


#endif