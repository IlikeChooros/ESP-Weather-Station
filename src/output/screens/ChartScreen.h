#pragma once

#include <TFT_eSPI.h> 
#include <SPI.h>
#include <Arduino.h>

#include "../items/WeatherDataCollector.h"
#include "../items/chart/LineChart.h"
#include "../items/chart/ChartFrame.h"

class ChartScreen
{
    TFT_eSPI *tft;
    uint16_t bg_c;
    Vector<uint16_t> chart_colors;

    ChartItem **charts;
    ChartFrameTime* chart_time;

    void draw_bg();
    public:

    ChartScreen(
        TFT_eSPI *tft,
        uint16_t bg_c,
        Vector<uint16_t>& chart_colors
    ): tft(tft), bg_c(bg_c), chart_colors(chart_colors) 
    {
        charts = new ChartItem* [6]{
            new ChartFrameVFull(tft, TFT_DARKGREY, STARTING_X, "`C"),
            new ChartFrameVUp(tft, TFT_DARKGREY, 302, "%"),
            new LineChartHumidity(tft, TFT_SKYBLUE, STARTING_X),
            new LineChartPop(tft, TFT_BLUE, STARTING_X),
            new LineCharTemp(tft, TFT_YELLOW, STARTING_X),
            new LineChartFeelsLike(tft, TFT_ORANGE, STARTING_X)
        };
        chart_time = new ChartFrameTime(tft, TFT_DARKGREY);
    }

    /**
     * @brief Draws the chart on to the TFT screen
     * 
     * @param data Obtained data via WeatherDataCollector
     * @param forceDraw Boolean value to draw forcefully objects in this 
     *                  screen
     */
    void draw(
        Vector<WeatherData>& data,
        int8_t* min_max,
        bool forceDraw
    );
};