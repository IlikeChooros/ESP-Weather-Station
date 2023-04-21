#line 1 "c:\\Users\\pawel\\arduino\\ESP-Weather-Station\\src\\data_structures\\Point.h"
#pragma once

#include <Arduino.h>

class Point
{
public:
    Point(
        uint16_t x = 0, 
        uint16_t y = 0
    ): x(x), y(y) {}

    uint16_t x;
    uint16_t y;
};
