#ifndef BUTTON_ITEM_H
#define BUTTON_ITEM_H

#include "../../input/TouchButton.h"

#include "TFT_eSPI.h"
#include "SPI.h"

#define BUTTON_BG 0x52AA
#define BUTTON_SQ TFT_WHITE

class KeypadButton
{
    TouchButton* button;
    TFT_eSPI* tft;

    int16_t x;
    int16_t y;
    int16_t width;
    int16_t height;

    String name;
    public:
    KeypadButton(TFT_eSPI* tft, int16_t x, int16_t y, int16_t width, int16_t height, String name);
    void set_button(void(*)(void));
    void draw();
    String get_name();
};


#endif