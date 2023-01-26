#pragma once

#include "ChartScreens.h"

class ChartScreenNextDays: public ChartScreens
{
    public:
    /**
     * @brief Chart Screen that will display in 3 hour format
     * forecasted weather for chosen day (idx)
     * 
     * @param tft 
     * @param bg_c 
     */
    ChartScreenNextDays(
        TFT_eSPI *tft,
        uint16_t bg_c
    ): ChartScreens(tft, bg_c)
    {}

    void draw(
        Vector<WeatherData>& data,
        int8_t* min_max,
        bool forceDraw
    );
};