#pragma once

#include <Arduino.h>

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

    print_data() = default;
    
    String string;
    uint8_t font;
    uint8_t size;
    uint16_t color;
    bool same_line;
};