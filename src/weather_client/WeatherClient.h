#ifndef WEATHER_CLIENT_H
#define WEATHER_CLIENT_H

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#include "Weather.h"
#include "Forecast.h"

#define APPID "6a0b31b6c9c1f95d47860092dadc1f6c"
#define FORECAST_CAPACITY JSON_ARRAY_SIZE(NUMBER_OF_HOURS_TO_FORECAST) + 3*JSON_OBJECT_SIZE(1) + NUMBER_OF_HOURS_TO_FORECAST*((5)*JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(9) + JSON_ARRAY_SIZE(4)+JSON_OBJECT_SIZE(3))

struct 
City_info
{
    double lat;
    double lon;

    String name;
    String country;
    String state;
};

class WeatherClient
{
    double  _lat,
            _lon;

    HTTPClient* http;

    int32_t cacheTime;
    int64_t lastWeatherCheck;
    int64_t lastForecastCheck;

public:
    WeatherClient(
        HTTPClient *http, 
        uint32_t cacheTime
    );

    bool 
    _init_(String city_name);

    bool 
    current_weather(Weather *weather);

    bool 
    forecast_weather(Forecast *forecast);

    City_info*
    get_city_info(
        String city_name,
        uint8_t idx
    );

    void
    set_lat_lon(double lat, double lon)
    {this->_lat = lat; this->_lon = lon;}
};

#endif