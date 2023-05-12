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
    );

    /**
     * @brief Draws the chart on to the TFT screen
     * 
     * @param data Obtained data via WeatherDataCollector
     * @param forceDraw Boolean value to draw forcefully objects in this 
     *                  screen
     */
    virtual void draw(
        std::vector<WeatherData>& data,
        int8_t* min_max,
        bool forceDraw
    ) = 0;

    protected:

    void
    draw_bg();

    void
    draw_(
        std::vector<WeatherData>& data,
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