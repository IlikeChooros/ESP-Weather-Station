#include "CurrentWeatherScreen.h"

extern City_info picked_city;

CurrentWeatherScreen::
CurrentWeatherScreen(TFT_eSPI * tft, uint16_t bg_c): MainScreen(tft,bg_c){
    
    weather_items = new WeatherItem*[NUMBER_OF_WEATHER_ITEMS] {
        new WeatherIcon(this->_tft, 190,30+OFFSET, 125, bg_c),
        new WindIcon(this->_tft, 80, 105+OFFSET, 20, bg_c),
        new TextTemp(this->_tft, 30, 30+OFFSET, LATIN, TFT_WHITE, "%d `C" , bg_c),
        new TextFeelsLike(this->_tft, 35, 80+OFFSET, WEATHER_FONT, TFT_WHITE,"Feels like: %d `C", bg_c),
        new TextWind(this->_tft, 105, 105+OFFSET, WEATHER_FONT, 0x77F2, "%d km/h", bg_c),
        new TextPressure(this->_tft, 105, 135+OFFSET, WEATHER_FONT, 0xB41F, "%d hPa", bg_c),
        new SunriseItem(_tft, 15, 100 + OFFSET, 25, bg_c),
        new SunsetItem(_tft, 15, 130 + OFFSET, 25, bg_c)
    }; 

    wifi = new WiFiItem(this->_tft, 5, 2, 15, bg_c);
    date = new DateItem(this->_tft, 160, 20, 50, bg_c);
}

void 
CurrentWeatherScreen::
draw(Weather* weather, bool forceDraw){
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
    _tft->setTextColor(TFT_LIGHTGREY, bg_c);
    _tft->loadFont(NOTE_FONT);
    uint16_t x = 32 + _tft->drawString(picked_city.name, 27, 5);
    _tft->drawString(picked_city.country, x, 5);
    _tft->unloadFont();
}

void
CurrentWeatherScreen::
init(Weather* weather){
    date
    ->timezone(weather->_timezone)
    ->init();
}