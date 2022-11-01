#ifndef WEATHER_CLIENT_H
#define WEATHER_CLIENT_H

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#include "Weather.h"
#include "Forecast.h"

#define APPID "6a0b31b6c9c1f95d47860092dadc1f6c"
#define NUMBER_OF_HOURS_TO_FORECAST 8
#define FORECAST_CAPACITY JSON_ARRAY_SIZE(NUMBER_OF_HOURS_TO_FORECAST) + 3*JSON_OBJECT_SIZE(1) + NUMBER_OF_HOURS_TO_FORECAST*((3)*JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(9) + JSON_ARRAY_SIZE(4)+JSON_OBJECT_SIZE(3))

class WeatherClient
{
    double  _lat,
            _lon;

    HTTPClient* http;
    public:
    WeatherClient(HTTPClient * http);
    uint16_t _init_(String city_name);
    Weather* current_weather();
    Forecast* forecast_weather();

    double lat();
    double lon();
};

#endif