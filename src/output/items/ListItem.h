#pragma once

#include "TFT_eSPI.h"
#include <vector>

#include "../../input/TouchButton.h"
#include "../icons/drawings.h"
#include "../../data_structures/Point.h"

class print_data
{

public:
    print_data(
        String string,
        uint8_t font,
        uint8_t size,
        uint16_t color,
        bool same_line
    ): string(string), font(font),
    size(size), color(color),
    same_line(same_line) {}
    
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

    std::vector<print_data> data;

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
    tft(tft), marked_(false) {}


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

    ListItem*
    set_position(Point& pos);

    std::vector<print_data>&
    stored();
};