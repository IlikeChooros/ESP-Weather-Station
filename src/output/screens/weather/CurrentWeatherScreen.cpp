#include "CurrentWeatherScreen.h"

extern City_info picked_city;

void 
CurrentWeatherScreen::
draw(Weather* weather, bool forceDraw)
{
    for (uint8_t i = 0; i<NUMBER_OF_WEATHER_ITEMS;i++){
        weather_items[i]
        ->setWeather(weather);
        weather_items[i]
        ->draw(forceDraw);
    }
    wifi->draw(forceDraw);
    date->draw(forceDraw);
    draw_city_info(forceDraw);
}

void
CurrentWeatherScreen::
draw(Forecast*, bool){
    return;
}

void 
CurrentWeatherScreen::
refresh(bool forceUpdate){
    date->add_second(forceUpdate);
}

void 
CurrentWeatherScreen::
draw_city_info(bool forceDraw){
    if(!forceDraw){
        return;
    }
    _tft->setTextColor(TFT_LIGHTGREY);
    _tft->setTextSize(1);
    uint16_t x = 32 + _tft->drawString(picked_city.name, 27, 0, 2);
    _tft->drawString(picked_city.country, x, 0, 2);
}

void
CurrentWeatherScreen::
init(Weather* weather){
    date
    ->timezone(weather->_timezone)
    ->init();
}