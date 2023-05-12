#pragma once

#include "ChartScreens.h"

class ChartScreenToday: public ChartScreens
{
    public:
    /**
     * @brief Chart Screen that will display collected weather data up to this moment
     * in 5 minutes format
     * 
     * @param tft 
     * @param bg_c 
     */
    ChartScreenToday(
        TFT_eSPI *tft,
        uint16_t bg_c
    );

    void draw(
        std::vector<WeatherData>& data,
        int8_t* min_max,
        bool forceDraw
    );
};