#line 1 "c:\\Users\\pawel\\arduino\\ESP-Weather-Station\\src\\output\\items\\scroll\\ScrollItem.h"
#pragma once

#include "TFT_eSPI.h"

class ScrollItem
{
    TFT_eSPI* tft;

    uint16_t x;
    uint16_t y;
    uint16_t w;
    uint16_t h;

    uint8_t max_range;
    uint8_t prev_idx;
    uint8_t segmenent_height;
public:
    ScrollItem(
        TFT_eSPI* tft,
        uint16_t x,
        uint16_t y,
        uint16_t w,
        uint16_t h,
        uint8_t max_range
    );

    void
    draw(uint8_t);
};


