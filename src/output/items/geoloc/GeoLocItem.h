#pragma once

#include <vector>

#include "GeoDisplayItem.h"

enum class
Move
{
    LEFT,
    RIGHT
};

class 
GeoLocItem
{
    std::vector<City_info> data;

    GeoDisplayItem** display;

    WeatherClient* wclient;
    TFT_eSPI* tft;

    uint16_t x;
    uint16_t y;
    uint16_t w;
    uint16_t h;

public:
    GeoLocItem(
        TFT_eSPI* tft,
        WeatherClient* wclient,
        uint16_t x,
        uint16_t y,
        uint16_t w,
        uint16_t h
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
     * @brief Clear previous data std::vector
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
