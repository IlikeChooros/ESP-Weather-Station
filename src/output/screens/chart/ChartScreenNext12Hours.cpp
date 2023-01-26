#include "ChartScreenNext12Hours.h"

void ChartScreenNext12Hours::draw(Vector<WeatherData>& data, int8_t* min_max, bool forceDraw)
{
    draw_(data, min_max, forceDraw, "Rest of the day");
}