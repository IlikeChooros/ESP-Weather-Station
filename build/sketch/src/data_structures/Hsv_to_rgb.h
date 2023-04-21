#line 1 "c:\\Users\\pawel\\arduino\\ESP-Weather-Station\\src\\data_structures\\Hsv_to_rgb.h"
#pragma once

#define TEMP_RANGE 35

#include <Arduino.h>

class HSV
{
public:
    float hue;
    float satrutaion;
    float value;
};

uint16_t
to_rgb(
    uint8_t r, 
    uint8_t g, 
    uint8_t b
);

uint16_t
HSV_RGB(
    HSV color
);

uint16_t
convert_to_idx(
    int16_t t
);

uint16_t*
set_text_colors();

uint16_t
get_text_color(
    int16_t temp, 
    uint16_t *temp_text_colors
);

/**
 * @brief Get the colors grey fade object
 * 
 * @param number_of_colors
 * @return uint16_t*  as new, should be deleted
 */
uint16_t*
get_colors_grey_fade(
    uint8_t number_of_colors
);