#ifndef CURRENT_WEATHER_SCREEN_H
#define CURRENT_WEATHER_SCREEN_H

#include "MainScreen.h"
#include "../../items/WeatherItem.h"
#include "../../items/TextItem.h"
#include "../../items/date/DateItem.h"
#include "../../items/wifi/WiFiItem.h"
#include "../../items/weather/SunriseItem.h"
#include "../../items/weather/SunsetItem.h"
#include "../../icons/WeatherIcon.h"
#include "../../icons/WindIcon.h"
#include "../../../data_structures/Hsv_to_rgb.h"
#include "../../../weather_client/WeatherClient.h"


#define NUMBER_OF_WEATHER_ITEMS 8
#define OFFSET 70


class CurrentWeatherScreen: public MainScreen
{
    WeatherItem** weather_items;
    WiFiItem* wifi;
    DateItem* date;

    void
    draw_city_info(bool);

    public:
    CurrentWeatherScreen(TFT_eSPI * tft, uint16_t bg_c): MainScreen(tft,bg_c){
        
        weather_items = new WeatherItem*[NUMBER_OF_WEATHER_ITEMS] {
            new WeatherIcon(this->_tft, 190,30+OFFSET, 125, bg_c),
            new WindIcon(this->_tft, 80, 105+OFFSET, 20, bg_c),
            new TextTemp(this->_tft, 30, 30+OFFSET, 4, 2, TFT_WHITE, "%d `C" , bg_c),
            new TextFeelsLike(this->_tft, 35, 80+OFFSET, 2, 1, TFT_WHITE,"Feels like: %d `C", bg_c),
            new TextWind(this->_tft, 105, 105+OFFSET, 2, 1, 0x77F2, "%d km/h", bg_c),
            new TextPressure(this->_tft, 105, 135+OFFSET, 2, 1, 0xB41F, "%d hPa", bg_c),
            new SunriseItem(_tft, 15, 100 + OFFSET, 25, bg_c),
            new SunsetItem(_tft, 15, 130 + OFFSET, 25, bg_c)
        }; 

        wifi = new WiFiItem(this->_tft, 5, 2, 15, bg_c);
        date = new DateItem(this->_tft, 160, 20, 50, bg_c);
      }
    void 
    draw(
        Weather* weather, 
        bool forceDraw
    );

    void 
    draw(
        Forecast* forecast,
        bool forceDraw
    );

    /// @brief Refreshes time item
    /// @param forceUpdate 
    void 
    refresh(bool forceUpdate);

    void 
    init(Weather* weather);
};


#endif