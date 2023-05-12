#ifndef FORECAST_12_SCREEN_H
#define FORECAST_12_SCREEN_H

#include "MainScreen.h"
#include "../../../weather_client/Forecast.h"
#include "../../../weather_client/Weather.h"
#include "../../items/ColumnItem.h"
#include "../../items/TextItem.h"
#include "../../items/TimeItem.h"
#include "../../items/DropletItem.h"
#include "../../icons/WeatherIcon.h"
#include "../../icons/Icons.h"
#include "../../../data_structures/Hsv_to_rgb.h"

#define NUMBER_OF_COLUMN_ITEMS 6
#define HOURS_TO_12_FORECAST 4

class Forecast12Screen: public MainScreen
{
    uint8_t column_height,
            column_width;

    ColumnItem* columnItems;
    public:
    Forecast12Screen(
        TFT_eSPI* tft, 
        uint16_t bg_c
    );
    
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