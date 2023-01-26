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

    wifi->draw(forceDraw);
    date->draw(forceDraw);
    // Fonts: 1,2,4,6,7,8
}
void CurrentWeatherScreen::refresh(bool forceUpdate)
{
    date->add_second(forceUpdate);
}

