#include "Forecast12Screen.h"

Forecast12Screen::Forecast12Screen(TFT_eSPI *tft, uint16_t bg_c)
{
    this->_tft = tft;
    this->bg_c = bg_c;

    // screen is rotated
    column_height = this->_tft->width();
    column_width = this->_tft->height()/NUMBER_OF_HOURS_TO_FORECAST;
    columnItems = new ColumnItem[NUMBER_OF_HOURS_TO_FORECAST];

    for(uint8_t i=0;i<NUMBER_OF_HOURS_TO_FORECAST;i++)
    {
        columnItems[i].number_of_items = NUMBER_OF_COLUMN_ITEMS;
        columnItems[i].weather_items = new WeatherItem*[NUMBER_OF_COLUMN_ITEMS]{
            new TimeItem(_tft, i*column_width+5, 10, bg_c, MIST, 1,2, 0),
            new WeatherIcon(_tft,i*column_width,40,column_width, this->bg_c),
            new TextTemp(_tft, i*column_width+8, 40 + column_width, 4, 1, TFT_WHITE, "%d `C",bg_c),
            new TextFeelsLike(_tft, i*column_width+10, 65 + column_width,2,1, TFT_WHITE, "(%d `C)", bg_c),
            new TextPop(_tft, i*column_width+22, 85 + column_width, 4,1,WATER, "%d %%", bg_c),
            new DropletItem(_tft,i*column_width+2, 85 + column_width, 20, bg_c)
        };
    }
}

void Forecast12Screen::draw(Forecast* forecast)
{
    double s [4]={0, 0.29f, 0.49f, 0.69f};
    for (uint8_t i=0;i<NUMBER_OF_HOURS_TO_FORECAST;i++)
    {
        forecast->forecasted_weather[i]->_pop = s[i];
        for(uint8_t j=0;j<columnItems[i].number_of_items;j++)
        {
            columnItems[i].weather_items[j]->setWeather(forecast->forecasted_weather[i]);
            columnItems[i].weather_items[j]->draw();
        }
    }
}