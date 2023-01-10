#include "FewDaysForecastScreen.h"

uint8_t get_day(uint64_t unix)
{
    // Save the time in Human
    // readable format
    String ans = "";
 
    // Number of days in month
    // in normal year
    int daysOfMonth[] = { 31, 28, 31, 30, 31, 30,
                          31, 31, 30, 31, 30, 31 };
 
    long int currYear, daysTillNow, extraTime, extraDays,
        index, date, month, hours, minutes,
        flag = 0;
 
    // Calculate total days unix time T
    daysTillNow = unix / (24 * 60 * 60);
    extraTime = unix % (24 * 60 * 60);
    currYear = 1970;
 
    // Calculating current year
    while (true) {
        if (currYear % 400 == 0
            || (currYear % 4 == 0 && currYear % 100 != 0)) {
            if (daysTillNow < 366) {
                break;
            }
            daysTillNow -= 366;
        }
        else {
            if (daysTillNow < 365) {
                break;
            }
            daysTillNow -= 365;
        }
        currYear += 1;
    }
    // Updating extradays because it
    // will give days till previous day
    // and we have include current day
    extraDays = daysTillNow + 1;
 
    if (currYear % 400 == 0
        || (currYear % 4 == 0 && currYear % 100 != 0))
        flag = 1;
 
    // Calculating MONTH and DATE
    month = 0, index = 0;
    if (flag == 1) {
        while (true) {
 
            if (index == 1) {
                if (extraDays - 29 < 0)
                    break;
                month += 1;
                extraDays -= 29;
            }
            else {
                if (extraDays - daysOfMonth[index] < 0) {
                    break;
                }
                month += 1;
                extraDays -= daysOfMonth[index];
            }
            index += 1;
        }
    }
    else {
        while (true) {
 
            if (extraDays - daysOfMonth[index] < 0) {
                break;
            }
            month += 1;
            extraDays -= daysOfMonth[index];
            index += 1;
        }
    }
 
    // Current Month
    if (extraDays > 0) {
        month += 1;
        date = extraDays;
    }
    else {
        if (month == 2 && flag == 1)
            date = 29;
        else {
            date = daysOfMonth[month - 1];
        }
    }
    return date;
}

void FewDaysForecastScreen::draw(Forecast* forecast, bool forceDraw)
{
    uint8_t current_day = get_day(forecast->forecasted_weather[0]->_dt);
    uint8_t starting_itr = 1;
    float* result;
    for (; starting_itr<8; starting_itr++)
    {
        if (get_day(forecast->forecasted_weather[starting_itr]->_dt) == current_day + 1)
        {
            break;
        }
    }
    starting_itr += 4;
    for (uint8_t i=0; i<NUMBER_OF_DAYS_TO_FORECAST; i++)
    {
        result = getMinMaxTemp_pop(forecast, i*8 + starting_itr - 4);
        forecast->forecasted_weather[i*8 + starting_itr]->pop(result[POP]);
        forecast->forecasted_weather[i*8 + starting_itr]->temp((double)result[MAX_TEMP]);
        forecast->forecasted_weather[i*8 + starting_itr]->feels_like((double)result[MIN_TEMP]);

        if (result[POP]>0.49f)
        {
            forecast->forecasted_weather[i*8 + starting_itr]->icon("09d");
        }

        for (uint8_t j=0;j<NUMBER_OF_COLUMN_ITEMS;j++)
        {
            column_items[i].weather_items[j]->setWeather(forecast->forecasted_weather[i*8 + starting_itr]);
            column_items[i].weather_items[j]->draw(forceDraw);
        }
        delete [] result;
    }
}

float*  FewDaysForecastScreen::getMinMaxTemp_pop(Forecast* forecast, uint8_t start_idx)
{
    float* results = new float [3] {0,-100,100};

    for (int8_t a = 0; a<8;a++)
    {
        results[POP] += forecast->forecasted_weather[(uint16_t) a + start_idx]->_pop;

        if (forecast->forecasted_weather[(uint16_t) a + start_idx]->_temp > results[MAX_TEMP])
        {
            results[MAX_TEMP]= forecast->forecasted_weather[(uint16_t) a + start_idx]->_temp;
        }
        if (results[MIN_TEMP] > forecast->forecasted_weather[(uint16_t) a + start_idx]->_temp)
        {
            results[MIN_TEMP] = forecast->forecasted_weather[(uint16_t) a + start_idx]->_temp;
        }
    }
    results[POP] /= 8;
    return results;
}