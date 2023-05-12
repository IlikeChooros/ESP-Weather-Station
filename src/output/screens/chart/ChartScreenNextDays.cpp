#include "ChartScreenNextDays.h"

ChartScreenNextDays::
ChartScreenNextDays(
    TFT_eSPI *tft,
    uint16_t bg_c
): ChartScreens(tft, bg_c) {}

void ChartScreenNextDays::draw(std::vector<WeatherData>& data, int8_t* min_max, bool forceDraw)
{
    draw_(data, min_max, forceDraw, get_full_day_str(data.at(0).dt()));
}