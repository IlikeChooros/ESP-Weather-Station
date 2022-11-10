#include "WeatherClient.h"

WeatherClient::WeatherClient(HTTPClient* http)
{
    this->http = http;
}

bool WeatherClient::_init_(String city_name)
{
    http->begin("http://api.openweathermap.org/geo/1.0/direct?q=" + city_name + "&limit=1&appid="+APPID);

    int16_t http_code = http->GET();
    Serial.println("HTTP: "+String(http_code));
    bool isSuccesful = http_code == 200;
    if (isSuccesful)
    {
        String payload = http->getString();

        StaticJsonDocument<100> filter;
        filter[0]["lat"] = true;
        filter[0]["lon"] = true;

        StaticJsonDocument<100> doc;
        deserializeJson(doc, payload, DeserializationOption::Filter(filter));

        _lat = doc[0]["lat"].as<double>();
        _lon = doc[0]["lon"].as<double>();
    }

    http->end();
    return isSuccesful;
}


Weather* WeatherClient::current_weather()
{
    http->begin("https://api.openweathermap.org/data/2.5/weather?lat="+String(_lat)+"&lon="+String(_lon)+"&units=metric&lang=pl&appid="+APPID);
    int16_t http_code = http->GET();

    Weather* weather = new Weather;

    Serial.println("HTTP: "+String(http_code));

    if (http_code == 200)
    {
        String payload = http->getString();

        StaticJsonDocument<400> filter;
        filter["weather"][0]["main"] = true;
        filter["weather"][0]["icon"] = true;
        filter["main"]["temp"] = true;
        filter["main"]["feels_like"] = true;
        filter["main"]["pressure"] = true;
        filter["main"]["humidity"] = true;
        filter["wind"]["speed"] = true;
        filter["sys"]["sunrise"] = true;
        filter["sys"]["sunset"] = true;
        filter["dt"]=true;

        StaticJsonDocument<440> doc;
        deserializeJson(doc, payload, DeserializationOption::Filter(filter));

        weather
            ->feels_like(doc["main"]["feels_like"].as<double>())
            ->main(doc["weather"][0]["main"].as<String>())
            ->icon(doc["weather"][0]["icon"].as<String>())
            ->pressure(doc["main"]["pressure"].as<uint16_t>())
            ->humidity(doc["main"]["humidity"].as<uint8_t>())
            ->temp(doc["main"]["temp"].as<double>())
            ->wind_speed(doc["wind"]["speed"].as<double>())
            ->sunrise(doc["sys"]["sunrise"].as<uint32_t>())
            ->sunset(doc["sys"]["sunset"].as<uint32_t>())
            ->dt(doc["dt"].as<uint32_t>());
    }
    http->end();
    return weather;
}

Forecast* WeatherClient::forecast_weather()
{
    http->begin("https://api.openweathermap.org/data/2.5/forecast?lat="+String(_lat)+"&lon="+String(_lon)+"&units=metric&lang=pl&appid="+APPID);
    int16_t http_code = http->GET();

    Forecast* forecast;
    Weather** weather;

    if (http_code == 200)
    {
        forecast = new Forecast;
        weather = new Weather* [NUMBER_OF_HOURS_TO_FORECAST];
        forecast->number_of_forecasts = NUMBER_OF_HOURS_TO_FORECAST;
        String payload = http->getString();
        DynamicJsonDocument filter(FORECAST_CAPACITY);
        for (uint8_t i=0;i<NUMBER_OF_HOURS_TO_FORECAST;i++)
        {
            weather[i] = new Weather;
            filter["list"][i]["weather"][0]["main"] = true;
            filter["list"][i]["weather"][0]["icon"] = true;
            filter["list"][i]["main"]["temp"] = true;
            filter["list"][i]["main"]["feels_like"] = true;
            filter["list"][i]["main"]["pressure"] = true;
            filter["list"][i]["main"]["humidity"] = true;
            filter["list"][i]["wind"]["speed"] = true;
            filter["list"][i]["dt"] = true;
            filter["list"][i]["pop"] = true;

            DynamicJsonDocument doc(FORECAST_CAPACITY);
            DeserializationError err = deserializeJson(doc, payload, DeserializationOption::Filter(filter));

            if (err) {
            Serial.print(F("deserializeJson() failed with code "));
            Serial.println(err.f_str());
            }


            weather[i]
                ->feels_like(doc["list"][i]["main"]["feels_like"].as<double>())
                ->main(doc["list"][i]["weather"][0]["main"].as<String>())
                ->icon(doc["list"][i]["weather"][0]["icon"].as<String>())
                ->pressure(doc["list"][i]["main"]["pressure"].as<uint16_t>())
                ->humidity(doc["list"][i]["main"]["humidity"].as<uint8_t>())
                ->temp(doc["list"][i]["main"]["temp"].as<double>())
                ->wind_speed(doc["list"][i]["wind"]["speed"].as<double>())
                ->pop(doc["list"][i]["pop"].as<double>())
                ->dt(doc["list"][i]["dt"].as<uint32_t>());
        }
        forecast->forecasted_weather = weather;
    }
    http->end();
    return forecast;
}

Weather* WeatherClient::update(Weather* weather)
{
    Weather* w;
    if(weather)
    {
        delete weather;
        w = current_weather();
    }
    return w;
}

Forecast* WeatherClient::update(Forecast* forecast)
{
    if(forecast)
    {
        Weather* w;
        for (uint8_t i=0;i<forecast->number_of_forecasts;i++)
        {
            Serial.println(String(i)+" w = f->...");
            w = forecast->forecasted_weather[i];
            if(w)
            {
                Serial.println(String(i)+" (w == true)");
                delete w;
            }
        }
        Serial.println("deleting f...");
        delete forecast;
    }
    Forecast* f = forecast_weather();
    Serial.println("END");
    return f;

}