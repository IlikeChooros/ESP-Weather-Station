#ifndef COLUMN_ITEM_H
#define COLUMN_ITEM_H

#include "WeatherItem.h"

class ColumnItem
{
    public:
    WeatherItem** weather_items;
    uint8_t number_of_items;
};


#endif