#pragma once

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

    TFT_eSprite location;

    void
    draw_city_info(bool);

    public:
    CurrentWeatherScreen(
        TFT_eSPI * tft, 
        uint16_t bg_c
    );

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
