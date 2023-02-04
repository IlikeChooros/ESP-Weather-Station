#ifndef WIFI_LIST_SCREEN_H
#define WIFI_LIST_SCREEN_H


#include "../../items/wifi/WiFiListItem.h"
#include "../../items/keypad/KeypadButton.h"
#include "../../items/keypad/CustomButton.h"
#include "WiFiScreen.h"

#define HEIGHT 30
#define WIDTH 270
#define OFFSET 5

class WiFiListScreen: public WiFiScreen
{
    WiFiListItem** wifis;
    CustomButton* refresh_button;

    int8_t number_of_networks;

    String picked_wifi;

    bool change_;
    bool load_main_;

    String** saved_wifi_info;
    uint8_t number_of_saved_wifis;

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
        refresh_button->set_on_press(refresh_func);
        refresh_button
        ->set_draw(drawRefreshButton)
        ->touch_color(0x19E2);
    }

    void 
    scan();

    void 
    draw(bool forceDraw);

    void 
    init();

    void 
    draw(
        String wifi_name,
        bool forceDraw
    )
    {
        return;
    }

    String 
    get_str()
    {
        return this->picked_wifi;
    }

    void 
    check(Point* pos);

    void 
    clear_buttons();

    bool
    change();

    bool 
    load_main(){
        return this->load_main_;
    }
};

#endif