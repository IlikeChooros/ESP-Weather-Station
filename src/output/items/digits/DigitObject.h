#ifndef DIGIT_OBJ_H
#define DIGIT_OBJ_H

#include "TFT_eSPI.h"
#include "SPI.h"
#include "Arduino.h"

class DigitObject
{
    int8_t currentDigit;
    int8_t prevDigit;

    TFT_eSPI* tft;
    int16_t x;
    int16_t y;
    uint8_t size;
    uint8_t font;
    int16_t bg_c;

    public:
    DigitObject(
        TFT_eSPI* tft, 
        int16_t x, 
        int16_t y, 
        uint8_t size, 
        uint8_t font, 
        int16_t bg_c
    );
    void 
    draw(int8_t digit, bool forceDraw);
    
    void 
    set_digit(int8_t digit);

    void 
    set_x_y(int16_t x, int16_t y);
};

#endif