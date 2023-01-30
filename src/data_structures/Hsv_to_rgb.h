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

inline
uint16_t
to_rgb(
    uint8_t r, 
    uint8_t g, 
    uint8_t b
)
{
    uint32_t RGB;
    r = (r >> 3);
    g = (g >> 2);
    b = (b >> 3);

    RGB = RGB | (r << 11);
    RGB = RGB | (g << 5);
    RGB = RGB | (b);

    return RGB;
}

inline
uint16_t
HSV_RGB(
    HSV color
)
{
    float s = color.satrutaion / 100;
    float v = color.value / 100;

    float C = s * v;
    float X = C * (1 - abs(fmod(color.hue / 60, 2) - 1));
    float m = v - C;

    float r, g, b;

    if (color.hue < 60)
    {
        r = C, g = X, b = 0;
    }
    else if (color.hue < 120)
    {
        r = X, g = C, b = 0;
    }
    else if (color.hue < 180)
    {
        r = 0, g = C, b = X;
    }
    else if (color.hue < 240)
    {
        r = 0, g = X, b = C;
    }
    else if (color.hue < 300)
    {
        r = X, g = 0, b = C;
    }
    else
    {
        r = C, g = 0, b = X;
    }

    return to_rgb(
        (r + m) * 255,
        (g + m) * 255,
        (b + m) * 255);
}

inline
uint16_t
convert_to_idx(
    int16_t t
)
{
    int16_t temp = t + 10;
    temp = temp > TEMP_RANGE ? TEMP_RANGE : temp;
    temp = temp < 0 ? 0 : temp;
    return temp;
}

inline
uint16_t*
set_text_colors()
{
    uint16_t *temp_text_colors = new uint16_t[TEMP_RANGE];
    HSV *hsv = new HSV;

    hsv->hue = 0;
    hsv->satrutaion = 47;
    hsv->value = 100;

    float itr = (float)250 / TEMP_RANGE;

    for (int8_t t = TEMP_RANGE - 1; t >= 0; t--)
    {
        temp_text_colors[t] = HSV_RGB(*hsv);
        hsv->hue += itr;
    }

    delete hsv;
    return temp_text_colors;
}

inline
uint16_t
get_text_color(
    int16_t temp, 
    uint16_t *temp_text_colors
)
{
    return temp_text_colors[convert_to_idx(temp)];
}

/**
 * @brief Get the colors grey fade object
 * 
 * @param number_of_colors
 * @return uint16_t*  as new, should be deleted
 */
inline
uint16_t*
get_colors_grey_fade(
    uint8_t number_of_colors
)
{
    uint16_t *colors = new uint16_t[number_of_colors];
    HSV *hsv = new HSV;

    colors[0]=0xFFFF;
    hsv->hue = 0;
    hsv->satrutaion = 0;
    hsv->value = 50;

    float itr = float(40 / number_of_colors);

    for (uint8_t i=1; i<number_of_colors; i++)
    {
        hsv->value -= itr;
        colors[i] = HSV_RGB(*hsv);
    }

    delete hsv;
    return colors;
}