#pragma once

#include "ChartItem.h"

class LineCharTemp: public ChartItem
{
    uint16_t starting_x;
    float scale_positive;
    float scale_negative;
    Vector<WeatherData> data;
    public:
    LineCharTemp(TFT_eSPI *tft, uint16_t color, uint8_t pixel_offset, int16_t min_value, int16_t max_value):
    ChartItem(tft, color, pixel_offset, min_value, max_value){
        scale_positive = (float)((MIDDLE_Y - MAX_POSITIVE)/max_value);
        scale_negative = min_value < 0 ? -(float)((MIDDLE_Y + MAX_NEGATIVE)/min_value) :(float)((MIDDLE_Y + MAX_NEGATIVE)/min_value);
    }
    void draw(bool forceDraw);
    uint16_t get_y(int16_t data);
    void set_data(Vector<WeatherData>& data);
};