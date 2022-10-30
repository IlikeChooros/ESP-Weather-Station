#ifndef POINT_H
#define POINT_H

#include <math.h>
#include <Arduino.h>

class Point{
    public:
    Point(uint16_t = 0, uint16_t = 0);
    uint16_t x;
    uint16_t y;
};


#endif