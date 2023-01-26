#pragma once

#include "date/DateFormat.h"
#include "../../data_structures/Vector.h"
#include "../../data_structures/Vector.cpp"
#include "../../weather_client/Weather.h"
#include "../../weather_client/Forecast.h"
#include "../../weather_client/WeatherData.h"
#include "../../data_structures/get_day.h"

#define MIN_5  300000
#define MIN_15 900000

using ui8 = uint8_t;
using i8 = int8_t;
using ui16 = uint16_t;

class WeatherDataCollector
{
    Vector<WeatherData> *data;

    i8** min_max;

    void print_all();
    void collect_data(
        Forecast* forecast,
        ui8 idx,
        ui8 starting_idx,
        ui8 ending_idx
    );
    public:
    WeatherDataCollector(ui8 number_of_data_to_collect) {
        data = new Vector<WeatherData> [number_of_data_to_collect];
        min_max = new i8* [number_of_data_to_collect];
        for (ui8 i=0; i<number_of_data_to_collect; i++)
        {
            min_max[i] = new i8 [2]{0,0};
        }
    }

    void
    collect(
        Weather* weather,
        uint8_t idx
    );

    void
    collect(
        Forecast* forecast,
        uint8_t idx
    );

    /**
     * @brief Get the min max out of collected data.
     *  This array shouldn't be deleted
     * 
     * @param idx 
     * 
     * @return int8_t* [0] -> min, [1]-> max
     */
    int8_t*
    get_min_max(
        uint8_t idx
    );

    /**
     * @brief Will collect forecasted data
     *  from the entire day
     * 
     * @param forecast 
     * @param idx 
     * @param starting_day for = 0, it is the next day, = 1, day after tomorrow, etc.
     */
    void
    collect_all(
        Forecast* forecast,
        uint8_t idx,
        uint8_t starting_day 
    );

    void clear_mem(uint8_t idx);
    Vector<WeatherData>& get_data(uint8_t idx);
};  
