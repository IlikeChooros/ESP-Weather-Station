#include "ChartScreenNextDays.h"

void ChartScreenNextDays::draw(Vector<WeatherData>& data, int8_t* min_max, bool forceDraw)
{
    if (data.size() == 1 || data.is_empty())
    {
        return;
    }

    if(forceDraw)
    {
        draw_bg();
        draw_name(data);
    }
    chart_time->draw(forceDraw);

    int8_t max_value = -min_max[0] > min_max[1] ? -min_max[0] + 3 :  min_max[1] + 3;

    charts[0]->set_min_max(-max_value, max_value);
    charts[1]->set_min_max(0, 100);
    charts[2]->set_min_max(0, 100);
    charts[3]->set_min_max(0, 100);
    charts[4]->set_min_max(-max_value, max_value);
    charts[5]->set_min_max(-max_value, max_value);

    for (uint8_t i=0; i<6; i++)
    {
        charts[i]->set_data(data);
        charts[i]->draw(true);
    }
}

void
ChartScreenNextDays::draw_name(Vector<WeatherData>& data)
{
    for (uint8_t i=0; i<4; i++) {chart_names[i]->draw();}
    if (data.is_empty()) {return;}

    tft->setTextColor(TFT_WHITE);
    tft->setTextSize(1);
    tft->drawCentreString(get_date_string(data.at(0).dt()), 60, 0, 2);
}