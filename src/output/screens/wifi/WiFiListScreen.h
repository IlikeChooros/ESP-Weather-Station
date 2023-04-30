#ifndef WIFI_LIST_SCREEN_H
#define WIFI_LIST_SCREEN_H


#include "../../items/wifi/WiFiListItem.h"
#include "../../items/keypad/KeypadButton.h"
#include "../../items/keypad/CustomButton.h"
#include "WiFiScreen.h"
#include "SavedWiFiScreen.h"

#define HEIGHT 33
#define WIDTH 270
#define OFFSET 5
namespace wifi{

class WiFiListScreen: public WiFiScreen
{
    WiFiListItem** wifis;
    CustomButton* refresh_button;
    CustomButton* settings_button;
    TouchScreen* ts;

    ReadMem read_mem;
    int8_t number_of_networks;
    String picked_wifi;

    bool change_;
    bool load_main_;

    std::list<std::pair<String, String>> wifi_info;

    void 
    connect_to_wifi();

    void
    settings();

    public:
    WiFiListScreen(
        TFT_eSPI* tft, 
        TouchScreen* ts,
        uint16_t bg_c, 
        void(*refresh_func)(void)
    );
    
    ~WiFiListScreen();


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


}


#endif