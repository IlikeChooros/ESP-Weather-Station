#pragma once

#include "TFT_eSPI.h"
#include <vector>

#include "../../input/TouchButton.h"
#include "../icons/drawings.h"
#include "../../data_structures/Point.h"
#include "../../data_structures/print_data.h"

class
ListItem: public TouchButton
{
    TFT_eSPI* tft;

    bool marked_;
    bool wrap;

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
    );


    void 
    draw(bool forceDraw);

    void
    on_touch();

    ListItem*
    marked(bool marked);

    ListItem*
    wrap_text(bool);

    ListItem*
    set_data(
        String str,
        bool same_line,
        String font,
        uint16_t text_color
    );

    ListItem*
    set_position(Point& pos);

    std::vector<print_data>&
    stored();
};