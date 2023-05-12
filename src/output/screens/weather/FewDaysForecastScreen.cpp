#include "FewDaysForecastScreen.h"

FewDaysForecastScreen::
FewDaysForecastScreen(TFT_eSPI *tft, uint16_t bg_c): MainScreen(tft,bg_c){
    column_items = new ColumnItem[NUMBER_OF_DAYS_TO_FORECAST];
    column_height = this->_tft->width();
    column_width = this->_tft->height()/NUMBER_OF_DAYS_TO_FORECAST;

    for (uint8_t i=0; i<NUMBER_OF_DAYS_TO_FORECAST; i++)
    {
        column_items[i].number_of_items = NUMBER_OF_COLUMN_ITEMS;
        column_items[i].weather_items = new WeatherItem* [NUMBER_OF_COLUMN_ITEMS]{
            new TimeItem(_tft, i*column_width+column_width/2, 10, bg_c, MIST, WEATHER_FONT, 0, false),
            new WeatherIcon(_tft,i*column_width,40,column_width, this->bg_c),
            new TextTemp(_tft, i*column_width+column_width/2 - 3, 55 + column_width, WEATHER_FONT, TFT_WHITE, "%d °C",bg_c),
            new TextFeelsLike(_tft, i*column_width+column_width/2 - 3, 80 + column_width, WEATHER_FONT, TFT_WHITE, "%d °C", bg_c),
            new TextPop(_tft, i*column_width+25, 100 + column_width + 10, WEATHER_FONT ,WATER, "%d %%", bg_c),
            new DropletItem(_tft,i*column_width+5, 105 + column_width, 20, bg_c)
        };
    }
}

void FewDaysForecastScreen::draw(Forecast* forecast, bool forceDraw)
{
    uint8_t current_day = get_day(forecast->forecasted_weather[0]->_dt + forecast->forecasted_weather[0]->_timezone);
    uint8_t starting_itr = 1;
    float* result;
    while(current_day == get_day(forecast->forecasted_weather[starting_itr]->_dt + forecast->forecasted_weather[starting_itr]->_timezone)) {starting_itr++;}
    starting_itr += 4;
    for (uint8_t i=0; i<NUMBER_OF_DAYS_TO_FORECAST; i++){
        result = getMinMaxTemp_pop(forecast, i*8 + starting_itr - 4);
        forecast->forecasted_weather[i*8 + starting_itr]->pop(result[POP]);
        forecast->forecasted_weather[i*8 + starting_itr]->temp((double)result[MAX_TEMP]);
        forecast->forecasted_weather[i*8 + starting_itr]->feels_like((double)result[MIN_TEMP]);

        for (uint8_t j=0;j<NUMBER_OF_COLUMN_ITEMS;j++){
            column_items[i].weather_items[j]->setWeather(forecast->forecasted_weather[i*8 + starting_itr]);
            column_items[i].weather_items[j]->draw(forceDraw);
        }
        delete [] result;
    }
}

float*  FewDaysForecastScreen::getMinMaxTemp_pop(Forecast* forecast, uint8_t start_idx)
{
    float* results = new float [3] {0.0f,-100.0f,100.0f};

    for (int8_t a = 0; a<8;a++)
    {
        results[POP] += forecast->forecasted_weather[(uint16_t) a + start_idx]->_pop;

        if (forecast->forecasted_weather[(uint16_t) a + start_idx]->_temp > results[MAX_TEMP]){
            results[MAX_TEMP]= forecast->forecasted_weather[(uint16_t) a + start_idx]->_temp;
        }
        if (results[MIN_TEMP] > forecast->forecasted_weather[(uint16_t) a + start_idx]->_temp){
            results[MIN_TEMP] = forecast->forecasted_weather[(uint16_t) a + start_idx]->_temp;
        }
    }
    results[POP] /= 8;
    return results;
}