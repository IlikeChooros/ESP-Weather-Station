#pragma once

#include <TFT_eSPI.h> 
#include <SPI.h>
#include <Arduino.h>

#include "../../items/WeatherDataCollector.h"
#include "../../items/chart/LineChart.h"
#include "../../items/chart/ChartFrame.h"
#include "../../items/chart/ChartName.h"

#define POP_COLOR TFT_BLUE
#define TEMP_COLOR TFT_YELLOW
#define FEELS_LIKE_COLOR TFT_ORANGE
#define HUMIDITY_COLOR TFT_SKYBLUE

class ChartScreens
{
    public:
    /**
     * @brief Mother, virtual class for ChartScreens
     * 
     * @param tft 
     * @param bg_c background color
     */
    explicit 
    ChartScreens(
        TFT_eSPI *tft,
        uint16_t bg_c
    ): tft(tft), bg_c(bg_c)
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

    /**
     * @brief Draws the chart on to the TFT screen
     * 
     * @param data Obtained data via WeatherDataCollector
     * @param forceDraw Boolean value to draw forcefully objects in this 
     *                  screen
     */
    virtual void draw(
        Vector<WeatherData>& data,
        int8_t* min_max,
        bool forceDraw
    ) = 0;

    protected:

    void
    draw_bg();

    void
    draw_(
        Vector<WeatherData>& data,
        int8_t* min_max,
        bool forceDraw,
        String str
    );

    void 
    draw_name(
        String name
    );

    TFT_eSPI *tft;
    uint16_t bg_c;

    ChartItem **charts;
    ChartFrameTime* chart_time;
    ChartName** chart_names;
};