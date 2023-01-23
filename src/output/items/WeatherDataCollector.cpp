#include "WeatherDataCollector.h"

Vector<WeatherData>& WeatherDataCollector::get_data(uint8_t idx)
{
    return data[idx];
}

//*********************************
// Will collect previous weather
// data
//*********************************
void WeatherDataCollector::collect(Weather* weather, uint8_t idx)
{
    if (millis() - lastWeatherCheck < MIN_5)
    {
        return;
    }
    WeatherData* temp = new WeatherData;
    temp
    ->dt(weather->_dt)
    ->humidity(weather->_humidity)
    ->temp((int8_t)weather->_temp)
    ->pop(100 * weather->_pop);
    data[idx].push_back(*temp);
    delete temp;
    lastWeatherCheck = millis();
}

//*********************************
// Will collect forecasted weather
// data for this day
//*********************************
void WeatherDataCollector::collect(Forecast* forecast, uint8_t idx)
{
    clear_mem(idx);

    uint8_t current_day = get_day(forecast->forecasted_weather[0]->_dt);
    uint8_t ending_idx=1;
    while(current_day == get_day(forecast->forecasted_weather[ending_idx]->_dt)){
        ending_idx++;
    }
    collect_data(forecast, idx, 0, ending_idx);
}

//*********************************
// Will collect forecasted data
// from the entire day
// day_offset = 0 -> next day
//*********************************
void WeatherDataCollector::collect_all(Forecast* forecast, uint8_t idx, uint8_t day_offset)
{
    clear_mem(idx);

    uint8_t current_day = get_day(forecast->forecasted_weather[0]->_dt);
    uint8_t starting_idx=1;
    while(current_day == get_day(forecast->forecasted_weather[starting_idx]->_dt)){
        starting_idx++;
    }
    starting_idx += 8*day_offset;
    collect_data(forecast, idx, starting_idx, starting_idx+8);
}

void WeatherDataCollector::collect_data(Forecast* forecast, uint8_t idx, uint8_t starting_idx, uint8_t ending_idx)
{
    for (uint8_t i=starting_idx; i<ending_idx;i++)
    {
        WeatherData* wdata = new WeatherData;
        wdata
        ->dt(forecast->forecasted_weather[i]->_dt)
        ->humidity(forecast->forecasted_weather[i]->_humidity)
        ->pop(forecast->forecasted_weather[i]->_pop)
        ->temp(forecast->forecasted_weather[i]->_temp);
        data[idx].push_back(*wdata);
        if (min_max[idx][0] > data[idx].at(i).temp())
        {
            min_max[idx][0] = data[idx].at(i).temp(); // min
        }
        else if(min_max[idx][1] < data[idx].at(i).temp())
        {
            min_max[idx][1] = data[idx].at(i).temp();
        }
        delete wdata;
    }
}

uint8_t* WeatherDataCollector::get_min_max(uint8_t idx)
{
    return this->min_max[idx];
}

void WeatherDataCollector::clear_mem(uint8_t idx)
{
    while (!data[idx].is_empty())
    {
        data[idx].pop_back();
    }
}