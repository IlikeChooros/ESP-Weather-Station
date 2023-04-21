#line 1 "c:\\Users\\pawel\\arduino\\ESP-Weather-Station\\src\\output\\items\\ColumnItem.h"
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