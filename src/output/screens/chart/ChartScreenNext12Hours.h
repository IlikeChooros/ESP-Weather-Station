#pragma once

#include "ChartScreens.h"

class ChartScreenNext12Hours: public ChartScreens
{
    public:
    /**
     * @brief Chart Screen that will display next 12 hours of weather data
     * 
     * @param tft 
     * @param bg_c 
     */
    ChartScreenNext12Hours(
        TFT_eSPI *tft,
        uint16_t bg_c
    );

    void draw(
        std::vector<WeatherData>& data,
        int8_t* min_max,
        bool forceDraw
    );
};