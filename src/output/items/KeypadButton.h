#ifndef BUTTON_ITEM_H
#define BUTTON_ITEM_H

#include "../../input/TouchButton.h"

#include "TFT_eSPI.h"
#include "SPI.h"

#define BUTTON_BG 0x52AA
#define BUTTON_SQ TFT_WHITE

class KeypadButton: public TouchButton
{
    TFT_eSPI* tft;

    String name;

    bool wrap;

    public:
    KeypadButton(TFT_eSPI* tft, int16_t x, int16_t y, int16_t width, int16_t height, String name): TouchButton(x,y,width,height)
    {
        this->tft = tft;
        this->name = name;
        this->wrap = false;
    }
    void draw();
    void on_touch();
    void set_wrap();
    String get_str();
    int16_t get_int(){
        return 0;
    }
};


#endif