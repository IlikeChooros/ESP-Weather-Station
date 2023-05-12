#include "LineChart.h"

LineCharTemp::
LineCharTemp(
    TFT_eSPI *tft,
    uint16_t color,
    uint16_t starting_x
): ChartItem(tft, color, starting_x) {}

void LineCharTemp::
set_min_max(int16_t min,int16_t max){
    min_value = min;
    max_value = max;
    scale_positive = (float)((MAX_POSITIVE)/max_value);
    scale_negative = min_value < 0 ? -(float)((MAX_NEGATIVE)/min_value) :(float)((MAX_NEGATIVE)/min_value);
}

LineChartFeelsLike::
LineChartFeelsLike(
    TFT_eSPI *tft,
    uint16_t color,
    uint16_t starting_x
): ChartItem(tft, color, starting_x) {}

void LineChartFeelsLike::
set_min_max(
    int16_t min,
    int16_t max
)
{
    min_value = min;
    max_value = max;
    scale_positive = (float)((MAX_POSITIVE)/max_value);
    scale_negative = min_value < 0 ? -(float)((MAX_NEGATIVE)/min_value) :(float)((MAX_NEGATIVE)/min_value);
}

LineChartHumidity::
LineChartHumidity(
    TFT_eSPI *tft,
    uint16_t color,
    uint16_t starting_x
): ChartItem(tft, color, starting_x) {}

void LineChartHumidity::
set_min_max(
    int16_t min,
    int16_t max
)
{
    min_value = min;
    max_value = max;
    scale = (float)((MAX_POSITIVE)/max_value);
}

LineChartPop::
LineChartPop(
    TFT_eSPI *tft,
    uint16_t color,
    uint16_t starting_x
): ChartItem(tft, color, starting_x) {}

void LineChartPop::
set_min_max(
    int16_t min,
    int16_t max
)
{
    min_value = min;
    max_value = max;
    scale = (float)((MAX_POSITIVE)/max_value);
}

ui16 
set_data_(std::vector<WeatherData> &data)
{
    if (data.size() <= 1){
        return 0;
    }
    return data.at(1).dt() - data.at(0).dt() > 3600 ? 3*HOURS_PIXELS : MINUTES_5_PIXELS; 
}

ui16
get_y_pos(float data, float sc){
    return MIDDLE_Y - data*sc;
}

ui16
get_y_n_p(
    float data,
    float sc_p,
    float sc_n
)
{
    return data > 0 ? MIDDLE_Y - data*sc_p : MIDDLE_Y - data*sc_n;
}

ui16
get_y_pos_by_idx(
    uint8_t idx, 
    float scale_pos, 
    float scale_neg,
    ui16 i,
    std::vector<WeatherData> &data
)
{
    switch (idx)
    {
        case POP_IDX:
            return get_y_pos(data.at(i).pop(), scale_pos);
        case HUM_IDX:
            return get_y_pos(data.at(i).humidity(), scale_pos);
        case TEMP_IDX:
            return get_y_n_p(data.at(i).temp(), scale_pos, scale_neg);
        case FEELS_IDX:
            return get_y_n_p(data.at(i).feels_like(), scale_pos, scale_neg);
    }
}

void
draw_number_chart(
    TFT_eSPI* tft,
    ui16 idx,
    ui16 x,
    ui16 y,
    ui16 color,
    std::vector<WeatherData> &data,
    ui16 i
)
{
    switch(idx)
    {
        case TEMP_IDX:
            tft->setCursor(x, y+3);
            tft->setTextColor(color);
            tft->setTextSize(1);
            tft->setTextFont(1);
            tft->print(data.at(i).temp());
            return;
        case FEELS_IDX:
            tft->setCursor(x, y-10);
            tft->setTextColor(color);
            tft->setTextSize(1);
            tft->setTextFont(1);
            tft->print(data.at(i).feels_like());
            return;
        case HUM_IDX:
            tft->setCursor(x, y+3);
            tft->setTextColor(color);
            tft->setTextSize(1);
            tft->setTextFont(1);
            tft->print(data.at(i).humidity());
            return;
        case POP_IDX:
            tft->setTextColor(color);
            tft->setTextSize(1);
            tft->drawCentreString(String(data.at(i).pop()), x-1, y-10, 1);
            return;
    }
}

void
draw_line_chart(
    TFT_eSPI* tft,
    uint8_t idx, 
    std::vector<WeatherData>& data, 
    ui16 starting_x_, 
    ui16 pixel_offset,
    ui16 color,
    float scale_pos, 
    float scale_neg
)
{
    HH_YY_date* dt = get_date_struct(data.at(0).dt());
    i16 prev_x = dt->hour * HOURS_PIXELS +  dt->min / 5 * MINUTES_5_PIXELS + starting_x_,
    prev_y = get_y_pos_by_idx(idx, scale_pos, scale_neg, 0, data), x, y;
    delete dt;

    draw_number_chart(tft, idx, prev_x, prev_y, color, data, 0);

    uint64_t lastCheck = data.at(0).dt();

    for(ui16 i=1; i<data.size(); i++)
    {
        x = prev_x + pixel_offset;
        y = get_y_pos_by_idx(idx, scale_pos, scale_neg, i, data);

        tft->drawLine(prev_x, prev_y, x,y, color);

        prev_x = x;
        prev_y = y;

        if (data.at(i).dt() - lastCheck < 10800){
            continue;
        }

        draw_number_chart(tft, idx, x, y, color, data, i);

        lastCheck = data.at(i).dt();
    }
}

void
draw_dots_chart(
    TFT_eSPI* tft,
    uint8_t idx, 
    std::vector<WeatherData>& data, 
    ui16 starting_x_, 
    ui16 pixel_offset,
    ui16 color,
    float scale_pos, 
    float scale_neg
)
{
    HH_YY_date* dt = get_date_struct(data.at(0).dt());
    i16 x = dt->hour * HOURS_PIXELS + dt->min / 5 * MINUTES_5_PIXELS + starting_x_,
    y = get_y_pos_by_idx(idx, scale_pos, scale_neg, 0, data);
    delete dt;

    uint64_t lastCheck = data.at(0).dt();

    tft->fillCircle(x,y,1,color);
    draw_number_chart(tft, idx, x, y, color, data, 0);

    for(ui16 i=1; i<data.size(); i++)
    {
        x += pixel_offset;
        y = get_y_pos_by_idx(idx, scale_pos, scale_neg, i, data);

        tft->fillCircle(x,y,1,color);

        if (data.at(i).dt() - lastCheck < 10800) // 3 hours
        {
            continue;
        }

        draw_number_chart(tft, idx, x, y, color, data, i);

        lastCheck = data.at(i).dt();
    }
}

void
LineCharTemp::
draw(bool forceDraw)
{
    draw_line_chart(tft, TEMP_IDX, data, starting_x_,pixel_offset, color, scale_positive, scale_negative);
}

void
LineCharTemp::
set_data(std::vector<WeatherData>& data)
{
    this->data = data;
    this->pixel_offset = set_data_(data);
}


//Feels like
void
LineChartFeelsLike::
draw(bool forceDraw)
{
    draw_line_chart(tft, FEELS_IDX, data, starting_x_,pixel_offset, color, scale_positive, scale_negative);
}

void
LineChartFeelsLike::
set_data(std::vector<WeatherData>& data)
{
    this->data = data;
    this->pixel_offset = set_data_(data);
}


// Pop
void
LineChartPop::
draw(bool forceDraw)
{
    draw_line_chart(tft, POP_IDX, data, starting_x_,pixel_offset, color, scale, 0.0f);
}

void
LineChartPop::
set_data(std::vector<WeatherData>& data)
{
    this->data = data;
    this->pixel_offset = set_data_(data);
}

// Humidity
void
LineChartHumidity::
draw(bool forceDraw)
{
    draw_line_chart(tft, HUM_IDX, data, starting_x_,pixel_offset, color, scale, 0.0f);
}

void
LineChartHumidity::
set_data(std::vector<WeatherData>& data)
{
    this->data = data;
    this->pixel_offset = set_data_(data);
}
