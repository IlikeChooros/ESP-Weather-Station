#pragma once

#include "TFT_eSPI.h"
#include "SPI.h"

#include "../../../data_structures/get_day.h"
#include "../../../data_structures/Vector.h"
#include "../../../data_structures/Vector.cpp"
#include "../../../weather_client/WeatherData.h"

#define MIDDLE_Y 120
#define STARTING_X 16
#define MAX_POSITIVE 90
#define MAX_NEGATIVE 90
#define HOURS_PIXELS 36
#define MINUTES_5_PIXELS 1
#define MIN_HEIGHT_ 30
#define MAX_HEIGHT_ 210

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
    TFT_eSPI *tft;
    Vector<WeatherData> data;

    public:

    explicit ChartItem(
        TFT_eSPI *tft,
        uint16_t color
    ): tft(tft), color(color) {}

    virtual void set_data(
        Vector<WeatherData>& data
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