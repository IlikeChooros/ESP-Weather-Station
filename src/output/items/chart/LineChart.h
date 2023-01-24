#pragma once

#include "ChartItem.h"

class LineCharTemp: public ChartItem
{
    uint16_t starting_x;

    float scale_positive;
    float scale_negative;

    uint16_t
    get_y(int16_t data);

    public:
    LineCharTemp(
        TFT_eSPI *tft,
        uint16_t color
    ): ChartItem(tft, color) {}

    void
    draw(bool forceDraw);


    void
    set_data(Vector<WeatherData>& data);

    void set_min_max(
        int16_t min,
        int16_t max
    )
    {
        min_value = min;
        max_value = max;
        scale_positive = (float)((MAX_POSITIVE)/max_value);
        scale_negative = min_value < 0 ? -(float)((MAX_NEGATIVE)/min_value) :(float)((MAX_NEGATIVE)/min_value);
    }
};