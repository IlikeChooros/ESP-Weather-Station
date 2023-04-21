#line 1 "c:\\Users\\pawel\\arduino\\ESP-Weather-Station\\src\\output\\items\\WeatherDataCollector.cpp"
#include "WeatherDataCollector.h"

std::vector<WeatherData>&
WeatherDataCollector::get_data(ui8 idx){
    return _data[idx];
}

void 
WeatherDataCollector::
init(Weather* weather){
    this->current_day_ = get_day(weather->_dt);
}

void
WeatherDataCollector::check_min_max(
    int8_t data, 
    uint8_t idx
)
{
    if (_min_max[idx][0] > data){
        _min_max[idx][0] = data; // min
    }
    else if(_min_max[idx][1] < data){
        _min_max[idx][1] = data; // max
    }
}

void
WeatherDataCollector::collect(
    Weather* weather, 
    ui8 idx
)
{
    if (current_day_ != get_day(weather->_dt)){
        clear_mem(idx);
        _min_max[idx][0] = -1;
        _min_max[idx][1] = 1;
        current_day_ = get_day(weather->_dt);
    }
    _data[idx].push_back(WeatherData(weather->_dt, weather->_temp, weather->_feels_like, weather->_humidity, 100 * weather->_pop));

    check_min_max(_data[idx].at(_data[idx].size()-1).temp(), idx);
    check_min_max(_data[idx].at(_data[idx].size()-1).feels_like(), idx);
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
    for (ui8 i = starting_idx; i < ending_idx; i++){
        Weather* weather = forecast->forecasted_weather[i];
        _data[idx].push_back(WeatherData(weather->_dt, weather->_temp, weather->_feels_like, weather->_humidity, 100 * weather->_pop));
        check_min_max(_data[idx].at(count).temp(), idx);
        check_min_max(_data[idx].at(count).feels_like(), idx);
        count++;
    }
}

i8*
WeatherDataCollector::
get_min_max(ui8 idx){
    return this->_min_max[idx].begin().base();
}

void
WeatherDataCollector::
clear_mem(ui8 idx){
    _data[idx].clear();
}