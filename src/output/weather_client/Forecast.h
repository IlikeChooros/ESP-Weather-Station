#ifndef FORECAST_H
#define FORECAST_H

#include <Arduino.h>

#include "Weather.h"

class Forecast
{
    public:
    Weather* forecasted_weather;
};

#endif