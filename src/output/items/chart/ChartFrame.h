#pragma once

#include "ChartItem.h"

#define SQRT_2_DIV_2 0.7071f
#define NUMBER_OF_SECTIONS 5

class ChartFrameVFull: public ChartItem
{
    float scale_positive;
    float scale_negative;
    i8 number_of_sections;

    String name;

    ui16
    get_y(
        i16 data
    );

    public:
    /**
     * @brief Construct a new Chart Frame V Full object
     * 
     * @param tft 
     * @param color color of the frame
     */
    ChartFrameVFull(
        TFT_eSPI *tft,
        uint16_t color,
        uint16_t starting_x,
        String name
    ): ChartItem(tft, color, starting_x) 
    {this->name = name;}

    /**
     * @brief Draws chart frame.
     * 
     * @param forceDraw 
     */
    void
    draw(bool forceDraw);

    /**
     * @brief Set the data, useless for this object
     * 
     * @param data 
     */
    void
    set_data(Vector<WeatherData>& data) {return;}


    void set_min_max(
        int16_t min,
        int16_t max
    )
    {
        min_value = min;
        max_value = max;
        scale_positive = (float)((MAX_POSITIVE)/max_value);
        scale_negative = min_value < 0 ? -(float)((MAX_NEGATIVE)/min_value) :(float)((MAX_NEGATIVE)/min_value);
        number_of_sections = (max - min)/2 < 8 ? (max-min)/2 : 8;
    }
};

class ChartFrameVUp: public ChartItem
{
    float scale;
    i8 number_of_sections;

    String name;

    ui16
    get_y(
        i16 data
    );

    public:
    ChartFrameVUp(
        TFT_eSPI *tft,
        uint16_t color,
        uint16_t starting_x,
        String name
    ): ChartItem(tft, color, starting_x) 
    {this->name = name;}

    void
    draw(bool forceDraw);

    void
    set_data(Vector<WeatherData>& data) {return;}

    void set_min_max(
        int16_t min,
        int16_t max
    )
    {
        max_value = max;
        min_value = min;
        this->scale = (float)(MAX_POSITIVE/max_value); 
        number_of_sections = (max - min)/2 > 5 ? 5 : (max - min)/2; 
    }
};

class ChartFrameTime
{
    TFT_eSPI *tft;
    ui16 color;

    public:
    ChartFrameTime(
        TFT_eSPI *tft,
        uint16_t color
    ): tft(tft), color(color)
    {}

    /**
     * @brief Draws time frame
     * 
     * @param forceDraw 
     */
    void
    draw(bool forceDraw);
};

