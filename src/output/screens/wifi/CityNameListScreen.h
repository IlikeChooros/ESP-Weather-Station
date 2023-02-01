#pragma once


#include "CityNameScreen.h"

#include "../../../data_structures/Vector.h"
#include "../../../data_structures/Vector.cpp"

#include "../../../data_structures/Point.h"

#include "../../items/keypad/KeypadButton.h"
#include "../../items/wifi/WiFiItem.h"



#define LIST_HEIGHT 60
#define LIST_WIDTH 280

class
CityNameListScreen: public CityNameScreen
{
    ListItem** saved_city_names;

    KeypadButton* input_city;
    WiFiItem* wifi;

    Vector<City_info> city_info;

    Vector<String> city_names;
    uint8_t number_of_saved_city_names;

public:
    CityNameListScreen(
        TFT_eSPI* tft,
        uint16_t bg_c,
        WeatherClient* wc,
        TouchScreen* ts
    ): CityNameScreen(tft, bg_c, wc, ts)
    {
        input_city = new KeypadButton(tft, 0, 180, 320, 60, "Set new location.");
        input_city->set_color(0x10A3);
        input_city->set_on_touch_color(0x0861);
        wifi = new WiFiItem(tft, 5,5,20, bg_c);

        
    }

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