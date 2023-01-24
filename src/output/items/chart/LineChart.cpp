#include "LineChart.h"

void
LineCharTemp::draw(bool forceDraw)
{
    HH_YY_date* dt = get_date_struct(data.at(0).dt());
    starting_x = dt->hour * HOURS_PIXELS + dt->min * MINUTES_5_PIXELS + STARTING_X;
    delete dt;
    i16 prev_x = starting_x, prev_y = get_y(data.at(0).temp()), x, y;
    for(ui8 i=1; i<data.size(); i++)
    {
        x = prev_x + pixel_offset;
        y = get_y(data.at(i).temp());

        tft->drawLine(prev_x, prev_y, x,y, color);

        if (data.at(i-1).dt() - data.at(i).dt() > 3600)
        {
            tft->setCursor(x, y);
            tft->setTextColor(color);
            tft->setTextSize(1);
            tft->setTextFont(1);
            tft->print(data.at(i).temp());
        }

        prev_x = x;
        prev_y = y;
    }
}

void
LineCharTemp::set_data(Vector<WeatherData>& data)
{
    this->data = data;
    if (data.size() <= 1)
    {
        return;
    }
    pixel_offset = data.at(1).dt() - data.at(0).dt() > 3600 ? HOURS_PIXELS : MINUTES_5_PIXELS; 
}

ui16
LineCharTemp::get_y(int16_t data)
{
    return data > 0 ? (MIDDLE_Y - data*scale_positive) : (MIDDLE_Y - data*scale_negative);
}