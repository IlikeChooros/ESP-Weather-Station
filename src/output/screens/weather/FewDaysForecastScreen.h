#ifndef FEW_DAYS_FORECAST_SCREEN_H
#define FEW_DAYS_FORECAST_SCREEN_H

#include "MainScreen.h"
#include "../../items/ColumnItem.h"
#include "../../../weather_client/Forecast.h"
#include "../../items/TextItem.h"
#include "../../items/TimeItem.h"
#include "../../items/DropletItem.h"
#include "../../icons/WeatherIcon.h"
#include "../../icons/WindIcon.h"
#include "../../icons/Icons.h"
#include "../../../weather_client/Weather.h"
#include "../../../data_structures/Hsv_to_rgb.h"
#include "../../../data_structures/get_day.h"

#define NUMBER_OF_COLUMN_ITEMS 6
#define NUMBER_OF_DAYS_TO_FORECAST 4

#define POP 0
#define MAX_TEMP 1
#define MIN_TEMP 2


class FewDaysForecastScreen: public MainScreen
{
    ColumnItem* column_items;
    uint8_t column_height,
            column_width;
    float* 
    getMinMaxTemp_pop(
        Forecast* forecast, 
        uint8_t start_idx
    );
    public:
    FewDaysForecastScreen(TFT_eSPI *tft, uint16_t bg_c);
    
    void 
    draw(
        Forecast* forecast, 
        bool forceDraw
    );

    void 
    draw(
        Weather* weather, 
        bool forceDraw
    )
    {
        return;
    }
    
    void 
    refresh(
        bool forceUpdate
    )
    {
        return;
    }

    void 
    init(Weather*) {
        return;
    }
};



#endif