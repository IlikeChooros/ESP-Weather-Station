#include "ChartScreens.h"

ChartScreens::
ChartScreens(
    TFT_eSPI *tft,
    uint16_t bg_c
): tft(tft), bg_c(bg_c)
{
    charts = new ChartItem* [6]{
        new ChartFrameVFull(tft, TFT_DARKGREY, STARTING_X, "`C"),
        new ChartFrameVUp(tft, TFT_DARKGREY, 301, "%"),
        new LineChartHumidity(tft, HUMIDITY_COLOR, STARTING_X),
        new LineChartPop(tft, POP_COLOR, STARTING_X),
        new LineCharTemp(tft, TEMP_COLOR, STARTING_X),
        new LineChartFeelsLike(tft, FEELS_LIKE_COLOR, STARTING_X)
    };
    chart_time = new ChartFrameTime(tft, TFT_DARKGREY);

    chart_names = new ChartName* [4]{
        new ChartName(tft, "TEMP", 160, 0, TEMP_COLOR),
        new ChartName(tft, "POP", 240, 0, POP_COLOR),
        new ChartName(tft, "FEELS LIKE", 160, 10, FEELS_LIKE_COLOR),
        new ChartName(tft, "HUM", 240, 10, HUMIDITY_COLOR)
    };
}

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
    if(forceDraw){
        draw_bg();
        draw_name(str);
    }
    chart_time->draw(forceDraw);
    if (data.size() == 1 || data.empty()){
        return;
    }

    int8_t max_value = -min_max[0] > min_max[1] ? -min_max[0] + 1 :  min_max[1] + 1;

    charts[0]->set_min_max(-max_value, max_value);
    charts[1]->set_min_max(0, 100);
    charts[2]->set_min_max(0, 100);
    charts[3]->set_min_max(0, 100);
    charts[4]->set_min_max(-max_value, max_value);
    charts[5]->set_min_max(-max_value, max_value);

    for (uint8_t i=0; i<6; i++){
        charts[i]->set_data(data);
        charts[i]->draw(true);
    }
}