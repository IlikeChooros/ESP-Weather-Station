#ifndef COORDINATE_SYSTEM_H
#define COORDINATE_SYSTEM_H

#include "../data_structures/Point.h"

#include <Arduino.h>
#include <TFT_eSPI.h> 
#include <SPI.h>

class Coordinate_system
{
    TFT_eSPI * _tft;

    public:
    Coordinate_system(TFT_eSPI* tft);
    void draw_coordinate_system(uint16_t resolution, Point cursor);
};



#endif