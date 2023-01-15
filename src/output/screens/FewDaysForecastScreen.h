#ifndef FEW_DAYS_FORECAST_SCREEN_H
#define FEW_DAYS_FORECAST_SCREEN_H

#include "MainScreen.h"
#include "../items/ColumnItem.h"
#include "../../weather_client/Forecast.h"
#include "../items/TextItem.h"
#include "../items/TimeItem.h"
#include "../items/DropletItem.h"
#include "../icons/WeatherIcon.h"
#include "../icons/WindIcon.h"
#include "../icons/Icons.h"
#include "../../weather_client/Weather.h"
#include "../../data_structures/Hsv_to_rgb.h"

#define NUMBER_OF_COLUMN_ITEMS 6
#define NUMBER_OF_DAYS_TO_FORECAST 4

#define POP 0
#define MAX_TEMP 1
#define MIN_TEMP 2


class FewDaysForecastScreen: public MainScreen
{
    ColumnItem* column_items;
    uint8_t column_height,
            column_width;
    float* getMinMaxTemp_pop(Forecast* forecast, uint8_t start_idx);
    public:
    FewDaysForecastScreen(TFT_eSPI *tft, uint16_t bg_c): MainScreen(tft,bg_c){
        column_items = new ColumnItem[NUMBER_OF_DAYS_TO_FORECAST];
        column_height = this->_tft->width();
        column_width = this->_tft->height()/NUMBER_OF_DAYS_TO_FORECAST;

        for (uint8_t i=0; i<NUMBER_OF_DAYS_TO_FORECAST; i++)
        {
            column_items[i].number_of_items = NUMBER_OF_COLUMN_ITEMS;
            column_items[i].weather_items = new WeatherItem* [NUMBER_OF_COLUMN_ITEMS]{
                new TimeItem(_tft, i*column_width+10, 10, bg_c, MIST, 2,2, 0, false),
                new WeatherIcon(_tft,i*column_width,40,column_width, this->bg_c),
                new TextTemp(_tft, i*column_width+8, 55 + column_width, 4, 1, TFT_WHITE, "%d `C",bg_c),
                new TextFeelsLike(_tft, i*column_width+10, 80 + column_width, 4,1, TFT_WHITE, "%d `C", bg_c),
                new TextPop(_tft, i*column_width+25, 100 + column_width + 5, 2,1,WATER, "%d %%", bg_c),
                new DropletItem(_tft,i*column_width+5, 105 + column_width, 20, bg_c)
            };
        }
    }
    void draw(Forecast* forecast, bool forceDraw);
    void draw(Weather* weather, bool forceDraw)
    {
        return;
    }
    void refresh(bool forceUpdate)
    {
        return;
    }
    void init() {
        return;
    }
};



#endif