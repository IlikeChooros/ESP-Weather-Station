#pragma once

#include "TFT_eSPI.h"
#include <vector>

#include "../../../data_structures/get_day.h"
#include "../../../weather_client/WeatherData.h"

#define CHART_NAME_WIDTH 15
#define CHART_NAME_HEIGHT 6

class ChartName
{
    TFT_eSPI* tft;

    String str;

    uint16_t x;
    uint16_t y;
    uint16_t color;

    public:
    ChartName(
        TFT_eSPI* tft,
        String str,
        uint16_t x,
        uint16_t y,
        uint16_t color
    ): tft(tft), str(str), x(x), y(y), color(color) {}

    /**
    * @brief Draws object to tft screen
    */
    void 
    draw();
};
