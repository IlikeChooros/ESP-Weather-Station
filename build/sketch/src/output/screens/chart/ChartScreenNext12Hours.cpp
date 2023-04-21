#line 1 "c:\\Users\\pawel\\arduino\\ESP-Weather-Station\\src\\output\\screens\\chart\\ChartScreenNext12Hours.cpp"
#include "ChartScreenNext12Hours.h"

void ChartScreenNext12Hours::draw(std::vector<WeatherData>& data, int8_t* min_max, bool forceDraw)
{
    draw_(data, min_max, forceDraw, "Rest of the day");
}