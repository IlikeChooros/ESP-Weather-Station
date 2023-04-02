#pragma once

#include "TFT_eSPI.h"
#include <vector>

#include "../../../data_structures/get_day.h"
#include "../../../weather_client/WeatherData.h"

#define MIDDLE_Y 120
#define STARTING_X 14
#define MAX_POSITIVE 100
#define MAX_NEGATIVE 100
#define HOURS_PIXELS 12
#define MINUTES_5_PIXELS 1

using i16 = int16_t;
using ui16 = uint16_t;
using i8 = int8_t;
using ui8 = uint8_t;

class ChartItem
{
    protected:
    ui16 color;
    uint8_t pixel_offset;
    int16_t min_value;
    int16_t max_value;
    uint16_t starting_x_;
    TFT_eSPI *tft;
    std::vector<WeatherData> data;

public:

    explicit ChartItem(
        TFT_eSPI *tft,
        uint16_t color,
        uint16_t starting_x
    ): tft(tft), color(color),
    starting_x_(starting_x) {}

    virtual void set_data(
        std::vector<WeatherData>& data
    ) = 0;

    virtual void draw(
        bool forceDraw
    ) = 0;

    /**
     * @brief Set the minimum and maxixum values.
     * According to these values, chartFram and LineChartTemp will scale
     * itself
     * 
     * @param min 
     * @param max 
     */
    virtual void set_min_max(
        int16_t min,
        int16_t max
    ) = 0;
};