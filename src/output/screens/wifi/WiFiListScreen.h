#ifndef WIFI_LIST_SCREEN_H
#define WIFI_LIST_SCREEN_H


#include "../../items/wifi/WiFiListItem.h"
#include "../../items/keypad/KeypadButton.h"
#include "../../items/keypad/CustomButton.h"
#include "WiFiScreen.h"
#include "../settings/PickOptionScreen.h"

#define HEIGHT 30
#define WIDTH 270
#define OFFSET 5

class WiFiListScreen: public WiFiScreen
{
    WiFiListItem** wifis;
    CustomButton* refresh_button;

    ReadMem read_mem;
    int8_t number_of_networks;
    String picked_wifi;

    bool change_;
    bool load_main_;

    std::list<std::pair<String, String>> wifi_info;

    /// @brief  Reads form eeprom saved 
    /// ssids and passwords
    /// then saves it as a String** pointer
    void 
    read_from_eeprom_wifis();

    void 
    connect_to_wifi();

    public:
    WiFiListScreen(
        TFT_eSPI* tft, 
        uint16_t bg_c, 
        void(*refresh_func)(void)
    ): WiFiScreen(tft, bg_c){
        WiFi.mode(WIFI_STA);
        change_ = false;
        load_main_ = false;

        refresh_button = new CustomButton(tft, 285, 10, 30, 30, 0x3CE6);
        refresh_button
        ->set_draw(drawRefreshButton)
        ->touch_color(0x19E2)
        ->set_on_press(refresh_func);
    }

    void 
    scan();

    /// @brief Before using it, make sure
    /// envoke scan() method
    /// @param forceDraw true - every element on in this screen will be drawn, false - only the ones that need to be redrawn
    void 
    draw(bool forceDraw);

    void 
    init();

    void 
    draw(String wifi_name){
        return;
    }

    String 
    get_str(){
        return this->picked_wifi;
    }

    void 
    check(Point* pos);

    /// @brief Deletes all WiFi List Items
    void 
    clear_buttons();

    /// @brief Returns true if this screen has to be
    /// changed to another one
    /// @return 
    bool
    change();

    bool 
    load_main(){
        return this->load_main_;
    }
};

#endif