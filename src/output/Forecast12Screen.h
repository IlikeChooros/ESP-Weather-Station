#ifndef FORECAST_12_SCREEN_H
#define FORECAST_12_SCREEN_H

#include "ColumnItem.h"
#include "../weather_client/Forecast.h"
#include "WeatherItem.h"
#include "TextItem.h"
#include "TimeItem.h"
#include "icons/DropletItem.h"
#include "icons/WeatherIcon.h"
#include "icons/WindIcon.h"
#include "icons/Icons.h"
#include "../weather_client/Weather.h"
#include "../data_structures/Hsv_to_rgb.h"

#define NUMBER_OF_COLUMN_ITEMS 6

class Forecast12Screen
{
    TFT_eSPI *_tft;
    uint16_t bg_c;

    uint8_t column_height,
            column_width;

    ColumnItem* columnItems;
    public:
    Forecast12Screen(TFT_eSPI* tft, uint16_t bg_c);
    void draw(Forecast* forecast, bool forceDraw);
};

#endif