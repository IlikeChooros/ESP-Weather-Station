#pragma once

#include "../../../data_structures/Vector.h"
#include "../../../data_structures/Vector.cpp"

#include "GeoDisplayItem.h"

enum Move
{
    LEFT,
    RIGHT
};

class 
GeoLocItem
{
    Vector<City_info> data;

    GeoDisplayItem** display;

    WeatherClient* wclient;
    TFT_eSPI* tft;

    int8_t
    get_pos();

public:
    GeoLocItem(
        TFT_eSPI* tft,
        WeatherClient* wclient
    );

    /**
     * @brief Gets location struct via weather client
     * 
     * @param city_name 
     */
    void 
    set_loctation
    (String city_name);

    /**
     * @brief Clear previous data Vector
     * 
     */
    void 
    clear();

    void
    draw(bool forceDraw);
    
    /**
     * @brief Changes displayed data to another one
     */
    void
    change(Move);
};
