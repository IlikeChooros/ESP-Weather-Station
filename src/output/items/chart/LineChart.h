#pragma once

#include "ChartItem.h"


#define POP_IDX 0 
#define TEMP_IDX 1
#define FEELS_IDX 2
#define HUM_IDX 3

class LineCharTemp: public ChartItem{
    float scale_positive;
    float scale_negative;

    public:
    LineCharTemp(
        TFT_eSPI *tft,
        uint16_t color,
        uint16_t starting_x
    );

    void
    draw(bool forceDraw);

    void
    set_data(std::vector<WeatherData>& data);

    void 
    set_min_max(
        int16_t min,
        int16_t max
    );
};


class LineChartFeelsLike: public ChartItem
{

    float scale_positive;
    float scale_negative;

    public:
    LineChartFeelsLike(
        TFT_eSPI *tft,
        uint16_t color,
        uint16_t starting_x
    );

    void
    draw(bool forceDraw);


    void
    set_data(std::vector<WeatherData>& data);

    void set_min_max(
        int16_t min,
        int16_t max
    );
};


class LineChartHumidity: public ChartItem
{
    float scale;

    public:
    LineChartHumidity(
        TFT_eSPI *tft,
        uint16_t color,
        uint16_t starting_x
    );

    void
    draw(bool forceDraw);

    void
    set_data(std::vector<WeatherData>& data);

    void set_min_max(
        int16_t min,
        int16_t max
    );
};


class LineChartPop: public ChartItem
{
    float scale;

    public:
    LineChartPop(
        TFT_eSPI *tft,
        uint16_t color,
        uint16_t starting_x
    );

    void
    draw(bool forceDraw);

    void
    set_data(std::vector<WeatherData>& data);

    void set_min_max(
        int16_t min,
        int16_t max
    );
};