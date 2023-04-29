#pragma once

#include "WeatherItem.h"

class ColumnItem
{
    public:
    WeatherItem** weather_items;
    uint8_t number_of_items;
};
