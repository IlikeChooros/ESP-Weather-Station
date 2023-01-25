#pragma once

#include "ChartScreens.h"
#include "../../items/chart/LineChart.h"
#include "../../items/chart/ChartFrame.h"
#include "../../items/chart/ChartName.h"

class ChartScreenNext12Hours: public ChartScreens
{
    ChartItem **charts;
    ChartFrameTime* chart_time;
    ChartName** chart_names;

    void
    draw_name(Vector<WeatherData>& data);
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
        Vector<WeatherData>& data,
        int8_t* min_max,
        bool forceDraw
    );
};