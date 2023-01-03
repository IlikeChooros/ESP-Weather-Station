#ifndef FORECAST_12_SCREEN_H
#define FORECAST_12_SCREEN_H

#include "MainScreen.h"
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
#define HOURS_TO_12_FORECAST 4

class Forecast12Screen: public MainScreen
{
    uint8_t column_height,
            column_width;

    ColumnItem* columnItems;
    public:
    Forecast12Screen(TFT_eSPI* tft, uint16_t bg_c): MainScreen(tft,bg_c)
    {
        column_height = this->_tft->width();
        column_width = this->_tft->height()/HOURS_TO_12_FORECAST;
        columnItems = new ColumnItem[HOURS_TO_12_FORECAST];

        for(uint8_t i=0;i<HOURS_TO_12_FORECAST;i++)
        {
            columnItems[i].number_of_items = NUMBER_OF_COLUMN_ITEMS;
            columnItems[i].weather_items = new WeatherItem*[NUMBER_OF_COLUMN_ITEMS]{
                new TimeItem(_tft, i*column_width+5, 10, bg_c, MIST, 2,2, 0, true),
                new WeatherIcon(_tft,i*column_width,40,column_width, this->bg_c),
                new TextTemp(_tft, i*column_width+8, 40 + column_width, 4, 1, TFT_WHITE, "%d `C",bg_c),
                new TextFeelsLike(_tft, i*column_width+10, 65 + column_width,2,1, TFT_WHITE, "(%d `C)", bg_c),
                new TextPop(_tft, i*column_width+25, 85 + column_width + 5, 2,1,WATER, "%d %%", bg_c),
                new DropletItem(_tft,i*column_width+5, 85 + column_width, 20, bg_c)
            };
        }
    }
    void draw(Forecast* forecast, bool forceDraw);
    void draw(Weather* weather, bool forceDraw)
    {
        return;
    }
    void refresh()
    {
        return;
    }
};

#endif