#ifndef WEATHER_CLIENT_H
#define WEATHER_CLIENT_H

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

class WeatherClient
{
    HTTPClient* http;
    public:
    WeatherClient(String city_name, HTTPClient * http);
    StaticJsonDocument<200> get_current_weather();


};

#endif