#include "FewDaysForecastScreen.h"

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