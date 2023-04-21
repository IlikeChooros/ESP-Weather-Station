#line 1 "c:\\Users\\pawel\\arduino\\ESP-Weather-Station\\src\\data_structures\\get_day.h"
#pragma once

#include "Arduino.h"

class
HH_YY_date
{
    public:
    HH_YY_date(uint64_t unix)
    {
        uint64_t temp = unix % (86400); // 1 day in sec
        this->hour = temp/3600;
        this->min = (temp%3600) / 60;
    }
    int8_t hour;
    int8_t min;
};

inline uint8_t
get_day(
    uint64_t unix
)
{
    uint64_t date = unix/(3600*24);
    date = (date+3)%7;
    return (uint8_t)date;
}

inline String
get_date_string(
    uint64_t unix
)
{
    String week_days [7] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
    return week_days[get_day(unix)];
}

inline String
get_full_day_str(
    uint64_t unix
)
{
    String week_days [7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    return week_days[get_day(unix)];
}

inline HH_YY_date*
get_date_struct(
    uint64_t unix
)
{
    return new HH_YY_date(unix);
}