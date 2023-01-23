#pragma once

#include "ChartItem.h"

#define SQRT_2_DIV_2 0.7071f
#define NUMBER_OF_SECTIONS 5

class ChartFrameVFull: public ChartItem
{
    float scale_positive;
    float scale_negative;
    Vector<WeatherData> data;
    public:
    ChartFrameVFull(TFT_eSPI *tft, uint16_t color ,uint8_t pixel_offset, int16_t min_value, int16_t max_value):
    ChartItem(tft, color, pixel_offset, min_value, max_value) {
        scale_positive = (float)((MIDDLE_Y - MAX_POSITIVE)/max_value);
        scale_negative = min_value < 0 ? -(float)((MIDDLE_Y + MAX_NEGATIVE)/min_value) :(float)((MIDDLE_Y + MAX_NEGATIVE)/min_value);
    }
    void draw(bool forceDraw);
    void set_data(Vector<WeatherData>& data){
        this->data = data;
    }
};

class ChartFrameVUp: public ChartItem
{
    Vector<WeatherData> data;
    float scale;
    public:
    ChartFrameVUp(TFT_eSPI *tft, uint16_t color ,uint8_t pixel_offset, int16_t min_value, int16_t max_value):
    ChartItem(tft, color, pixel_offset, min_value, max_value) {
        this->scale = (float)((MIDDLE_Y - MAX_POSITIVE)/max_value); 
    }
    void draw(bool forceDraw);
    void set_data(Vector<WeatherData>& data);
};

class ChartFrameVDown: public ChartItem
{
    Vector<WeatherData> data;
    float scale;
    public:
    ChartFrameVDown(TFT_eSPI *tft, uint16_t color ,uint8_t pixel_offset, int16_t min_value, int16_t max_value):
    ChartItem(tft, color, pixel_offset, min_value, max_value) {
        this->scale = (float)((MIDDLE_Y + MAX_NEGATIVE)/min_value); 
    }
    void draw(bool forceDraw);
    void set_data(Vector<WeatherData>& data);
};

class ChartFrameHLeft: public ChartItem
{
    Vector<WeatherData> data;
    float scale;
    public:
    ChartFrameHLeft(TFT_eSPI *tft, uint16_t color ,uint8_t pixel_offset, int16_t min_value, int16_t max_value):
    ChartItem(tft, color, pixel_offset, min_value, max_value) {
    }
    void draw(bool forceDraw);
    void set_data(Vector<WeatherData>& data);
};

