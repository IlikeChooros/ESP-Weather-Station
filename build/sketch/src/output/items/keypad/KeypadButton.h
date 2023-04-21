#line 1 "c:\\Users\\pawel\\arduino\\ESP-Weather-Station\\src\\output\\items\\keypad\\KeypadButton.h"
#ifndef BUTTON_ITEM_H
#define BUTTON_ITEM_H

#include "../../../input/TouchButton.h"

#include "TFT_eSPI.h"
#include "SPI.h"

#define BUTTON_BG 0x52AA
#define BUTTON_SQ TFT_WHITE

class KeypadButton: public TouchButton
{
    TFT_eSPI* tft;

    String name;

    uint16_t 
    touch_color;

    uint16_t 
    text_color;

    bool wrap;

    void
    draw_(uint16_t color);

    public:
    KeypadButton(
        TFT_eSPI* tft, 
        int16_t x, 
        int16_t y, 
        int16_t width, 
        int16_t height, 
        String name
    ): TouchButton(x,y,width,height),
    name(name), wrap(false), tft(tft),
    touch_color(0x2104),
    text_color(TFT_LIGHTGREY)
    {}

    void 
    draw(bool forceDraw);

    void 
    on_touch();

    void
    set_on_touch_color
    (uint16_t color)
    {touch_color = color;}

    void
    set_text_color
    (uint16_t color)
    {text_color = color;}
    
    /**
     * @brief Set wrapping of the text
     * 
     */
    void 
    set_wrap();

    String 
    get_str();
};


#endif