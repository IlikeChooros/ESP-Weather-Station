#include "ChartScreens.h"

void
ChartScreens::draw_bg()
{
    tft->fillScreen(bg_c);

    // Lines
    int16_t x_itr = 320 / 5,
            y_itr = 240 / 4;
    int16_t x = x_itr,
            y = y_itr;

    for (uint8_t i=1 ; i<5; i++)
    {
        tft->drawFastVLine(x, 0, 240, TFT_NAVY);

        if (i<4)
        {
            tft->drawFastHLine(0, y, 320, TFT_NAVY);
        }
        x+=x_itr;
        y+=y_itr;
    }
}

void
ChartScreens::draw_name(String str)
{
    for (uint8_t i=0; i<4; i++) {chart_names[i]->draw();}
    tft->setTextColor(TFT_WHITE);
    tft->setTextSize(1);
    tft->drawCentreString(str, 70, 0, 2);
}

void 
ChartScreens::draw_(
    std::vector<WeatherData>& data,
    int8_t* min_max,
    bool forceDraw,
    String str
)
{
    if(forceDraw)
    {
        draw_bg();
        draw_name(str);
    }
    chart_time->draw(forceDraw);

    if (data.size() == 1 || data.empty())
    {
        return;
    }

    int8_t max_value = -min_max[0] > min_max[1] ? -min_max[0] + 1 :  min_max[1] + 1;

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