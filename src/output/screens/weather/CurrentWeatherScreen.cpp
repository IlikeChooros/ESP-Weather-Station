#include "CurrentWeatherScreen.h"

extern City_info picked_city;

CurrentWeatherScreen::
CurrentWeatherScreen(TFT_eSPI * tft, uint16_t bg_c): MainScreen(tft,bg_c), location(tft){
    
    weather_items = new WeatherItem*[NUMBER_OF_WEATHER_ITEMS] {
        new WeatherIcon(this->_tft, 190,30+OFFSET, 125, bg_c),
        new WindIcon(this->_tft, 85, 100+OFFSET, 20, bg_c),
        new TextTemp(this->_tft, 95, 35+OFFSET, TEMP_FONT, TFT_WHITE, "%d °C" , bg_c),
        new TextFeelsLike(this->_tft, 80, 80+OFFSET, WEATHER_FONT, TFT_WHITE,"Feels like: %d °C", bg_c),
        new TextWind(this->_tft, 110, 105+OFFSET, WEATHER_FONT, 0x77F2, "%d km/h", bg_c),
        new TextPressure(this->_tft, 110, 135+OFFSET, WEATHER_FONT, 0xB41F, "%d hPa", bg_c),
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
    location.pushSprite(30, 5);
}

void
CurrentWeatherScreen::
init(Weather* weather){
    date
    ->timezone(weather->_timezone)
    ->init();

    location.setTextColor(TFT_LIGHTGREY, bg_c);
    location.loadFont(EXTENDED_LATIN_SMALL);
    String to_print = picked_city.name + " " + picked_city.country;
    uint16_t width = location.textWidth(to_print);
    location.createSprite(width, location.fontHeight());
    location.fillSprite(bg_c);
    location.drawString(to_print, 0, 0);
    location.unloadFont();
}