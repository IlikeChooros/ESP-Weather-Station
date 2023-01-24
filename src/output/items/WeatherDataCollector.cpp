#include "WeatherDataCollector.h"

Vector<WeatherData>& WeatherDataCollector::get_data(ui8 idx)
{
    return data[idx];
}

void WeatherDataCollector::collect(Weather* weather, ui8 idx)
{
    if (millis() - lastWeatherCheck < MIN_5)
    {
        return;
    }
    WeatherData* temp = new WeatherData;
    temp
    ->dt(weather->_dt)
    ->humidity(weather->_humidity)
    ->temp((i8)weather->_temp)
    ->pop(100 * weather->_pop);
    data[idx].push_back(*temp);
    delete temp;
    lastWeatherCheck = millis();
}


void WeatherDataCollector::collect(
    Forecast* forecast,
    ui8 idx
)
{
    clear_mem(idx);

    ui8 current_day = get_day(forecast->forecasted_weather[0]->_dt);
    ui8 ending_idx=1;
    while(current_day == get_day(forecast->forecasted_weather[ending_idx]->_dt)) {ending_idx++;}
    collect_data(forecast, idx, 0, ending_idx);
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
    collect_data(forecast, idx, starting_idx, starting_idx+8);
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
        ->pop(forecast->forecasted_weather[i]->_pop)
        ->temp(forecast->forecasted_weather[i]->_temp);

        data[idx].push_back(*wdata);
        if (min_max[idx][0] > data[idx].at(count).temp())
        {
            min_max[idx][0] = data[idx].at(count).temp(); // min
        }
        else if(min_max[idx][1] < data[idx].at(count).temp())
        {
            min_max[idx][1] = data[idx].at(count).temp(); // max
        }
        count++;
        delete wdata;
    }
}

i8*
WeatherDataCollector::get_min_max(ui8 idx)
{
    return this->min_max[idx];
}

void
WeatherDataCollector::clear_mem(ui8 idx)
{
    while (!data[idx].is_empty())
    {
        data[idx].pop_back();
    }
}