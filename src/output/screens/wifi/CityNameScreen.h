#pragma once

#include "Arduino.h"
#include "TFT_eSPI.h"
#include "SPI.h"
#include <EEPROM.h>

#include "../../../weather_client/WeatherClient.h"
#include "../../../input/TouchScreen.h"

#include "../../items/ListItem.h"

#ifndef EEPROM_SIZE
#define EEPROM_SIZE 512
#endif

#define MAX_CITIES 2
#define CITY_NAME_LEN 22
#define CITY_NAME_IDX EEPROM_SIZE-CITY_NAME_LEN*MAX_CITIES-MAX_CITIES
// city name is up to 22 characters, 512 - 2*22 -2 = 466, 
// 466 address is used for number of saved city names
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
    wclient(wc), ts(ts)
    {}

    virtual void
    draw(bool forceDraw) = 0;

    bool 
    load_main() 
    {return this->load_main_;}

    bool
    change()
    {return this->change_;}

protected:
    TFT_eSPI* tft;
    uint16_t bg_c;
    WeatherClient* wclient;
    TouchScreen* ts;

    bool load_main_;
    bool change_;

    bool
    draw_get(String city_name);
};