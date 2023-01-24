#pragma once

#include "ChartItem.h"

class LineCharTemp: public ChartItem
{

    float scale_positive;
    float scale_negative;

    uint16_t
    get_y(int16_t data);

    public:
    LineCharTemp(
        TFT_eSPI *tft,
        uint16_t color,
        uint16_t starting_x
    ): ChartItem(tft, color, starting_x) {}

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


class LineChartFeelsLike: public ChartItem
{

    float scale_positive;
    float scale_negative;

    uint16_t
    get_y(int16_t data);

    public:
    LineChartFeelsLike(
        TFT_eSPI *tft,
        uint16_t color,
        uint16_t starting_x
    ): ChartItem(tft, color, starting_x) {}

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


class LineChartHumidity: public ChartItem
{
    float scale;

    uint16_t
    get_y(int16_t data);

    public:
    LineChartHumidity(
        TFT_eSPI *tft,
        uint16_t color,
        uint16_t starting_x
    ): ChartItem(tft, color, starting_x) {}

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
        scale = (float)((MAX_POSITIVE)/max_value);
    }
};


class LineChartPop: public ChartItem
{
    float scale;

    uint16_t
    get_y(int16_t data);

    public:
    LineChartPop(
        TFT_eSPI *tft,
        uint16_t color,
        uint16_t starting_x
    ): ChartItem(tft, color, starting_x) {}

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
        scale = (float)((MAX_POSITIVE)/max_value);
    }
};