#include "CurrentWeatherScreen.h"

void CurrentWeatherScreen::draw(Weather* weather, bool forceDraw)
{
    for (uint8_t i = 0; i<NUMBER_OF_WEATHER_ITEMS;i++)
    {
        weather_items[i]
        ->setWeather(weather);
        weather_items[i]
        ->draw(forceDraw);
    }

    if (forceDraw)
    {
        wifi->draw();
    }

    date->draw(forceDraw);
    // Fonts: 1,2,4,6,7,8
}

void CurrentWeatherScreen::refresh()
{
    date->add_second();
}

