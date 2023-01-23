#pragma once

#include "Arduino.h"

struct HH_YY_date{
    int8_t hour;
    int8_t min;
};

inline uint8_t get_day(uint64_t unix)
{
    uint64_t date = unix/(3600*24);
    date = (date+3)%7;
    return (uint8_t)date;
}

inline HH_YY_date* get_date_struct(uint64_t unix)
{
    return new HH_YY_date {unix%3600, unix%60};
}