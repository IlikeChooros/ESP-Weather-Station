#ifndef FORECAST_H
#define FORECAST_H

#include <Arduino.h>

#include "Weather.h"

#define NUMBER_OF_HOURS_TO_FORECAST 4

class Forecast
{
    public:
    Weather** forecasted_weather;
    uint8_t number_of_forecasts;
};

#endif