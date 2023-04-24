#pragma once

#include "Arduino.h"
#include "TFT_eSPI.h"
#include "SPI.h"
#include <EEPROM.h>

#include "../../../weather_client/WeatherClient.h"
#include "../../../input/TouchScreen.h"

#include "../../items/ListItem.h"
#include "../../items/memory/ReadMem.h"


// city name is up to 22 characters, 512 - 2*22 -2 = 466, 
// 466 (default) address is used for number of saved city names
// 467 - idx               <-|
// 468-489 - string          | difference is MAX_CITY_LEN+1 (490-467 = 23)
// 490 - idx               <-|
// 491 - 512 - string
class
CityNameScreen
{

public:
    explicit CityNameScreen(
        TFT_eSPI* tft,
        uint16_t bg_c,
        WeatherClient* wc,
        TouchScreen* ts
    ): tft(tft), bg_c(bg_c),
    load_main_(false),
    change_(false),
    wclient(wc), ts(ts) {}

    virtual void
    draw(bool forceDraw) = 0;

    virtual void
    check(Point*) = 0;

    bool 
    load_main();
    
    bool
    change();

protected:
    TFT_eSPI* tft;
    uint16_t bg_c;
    WeatherClient* wclient;
    TouchScreen* ts;

    bool load_main_;
    bool change_;

    bool
    draw_get(String city_name, uint8_t idx);
};