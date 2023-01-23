#pragma once

#include "TFT_eSPI.h"
#include "SPI.h"

#include "../../../data_structures/get_day.h"
#include "../../../data_structures/Vector.h"
#include "../../../data_structures/Vector.cpp"
#include "../../../weather_client/WeatherData.h"

#define MIDDLE_Y 130
#define STARTING_X 16
#define MAX_POSITIVE 90
#define MAX_NEGATIVE 90
#define HOURS_PIXELS 12
#define MINUTES_5_PIXELS 1

class ChartItem
{
    public:
    explicit ChartItem(TFT_eSPI *tft, uint16_t color ,uint8_t pixel_offset, int16_t min_value, int16_t max_value)
    {
        this->tft = tft;
        this->color = color;
        this->pixel_offset = pixel_offset;
        this->min_value = min_value;
        this->max_value = max_value;
    }
    virtual void set_data(Vector<WeatherData>& data) = 0;
    virtual void draw(bool forceDraw) = 0;

    protected:
    uint16_t color;
    uint8_t pixel_offset;
    int16_t min_value;
    int16_t max_value;
    TFT_eSPI *tft;
};