#pragma once

#include <vector>

#include "CityNameScreen.h"
#include "../../../data_structures/Point.h"
#include "../../items/keypad/CustomButton.h"
#include "../../items/wifi/WiFiItem.h"

#define LIST_HEIGHT 60
#define LIST_WIDTH 280

class
CityNameListScreen: public CityNameScreen
{
    ListItem** city_list;
    CustomButton* set_new_location;
    WiFiItem* wifi;
    TFT_eSprite choose_location;
    TFT_eSprite wifi_name;
    uint16_t choose_location_x;

    ReadMem read_mem;
    std::list<std::pair<String, uint8_t>> city_info;
    uint8_t number_of_saved_city_names;

    void
    draw_wifi_name(bool forceDraw);

public:
    CityNameListScreen(
        TFT_eSPI* tft,
        uint16_t bg_c,
        WeatherClient* wc,
        TouchScreen* ts
    );

    ~CityNameListScreen();

    /**
     * @brief Reads form eeprom saved city names,
     * should be called only once, before using any other method
     * in this class
     */
    void 
    init();

    void
    set_city_info();

    void 
    check(Point* pos);

    void
    draw(bool forceDraw);
};