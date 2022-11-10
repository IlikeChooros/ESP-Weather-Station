#include "Forecast12Screen.h"

void Forecast12Screen::draw(Forecast* forecast, bool forceDraw)
{
    for (uint8_t i=0;i<NUMBER_OF_HOURS_TO_FORECAST;i++)
    {
        for(uint8_t j=0;j<columnItems[i].number_of_items;j++)
        {
            columnItems[i].weather_items[j]->setWeather(forecast->forecasted_weather[i]);
            columnItems[i].weather_items[j]->draw(forceDraw);
        }
    }
}