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
    void draw_bg();
    public:

    ChartScreen(
        TFT_eSPI *tft,
        uint16_t bg_c,
        Vector<uint16_t>& chart_colors
    ): tft(tft), bg_c(bg_c), chart_colors(chart_colors) 
    {
        charts = new ChartItem* [2]{
            new ChartFrameVFull(tft, TFT_DARKGREY),
            new LineCharTemp(tft, TFT_YELLOW)
        };

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