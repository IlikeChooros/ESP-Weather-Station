#include "WeatherClient.h"

City_info picked_city;

//--------------------------
// 1. http = new HTPP
// 2. cacheTime in millis
//--------------------------
WeatherClient::
WeatherClient(
    HTTPClient* http, 
    uint32_t cacheTime
)
{
    Serial.begin(115200);
    this->http = http;
    this->cacheTime = cacheTime;
}

std::vector<City_info>
WeatherClient::
get_all_cities_info(
    String city_name
){
    http->begin("http://api.openweathermap.org/geo/1.0/direct?q=" + city_name + "&limit=5&appid="+APPID);
    uint16_t http_code = http->GET();
    String payload = http->getString();

    std::vector<City_info> data;

    if (http_code == 200)
    {   
        DynamicJsonDocument filter(8200);
        for(uint8_t i = 0; i < 5; ++i){
            filter[i]["lat"] = true;
            filter[i]["lon"] = true;
            filter[i]["country"] = true;
            filter[i]["state"] = true;
            filter[i]["name"] = true;

            DynamicJsonDocument doc(8200);

            deserializeJson(doc, payload, DeserializationOption::Filter(filter));
            if (doc[i]["lat"].as<String>() == "null"){
                break;
            }

            data.push_back({
                doc[i]["lat"].as<double>(),
                doc[i]["lon"].as<double>(),
                doc[i]["name"].as<String>(),
                doc[i]["country"].as<String>(), 
                doc[i]["state"].as<String>()
            });

        }
    }
    http->end();
    return data;
}

City_info*
WeatherClient::
get_city_info(
    String city_name, 
    uint8_t idx
)
{
    City_info *data, get_data;
    auto get = get_all_cities_info(city_name);
    try{
        get_data = get.at(idx);
        data = new City_info(get_data);
    }
    catch(const std::out_of_range& err){
        data = 0;
    }
    return data;
}

bool
WeatherClient::
_init_(
    String city_name,
    uint8_t idx
)
{
    auto get = get_city_info(city_name, idx);
    bool isSuccessful = false;
    if (get){
        isSuccessful = true;
        picked_city = *get;
        delete get;
        _lat = picked_city.lat;
        _lon = picked_city.lon;
    }

    lastWeatherCheck = -2*cacheTime;
    lastForecastCheck = -2*cacheTime;
    return isSuccessful;
}

//-------------------------------------------------------------
// Must get already initcialized object
// 1. Weather weather = new Weather
// Returns boolean wheter obtaining weather info was successful
//--------------------------------------------------------------
bool 
WeatherClient::
current_weather
(Weather* weather)
{
    if (millis() - lastWeatherCheck < cacheTime){
        return false;
    }
    http->begin("http://api.openweathermap.org/data/2.5/weather?lat="+String(_lat)+"&lon="+String(_lon)+"&units=metric&lang=pl&appid="+APPID);
    
    int16_t http_code = http->GET();
    String payload = http->getString();

    bool isSuccessfull = http_code == 200;

    if (isSuccessfull)
    {
        DynamicJsonDocument filter(1024);
        filter["weather"][0]["main"] = true;
        filter["weather"][0]["icon"] = true;
        filter["main"]["temp"] = true;
        filter["main"]["feels_like"] = true;
        filter["main"]["pressure"] = true;
        filter["main"]["humidity"] = true;
        filter["wind"]["speed"] = true;
        filter["sys"]["sunrise"] = true;
        filter["sys"]["sunset"] = true;
        filter["dt"] = true;
        filter["timezone"] = true;

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, payload, DeserializationOption::Filter(filter));
        weather
            ->feels_like(doc["main"]["feels_like"].as<double>())
            ->main(doc["weather"][0]["main"].as<String>())
            ->icon(doc["weather"][0]["icon"].as<String>())
            ->pressure(doc["main"]["pressure"].as<int16_t>())
            ->humidity(doc["main"]["humidity"].as<uint8_t>())
            ->temp(doc["main"]["temp"].as<double>())
            ->wind_speed(doc["wind"]["speed"].as<double>())
            ->sunrise(doc["sys"]["sunrise"].as<uint32_t>())
            ->sunset(doc["sys"]["sunset"].as<uint32_t>())
            ->dt(doc["dt"].as<uint32_t>())
            ->timezone(doc["timezone"].as<int16_t>());
        doc.clear();
        filter.clear();
    }
    http->end();
    lastWeatherCheck = millis();

    return isSuccessfull;
}

//----------------------------------
// 1. Forecast must be init -> new Forecast
// 2. forecasted_weather must be init -> forecast->forecasted_weather = new ...
// 3. forecast->number_of_forecasts = NUMBER_OF_HOURS_TO_FORECAST;
// Returns boolean wheter obtaining weather info was successful
//----------------------------------
bool 
WeatherClient::
forecast_weather
(Forecast* forecast)
{
    if (millis() - lastForecastCheck < cacheTime){
        return false;
    }

    http->begin("http://api.openweathermap.org/data/2.5/forecast?lat="+String(_lat)+"&lon="+String(_lon)+"&units=metric&lang=pl&appid="+APPID);
    
    int16_t http_code = http->GET();
    String payload = http->getString();

    bool isSuccessfull = http_code == 200;

    if (isSuccessfull)
    {
        DynamicJsonDocument filter(FORECAST_CAPACITY);
        for (uint8_t i=0;i<NUMBER_OF_HOURS_TO_FORECAST;i++)
        {
            filter["list"][i]["weather"][0]["main"] = true;
            filter["list"][i]["weather"][0]["icon"] = true;
            filter["list"][i]["main"]["temp"] = true;
            filter["list"][i]["main"]["feels_like"] = true;
            filter["list"][i]["main"]["pressure"] = true;
            filter["list"][i]["main"]["humidity"] = true;
            filter["list"][i]["wind"]["speed"] = true;
            filter["list"][i]["dt"] = true;
            filter["list"][i]["pop"] = true;
            filter["city"]["timezone"] = true;

            DynamicJsonDocument doc(FORECAST_CAPACITY);
            DeserializationError err = deserializeJson(doc, payload, DeserializationOption::Filter(filter));

            forecast->forecasted_weather[i]
                ->feels_like(doc["list"][i]["main"]["feels_like"].as<double>())
                ->main(doc["list"][i]["weather"][0]["main"].as<String>())
                ->icon(doc["list"][i]["weather"][0]["icon"].as<String>())
                ->pressure(doc["list"][i]["main"]["pressure"].as<uint16_t>())
                ->humidity(doc["list"][i]["main"]["humidity"].as<uint8_t>())
                ->temp(doc["list"][i]["main"]["temp"].as<double>())
                ->wind_speed(doc["list"][i]["wind"]["speed"].as<double>())
                ->pop(doc["list"][i]["pop"].as<double>())
                ->dt(doc["list"][i]["dt"].as<uint32_t>())
                ->timezone(doc["city"]["timezone"].as<int16_t>());
        }
        filter.clear();
    }
    http->end();
    lastForecastCheck = millis();

    return isSuccessfull;
}