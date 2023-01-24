#pragma once

#include "ChartItem.h"

#define SQRT_2_DIV_2 0.7071f
#define NUMBER_OF_SECTIONS 5

class ChartFrameVFull: public ChartItem
{
    float scale_positive;
    float scale_negative;
    i8 number_of_sections;

    public:
    /**
     * @brief Construct a new Chart Frame V Full object
     * 
     * @param tft 
     * @param color color of the frame
     */
    ChartFrameVFull(
        TFT_eSPI *tft,
        uint16_t color
    ): ChartItem(tft, color) 
    {
        scale_positive = (float)((MIDDLE_Y - MAX_POSITIVE)/max_value);
        scale_negative = min_value < 0 ? -(float)((MIDDLE_Y - MAX_NEGATIVE)/min_value) :(float)((MIDDLE_Y - MAX_NEGATIVE)/min_value);
    }

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
        number_of_sections = (max - min)/2;
    }

    ui16
    get_y(
        i16 data
    );
};

class ChartFrameVUp: public ChartItem
{
    Vector<WeatherData> data;
    float scale;
    public:

    ChartFrameVUp(
        TFT_eSPI *tft,
        uint16_t color
    ): ChartItem(tft, color)
    {
        this->scale = (float)((MIDDLE_Y - MAX_POSITIVE)/max_value); 
    }

    void
    draw(bool forceDraw);

    void
    set_data(Vector<WeatherData>& data);

    void set_min_max(
        int16_t min,
        int16_t max
    );
};

class ChartFrameVDown: public ChartItem
{
    Vector<WeatherData> data;
    float scale;
    public:

    ChartFrameVDown(
        TFT_eSPI *tft,
        uint16_t color
    ): ChartItem(tft, color) 
    {
        this->scale = (float)((MIDDLE_Y + MAX_NEGATIVE)/min_value); 
    }
    void
    draw(bool forceDraw);

    void
    set_data(Vector<WeatherData>& data);

    void set_min_max(
        int16_t min,
        int16_t max
    );
};

class ChartFrameHLeft: public ChartItem
{
    Vector<WeatherData> data;
    float scale;
    public:

    ChartFrameHLeft(
        TFT_eSPI *tft,
        uint16_t color
    ): ChartItem(tft, color)
    {}

    void
    draw(bool forceDraw);

    void
    set_data(Vector<WeatherData>& data);

    void set_min_max(
        int16_t min,
        int16_t max
    );
};

