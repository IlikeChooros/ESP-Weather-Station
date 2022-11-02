#ifndef FORECAST_H
#define FORECAST_H

#include <Arduino.h>

#include "Weather.h"

class Forecast
{
    public:
    Weather* forecasted_weather;
    uint8_t number_of_forecasts;
};

#endif