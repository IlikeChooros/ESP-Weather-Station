#include "WiFiListScreen.h"

namespace wifi{

WiFiListScreen::
WiFiListScreen(
    TFT_eSPI* tft, 
    TouchScreen* ts,
    uint16_t bg_c, 
    void(*refresh_func)(void)
): WiFiScreen(tft, bg_c),
ts(ts), change_(false),
load_main_(false){
    WiFi.mode(WIFI_STA);

    refresh_button = new CustomButton(tft, 285, 10, 30, 30, 0x3CE6);
    refresh_button
    ->set_draw(drawRefreshButton)
    ->touch_color(0x19E2)
    ->set_on_press(refresh_func);

    settings_button = new CustomButton(tft, 285, 55, 30, 30, TFT_DARKGREY);
    settings_button
    ->set_draw(drawSettingsButton)
    ->touch_color(0x18E3);
}

WiFiListScreen::
~WiFiListScreen(){
    delete refresh_button;
    delete settings_button;

    if (number_of_networks > 0){
        for (uint8_t i = 0; i < number_of_networks; ++i){
            delete wifis[i];
        }
        delete [] wifis;
    }
}

void WiFiListScreen::init(){
    wifi_info = read_mem.wifis(true);
}

//-----------------------------------
// Scans for WiFis, creates new WiFi
// List Objects with WiFis data
// make sure to call clear_buttons()
// before using it
//----------------------------------
void WiFiListScreen::scan()
{
    change_ = false;

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    number_of_networks = WiFi.scanNetworks();
    wifis = 0;

    if (number_of_networks <= 0){
        return;
    }

    uint16_t x = 10, y = 10;
    uint8_t size_count = 1;
    number_of_networks = number_of_networks < 6 ? number_of_networks : 6;
    wifis = new WiFiListItem* [number_of_networks];
    
    tft->loadFont(LATIN);
    for (uint8_t i=0; i < number_of_networks; i++){
        String ssid = WiFi.SSID(i);
        bool is_saved = false;
        for (auto j : wifi_info){
            // If saved wifi has the same ssid as the scanned wifi
            if (j.first == ssid){
                is_saved = true;
                break;
            }
        }
        wifis[i] = new WiFiListItem(tft, x, y + i *(HEIGHT+OFFSET), WIDTH, HEIGHT, ssid, is_saved, WiFi.RSSI(i), bg_c);
    }
    tft->unloadFont();
}

void 
WiFiListScreen::
check(Point* pos){
    change_ = false;
    for (uint8_t i=0; i<number_of_networks; i++)
    {
        if (wifis[i]->check(pos->x, pos->y)){

            picked_wifi = wifis[i]->get_ssid();
            if (wifis[i]->is_saved()){
                connect_to_wifi();
                return;
            }
            change_ = true;
            return;
        }
    }

    // Already got refresh function
    if (refresh_button->check(pos->x, pos->y)){
        return;
    }

    if (settings_button->check(pos->x, pos->y)){
        settings();
    }
}

void
WiFiListScreen::
settings(){
    tft->fillScreen(bg_c);
    std::unique_ptr<SavedWiFiScreen> screen(new SavedWiFiScreen(tft, ts, bg_c));

    screen->draw(true);
    while (!screen->exited()){
        screen->check();
    }
    if (screen->changed()){
        wifi_info = read_mem.wifis(true);
        // Look for deleted network, and update icon
        for (uint8_t i=0; i < number_of_networks; ++i){
            if (wifis[i]->get_ssid() != screen->erased()){
                continue;
            }
            wifis[i]->set_save(false);
        }
    }
    tft->fillScreen(bg_c);
    draw(true);
}

void 
WiFiListScreen::
connect_to_wifi(){
    String psw;
    // Look for saved wifi
    for (auto i : wifi_info){
        if (i.first == picked_wifi){
            psw = i.second;
            break;
        }
    }

    char* pass = new char [psw.length()+1];
    char* ssid = new char [picked_wifi.length()+1];

    psw.toCharArray(pass, psw.length()+1);
    picked_wifi.toCharArray(ssid, picked_wifi.length()+1);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);

    load_main_ = draw_connecting_to_wifi(picked_wifi, ssid, pass);
    change_ = !load_main_;
}

bool 
WiFiListScreen::
change(){
    return this->change_;
}

void 
WiFiListScreen::
draw(bool forceDraw){
    for (uint8_t i=0; i<number_of_networks; i++){
        wifis[i]->draw(forceDraw);
    }
    refresh_button->draw(forceDraw);
    settings_button->draw(forceDraw);
}

void 
WiFiListScreen::
clear_buttons(){
    if (!number_of_networks){
        return;
    }
    for (uint8_t i=0; i < number_of_networks; i++){
        delete wifis[i];
    }
    delete [] wifis;
}

}