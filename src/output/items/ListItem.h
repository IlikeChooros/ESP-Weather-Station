#pragma once

#include "TFT_eSPI.h"
#include "SPI.h"

#include "../../input/TouchButton.h"
#include "../icons/drawings.h"

#include "../../data_structures/Vector.h"
#include "../../data_structures/Vector.cpp"

struct print_data
{
    String string;
    uint8_t font;
    uint8_t size;
    uint16_t color;
    bool same_line;
};

class
ListItem: public TouchButton
{
    TFT_eSPI* tft;

    bool marked_;

    Vector<print_data> data;

    void 
    draw_(uint16_t color);
    
public:
    ListItem(
        TFT_eSPI* tft,
        int16_t x,
        int16_t y,
        int16_t width,
        int16_t height
    ): TouchButton(x, y, width, height),
    tft(tft), marked_(false)
    {}


    void 
    draw(bool forceDraw);

    void
    on_touch();

    ListItem*
    marked(bool marked);

    ListItem*
    set_data(
        String str,
        bool same_line,
        uint8_t font,
        uint8_t text_size,
        uint16_t text_color
    );
};