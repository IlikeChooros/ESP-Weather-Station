#include "CurrentWeatherScreen.h"

void CurrentWeatherScreen::draw(Weather* weather, bool forceDraw)
{
    for (uint8_t i = 0; i<NUMBER_OF_WEATHER_ITEMS;i++)
    {
        Serial.println(String(i)+" items");
        weather_items[i]
        ->setWeather(weather);
        Serial.println("set weather");
        weather_items[i]
        ->draw(forceDraw);
        Serial.println("draw");
    }

    Serial.println("draw wifi");
    wifi->draw(forceDraw);
    Serial.println("date draw");
    date->draw(forceDraw);
    // Fonts: 1,2,4,6,7,8
}
void CurrentWeatherScreen::refresh(bool forceUpdate)
{
    date->add_second(forceUpdate);
}

