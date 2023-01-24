#include "ChartScreen.h"

void ChartScreen::draw(Vector<WeatherData>& data, int8_t* min_max, bool forceDraw)
{
    if (data.size() == 1 || data.is_empty())
    {
        return;
    }

    if(forceDraw)
    {
        draw_bg();
    }

    int8_t max_value = -min_max[0] > min_max[1] ? -min_max[0] + 2 :  min_max[1] + 2;
    Serial.println("MAX: "+String(max_value) + "  "+String(-max_value));
    for (uint8_t i=0; i<2; i++)
    {
        charts[i]->set_min_max(-max_value, max_value);
        charts[i]->set_data(data);
        charts[i]->draw(true);
    }
}

void
ChartScreen::draw_bg()
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