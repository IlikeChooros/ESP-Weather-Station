#pragma once

#include <TFT_eSPI.h> 
#include <SPI.h>
#include <Arduino.h>

#include "../../items/WeatherDataCollector.h"

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
     * @param bg_c 
     */
    explicit 
    ChartScreens(
        TFT_eSPI *tft,
        uint16_t bg_c
    ): tft(tft), bg_c(bg_c){}

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

    TFT_eSPI *tft;
    uint16_t bg_c;
};