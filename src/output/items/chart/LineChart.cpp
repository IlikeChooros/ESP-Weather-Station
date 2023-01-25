#include "LineChart.h"

void
LineCharTemp::draw(bool forceDraw)
{
    HH_YY_date* dt = get_date_struct(data.at(0).dt());
    i16 prev_x = dt->hour * HOURS_PIXELS + dt->min * MINUTES_5_PIXELS + starting_x_,
    prev_y = get_y(data.at(0).temp()), x, y;
    delete dt;

    uint64_t lastCheck = data.at(0).dt();

    for(ui16 i=1; i<data.size(); i++)
    {
        x = prev_x + pixel_offset;
        y = get_y(data.at(i).temp());

        tft->drawLine(prev_x, prev_y, x,y, color);

        prev_x = x;
        prev_y = y;

        if (data.at(i).dt() - lastCheck < 10800) // 3 hours
        {
            continue;
        }

        tft->setCursor(x, y+3);
        tft->setTextColor(color);
        tft->setTextSize(1);
        tft->setTextFont(1);
        tft->print(data.at(i).temp());

        lastCheck = data.at(i).dt();
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
    pixel_offset = data.at(1).dt() - data.at(0).dt() > 3600 ? 3*HOURS_PIXELS : MINUTES_5_PIXELS; 
}

ui16
LineCharTemp::get_y(int16_t data)
{
    return data > 0 ? (MIDDLE_Y - data*scale_positive) : (MIDDLE_Y - data*scale_negative);
}


//Feels like
void
LineChartFeelsLike::draw(bool forceDraw)
{
    HH_YY_date* dt = get_date_struct(data.at(0).dt());
    i16 prev_x = dt->hour * HOURS_PIXELS + dt->min * MINUTES_5_PIXELS + starting_x_,
    prev_y = get_y(data.at(0).feels_like()), x, y;
    delete dt;

    uint64_t lastCheck = data.at(0).dt();

    for(ui16 i=1; i<data.size(); i++)
    {
        x = prev_x + pixel_offset;
        y = get_y(data.at(i).feels_like());

        tft->drawLine(prev_x, prev_y, x,y, color);

        prev_x = x;
        prev_y = y;

        if (data.at(i).dt() - lastCheck < 10800) // 3 hours
        {
            continue;
        }

        tft->setCursor(x, y-10);
        tft->setTextColor(color);
        tft->setTextSize(1);
        tft->setTextFont(1);
        tft->print(data.at(i).feels_like());

        lastCheck = data.at(i).dt();
    }
}

void
LineChartFeelsLike::set_data(Vector<WeatherData>& data)
{
    this->data = data;
    if (data.size() <= 1)
    {
        return;
    }
    pixel_offset = data.at(1).dt() - data.at(0).dt() > 3600 ? 3*HOURS_PIXELS : MINUTES_5_PIXELS; 
}

ui16
LineChartFeelsLike::get_y(int16_t data)
{
    return data > 0 ? (MIDDLE_Y - data*scale_positive) : (MIDDLE_Y - data*scale_negative);
}


// Pop
void
LineChartPop::draw(bool forceDraw)
{
    HH_YY_date* dt = get_date_struct(data.at(0).dt());
    i16 prev_x = dt->hour * HOURS_PIXELS + dt->min * MINUTES_5_PIXELS + starting_x_,
    prev_y = get_y(data.at(0).pop()), x, y;
    delete dt;

    uint64_t lastCheck = data.at(0).dt();

    for(ui16 i=1; i<data.size(); i++)
    {
        x = prev_x + pixel_offset;
        y = get_y(data.at(i).pop());

        tft->drawLine(prev_x, prev_y, x,y, color);

        prev_x = x;
        prev_y = y;

        if (data.at(i).dt() - lastCheck < 10800) // 3 hours
        {
            continue;
        }

        tft->setTextColor(color);
        tft->setTextSize(1);
        tft->drawCentreString(String(data.at(i).pop()), x-1, y-10, 1);

        lastCheck = data.at(i).dt();
    }
}

void
LineChartPop::set_data(Vector<WeatherData>& data)
{
    this->data = data;
    if (data.size() <= 1)
    {
        return;
    }
    pixel_offset = data.at(1).dt() - data.at(0).dt() > 3600 ? 3*HOURS_PIXELS : MINUTES_5_PIXELS; 
}

ui16
LineChartPop::get_y(int16_t data)
{
    return MIDDLE_Y - data*scale;
}


// Humidity
void
LineChartHumidity::draw(bool forceDraw)
{
    HH_YY_date* dt = get_date_struct(data.at(0).dt());
    i16 prev_x = dt->hour * HOURS_PIXELS + dt->min * MINUTES_5_PIXELS + starting_x_,
    prev_y = get_y(data.at(0).humidity()), x, y;
    delete dt;

    uint64_t lastCheck = data.at(0).dt();

    for(ui16 i=1; i<data.size(); i++)
    {
        x = prev_x + pixel_offset;
        y = get_y(data.at(i).humidity());

        tft->drawLine(prev_x, prev_y, x,y, color);

        prev_x = x;
        prev_y = y;

        if (data.at(i).dt() - lastCheck < 10800) // 3 hours
        {
            continue;
        }

        tft->setCursor(x, y+3);
        tft->setTextColor(color);
        tft->setTextSize(1);
        tft->setTextFont(1);
        tft->print(data.at(i).humidity());

        lastCheck = data.at(i).dt();
    }
}

void
LineChartHumidity::set_data(Vector<WeatherData>& data)
{
    this->data = data;
    if (data.size() <= 1)
    {
        return;
    }
    pixel_offset = data.at(1).dt() - data.at(0).dt() > 3600 ? 3*HOURS_PIXELS : MINUTES_5_PIXELS; 
}

ui16
LineChartHumidity::get_y(int16_t data)
{
    return MIDDLE_Y - data*scale;
}

