#line 1 "c:\\Users\\pawel\\arduino\\ESP-Weather-Station\\src\\output\\screens\\chart\\ChartScreenToday.h"
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
    ): ChartScreens(tft, bg_c)
    {
        charts = new ChartItem* [6]{
            new ChartFrameVFull(tft, TFT_DARKGREY, STARTING_X, "`C"),
            new ChartFrameVUp(tft, TFT_DARKGREY, 301, "%"),
            new LineChartHumidity(tft, HUMIDITY_COLOR, STARTING_X),
            new LineChartPop(tft, POP_COLOR, STARTING_X),
            new LineCharTemp(tft, TEMP_COLOR, STARTING_X),
            new LineChartFeelsLike(tft, FEELS_LIKE_COLOR, STARTING_X)
        };
        chart_time = new ChartFrameTime(tft, TFT_DARKGREY);

        chart_names = new ChartName* [4]{
            new ChartName(tft, "TEMP", 160, 0, TEMP_COLOR),
            new ChartName(tft, "POP", 240, 0, POP_COLOR),
            new ChartName(tft, "FEELS LIKE", 160, 10, FEELS_LIKE_COLOR),
            new ChartName(tft, "HUM", 240, 10, HUMIDITY_COLOR)
        };
    }

    void draw(
        std::vector<WeatherData>& data,
        int8_t* min_max,
        bool forceDraw
    );
};