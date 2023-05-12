#include "Forecast12Screen.h"

Forecast12Screen::
Forecast12Screen(
    TFT_eSPI* tft, 
    uint16_t bg_c
): MainScreen(tft,bg_c)
{
    column_height = this->_tft->width();
    column_width = this->_tft->height()/HOURS_TO_12_FORECAST;
    columnItems = new ColumnItem[HOURS_TO_12_FORECAST];

    for(uint8_t i=0;i<HOURS_TO_12_FORECAST;i++)
    {
        columnItems[i].number_of_items = NUMBER_OF_COLUMN_ITEMS;
        columnItems[i].weather_items = new WeatherItem*[NUMBER_OF_COLUMN_ITEMS]{
            new TimeItem(_tft, i*column_width+column_width/2, 10, bg_c, MIST, WEATHER_FONT, 0, true),
            new WeatherIcon(_tft,i*column_width,40,column_width, this->bg_c),
            new TextTemp(_tft, i*column_width+column_width/2 - 3, 55 + column_width, WEATHER_FONT, TFT_WHITE, "%d °C",bg_c),
            new TextFeelsLike(_tft, i*column_width+column_width/2 - 3, 80 + column_width, WEATHER_FONT, TFT_WHITE, "%d °C", bg_c),
            new TextPop(_tft, i*column_width+25, 100 + column_width + 5, WEATHER_FONT,WATER, "%d %%", bg_c),
            new DropletItem(_tft,i*column_width+5, 100 + column_width, 20, bg_c)
        };
    }
}

void Forecast12Screen::draw(Forecast* forecast, bool forceDraw){
    for (uint8_t i=0;i<HOURS_TO_12_FORECAST;i++){
        for(uint8_t j=0;j<columnItems[i].number_of_items;j++){
            columnItems[i].weather_items[j]->setWeather(forecast->forecasted_weather[i]);
            columnItems[i].weather_items[j]->draw(forceDraw);
        }
    }
}