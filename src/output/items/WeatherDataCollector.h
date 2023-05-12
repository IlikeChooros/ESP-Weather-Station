#pragma once

#include <vector>

#include "date/DateFormat.h"


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
    std::vector<std::vector<WeatherData>> _data;
    std::vector<std::vector<i8>> _min_max;
    ui8 current_day_;

    void
    check_min_max(int8_t data, uint8_t idx);

    void
    collect_data(
        Forecast* forecast,
        ui8 idx,
        ui8 starting_idx,
        ui8 ending_idx
    );

    public:
    WeatherDataCollector(ui8 number_of_data_to_collect);

    /**
     * @brief Initializes the object, setting starting day
     * 
     */
    void 
    init(
        Weather* weather
    );

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

    void 
    clear_mem(uint8_t idx);

    std::vector<WeatherData>& 
    get_data(uint8_t idx);
};  
