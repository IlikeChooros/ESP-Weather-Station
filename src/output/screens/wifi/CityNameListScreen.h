#pragma once


#include "CityNameScreen.h"

#include <vector>

#include "../../../data_structures/Point.h"

#include "../../items/keypad/CustomButton.h"
#include "../../items/wifi/WiFiItem.h"



#define LIST_HEIGHT 60
#define LIST_WIDTH 280

class
CityNameListScreen: public CityNameScreen
{
    ListItem** saved_city_names;

    CustomButton* set_new_location;
    WiFiItem* wifi;

    std::vector<City_info> city_info;

    std::vector<String> city_names;
    uint8_t number_of_saved_city_names;

public:
    CityNameListScreen(
        TFT_eSPI* tft,
        uint16_t bg_c,
        WeatherClient* wc,
        TouchScreen* ts
    );

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