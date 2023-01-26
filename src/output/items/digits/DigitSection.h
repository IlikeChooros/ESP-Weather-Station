#ifndef DIGIT_SECTION_H
#define DIGIT_SECTION_H

#include "DigitObject.h"

#define NUMBER_OF_DIGITS 2
#define LEFT_DIGIT 0
#define RIGHT_DIGIT 1
#define DIGIT_WIDTH 27

class DigitSection
{
    TFT_eSPI* tft;
    int16_t x;
    int16_t y;
    uint8_t size;
    uint8_t font;
    bool colon;
    DigitObject** digitsObj;

public:
    DigitSection(
        TFT_eSPI *tft, 
        int16_t x, 
        int16_t y, 
        uint8_t size, 
        uint8_t font, 
        int16_t bg_c, 
        bool putColonOnTheEnd
    );

    void 
    draw(uint8_t digits, bool forceDraw);

    void 
    set_x(int16_t x);
};


#endif