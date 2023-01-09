#ifndef WIFI_LIST_SCREEN_H
#define WIFI_LIST_SCREEN_H

#include <WiFi.h>

#include "../items/WiFiListItem.h"
#include "../items/KeypadButton.h"
#include "WiFiScreen.h"

#define HEIGHT 30
#define WIDTH 270
#define OFFSET 5

class WiFiListScreen: public WiFiScreen
{
    bool scroll;
    TouchButton** wifis;
    TouchButton* refresh_button;

    int8_t number_of_networks;

    String picked_wifi;

    bool change_;
    bool onRelease;
    uint8_t onReleaseIdx;
    public:
    WiFiListScreen(TFT_eSPI* tft, uint16_t bg_c, void(*refresh_func)(void)): WiFiScreen(tft, bg_c){
        WiFi.mode(WIFI_STA);
        onRelease = false;
        change_ = false;
        onReleaseIdx = 0;

        refresh_button = new KeypadButton(tft, 285, 10, 30, 30, "O");
        refresh_button->set_color(TFT_DARKGREEN);
        refresh_button->set_on_press(refresh_func);
    }

    void scan();
    void draw();
    void draw(String wifi_name){
        return;
    }
    String get_str()
    {
        return this->picked_wifi;
    }
    void check(int16_t* pos);
    void clear_buttons();
    bool change();
    bool load_main(){
        return false;
    }
};

#endif