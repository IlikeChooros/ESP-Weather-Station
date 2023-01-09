#ifndef INPUT_FIELD_H
#define INPUT_FIELD_H

#include "Arduino.h"
#include "TFT_eSPI.h"
#include "SPI.h"

#define INPUT_FIELD_BG 0x1904

class InputField
{
    TFT_eSPI* tft;
    String input;

    int16_t x;
    int16_t y;
    int16_t width;
    int16_t height;

    public:
    InputField(TFT_eSPI* tft, int16_t x, int16_t y, int16_t width, int16_t height);
    void draw();
    void add_input(String input);
    String get_input();
    void del();
};

#endif