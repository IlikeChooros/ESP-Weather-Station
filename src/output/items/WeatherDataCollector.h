#pragma once

#include "DateFormat.h"
#include "../../data_structures/Vector.h"
#include "../../data_structures/Vector.cpp"
#include "../../weather_client/Weather.h"
#include "../../weather_client/Forecast.h"
#include "../../weather_client/WeatherData.h"
#include "../../data_structures/get_day.h"

#define MIN_5  300000
#define MIN_15 900000

class WeatherDataCollector
{
    Vector<WeatherData> *data;
    int64_t lastWeatherCheck;

    uint8_t** min_max;

    void print_all();
    void collect_data( Forecast* forecast, uint8_t idx, uint8_t starting_idx, uint8_t ending_idx);
    public:
    WeatherDataCollector(uint8_t number_of_data_to_collect):
    lastWeatherCheck(-MIN_5) {
        data = new Vector<WeatherData> [number_of_data_to_collect];
        min_max = new uint8_t* [number_of_data_to_collect];
        for (uint8_t i=0; i<number_of_data_to_collect; i++)
        {
            min_max = new uint8_t [2]{30,-10};
        }
    }
    void collect(Weather* weather, uint8_t idx);
    void collect(Forecast* forecast, uint8_t idx);
    int8_t* get_min_max(uint8_t idx);
    void collect_all(Forecast* forecast, uint8_t idx, uint8_t starting_day);
    void clear_mem(uint8_t idx);
    Vector<WeatherData>& get_data(uint8_t idx);
};  
