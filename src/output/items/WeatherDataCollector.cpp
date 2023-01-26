#include "WeatherDataCollector.h"

Vector<WeatherData>&
WeatherDataCollector::get_data(ui8 idx)
{
    return data[idx];
}

void
WeatherDataCollector::collect(Weather* weather, ui8 idx)
{
    WeatherData* wdata(static_cast<WeatherData*>(::operator new(sizeof(WeatherData))));
    wdata
    ->dt(weather->_dt)
    ->humidity(weather->_humidity)
    ->temp(weather->_temp)
    ->feels_like(weather->_feels_like)
    ->pop(100 * weather->_pop);
    data[idx].push_back(*wdata);

    if (min_max[idx][0] > data[idx].at(data[idx].size()-1).temp())
    {
        min_max[idx][0] = data[idx].at(data[idx].size()-1).temp(); // min
    }
    else if(min_max[idx][1] < data[idx].at(data[idx].size()-1).temp())
    {
        min_max[idx][1] = data[idx].at(data[idx].size()-1).temp(); // max
    }

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

    Serial.println("*****************************");
    Serial.println("PUSH_BACK COLLECT: ");
    for (ui16 i = 0; i<data[idx].size(); i++)
    {
        HH_YY_date* dt = new HH_YY_date (data[idx].at(i).dt());
        Serial.println("----------------------");
        Serial.println(String(i)+": ");
        Serial.println(get_date_string(data[idx].at(i).dt()) + String(dt->hour) + " : " + String(dt->min));
        Serial.println(String(data[idx].at(i).feels_like())+" C FEELS");
        Serial.println(String(data[idx].at(i).temp())+" C TEMP");
        Serial.println(String(data[idx].at(i).pop())+" % POP");
        Serial.println(String(data[idx].at(i).humidity())+" % HUM");
        delete dt;
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