#pragma once

#include <Arduino.h>

class print_data
{

public:
    print_data(
        String string,
        String font,
        uint16_t color,
        bool same_line
    ): string(string), font(font), color(color),
    same_line(same_line) {}

    print_data() = default;
    
    String string;
    String font;
    uint16_t color;
    bool same_line;
};