#include "LineChart.h"

void LineCharTemp::draw(bool forceDraw)
{
    HH_YY_date* dt = get_date_struct(data.at(0).dt());
    Serial.println("H: "+String(dt->hour)+ " M: "+String(dt->min));
    starting_x = dt->hour * HOURS_PIXELS + dt->min * MINUTES_5_PIXELS + STARTING_X;

    Serial.println("ST_X "+String(starting_x));
    delete dt;
    int16_t prev_x = starting_x, prev_y = MIDDLE_Y - get_y(data.at(0).temp()), x, y;
    for(uint8_t i=1; i<data.size(); i++)
    {
        Serial.println(String(i)+". "+String(data.at(i).temp()));
        x = prev_x + pixel_offset;
        y = MIDDLE_Y - get_y(data.at(i).temp());

        tft->drawLine(prev_x, prev_y, x,y, color);

        if (data.at(i-1).dt() - data.at(i).dt() > 3600)
        {
            tft->setCursor(prev_x, prev_y);
            tft->setTextColor(color);
            tft->setTextSize(1);
            tft->setTextFont(1);
            tft->print(data.at(i).temp());
        }

        prev_x = x;
        prev_y = y;
    }
}

void LineCharTemp::set_data(Vector<WeatherData>& data)
{
    this->data = data;

    if (data.size() <= 1)
    {
        return;
    }

    pixel_offset = data.at(1).dt() - data.at(0).dt() > 3600 ? 3*HOURS_PIXELS : MINUTES_5_PIXELS; 
}

uint16_t LineCharTemp::get_y(int16_t data)
{
    if (data > 0)
    {
        return data*scale_positive;
    }
    return data*scale_negative;
}