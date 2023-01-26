#include "WeatherDataCollector.h"

Vector<WeatherData>&
WeatherDataCollector::get_data(ui8 idx)
{
    return data[idx];
}

void 
WeatherDataCollector::init(
    Weather* weather
)
{
    this->current_day_ = get_day(weather->_dt);
}

void
WeatherDataCollector::check_min_max(
    int8_t data, 
    uint8_t idx
)
{
    if (min_max[idx][0] > data)
    {
        min_max[idx][0] = data; // min
    }
    else if(min_max[idx][1] < data)
    {
        min_max[idx][1] = data; // max
    }
}

void
WeatherDataCollector::collect(
    Weather* weather, 
    ui8 idx
)
{
    if (current_day_ != get_day(weather->_dt))
    {
        clear_mem(idx);
        min_max[idx][0] = -1;
        min_max[idx][1] = 1;
        current_day_ = get_day(weather->_dt);
    }
    WeatherData* wdata(static_cast<WeatherData*>(::operator new(sizeof(WeatherData))));
    wdata
    ->dt(weather->_dt)
    ->humidity(weather->_humidity)
    ->temp(weather->_temp)
    ->feels_like(weather->_feels_like)
    ->pop(100 * weather->_pop);
    data[idx].push_back(*wdata);

    check_min_max(data[idx].at(data[idx].size()-1).temp(), idx);
    check_min_max(data[idx].at(data[idx].size()-1).feels_like(), idx);

    delete wdata;
}


void
WeatherDataCollector::collect(
    Forecast* forecast,
    ui8 idx
)
{
    clear_mem(idx);

    ui8 current_day = get_day(forecast->forecasted_weather[0]->_dt);

    ui8 ending_idx=1;
    while(current_day == get_day(forecast->forecasted_weather[ending_idx]->_dt)) {ending_idx++;}

    collect_data(forecast, idx, 0, ending_idx+1);
}

void
WeatherDataCollector::collect_all(
    Forecast* forecast,
    ui8 idx,
    ui8 day_offset
)
{
    clear_mem(idx);

    ui8 current_day = get_day(forecast->forecasted_weather[0]->_dt);
    ui8 starting_idx=1;
    while(current_day == get_day(forecast->forecasted_weather[starting_idx]->_dt)) {starting_idx++;}
    starting_idx += 8*day_offset;
    collect_data(forecast, idx, starting_idx, starting_idx+9);
}

void
WeatherDataCollector::collect_data(
    Forecast* forecast,
    ui8 idx,
    ui8 starting_idx,
    ui8 ending_idx
)
{
    ui8 count = 0;

    for (ui8 i=starting_idx; i<ending_idx;i++)
    {
        WeatherData* wdata(static_cast<WeatherData*>(::operator new(sizeof(WeatherData))));
        wdata
        ->dt(forecast->forecasted_weather[i]->_dt)
        ->humidity(forecast->forecasted_weather[i]->_humidity)
        ->pop(100*forecast->forecasted_weather[i]->_pop)
        ->feels_like(forecast->forecasted_weather[i]->_feels_like)
        ->temp(forecast->forecasted_weather[i]->_temp);

        data[idx].push_back(*wdata);
        check_min_max(data[idx].at(count).temp(), idx);
        check_min_max(data[idx].at(count).feels_like(), idx);
        count++;
        delete wdata;
    }
}

i8*
WeatherDataCollector::get_min_max(
    ui8 idx
)
{
    return this->min_max[idx];
}

void
WeatherDataCollector::clear_mem(
    ui8 idx
)
{
    while (!data[idx].is_empty())
    {
        data[idx].pop_back();
    }
}