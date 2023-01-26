#include "ChartScreenToday.h"


void ChartScreenToday::draw(Vector<WeatherData>& data, int8_t* min_max, bool forceDraw)
{
    draw_(data, min_max, forceDraw, "Today");
}