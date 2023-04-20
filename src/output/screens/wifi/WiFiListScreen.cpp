#include "WiFiListScreen.h"

void WiFiListScreen::init(){
    read_from_eeprom_wifis();
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

    uint16_t x = 10, y = 20;
    uint8_t size_count = 1;

    number_of_networks = number_of_networks < 6 ? number_of_networks : 6;

    wifis = new WiFiListItem* [number_of_networks];
    
    for (uint8_t i=0; i < number_of_networks; i++){
        String ssid = WiFi.SSID(i);
        bool is_saved = false;
        for (auto j = wifi_info.begin(); j != wifi_info.end(); j++){
            // If saved wifi has the same ssid as the scanned wifi
            if (j->first == ssid){
                is_saved = true;
                break;
            }
        }
        wifis[i] = new WiFiListItem(tft, x, y + i *(HEIGHT+OFFSET), WIDTH, HEIGHT, ssid, is_saved,WiFi.RSSI(i), bg_c);
    }
}

void 
WiFiListScreen::
check(Point* pos){
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
    refresh_button->check(pos->x, pos->y);
}

void 
WiFiListScreen::
connect_to_wifi(){
    String psw;
    // Look for saved wifi
    for (auto i=wifi_info.begin(); i != wifi_info.end(); i++){
        if (i->first == picked_wifi){
            psw = i->second;
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


void 
WiFiListScreen::
read_from_eeprom_wifis(){
    wifi_info = read_mem.wifis(true);
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
}

void 
WiFiListScreen::
clear_buttons()
{
    if (number_of_networks<1){
        return;
    }
    for (uint8_t i=0; i<number_of_networks; i++){
        delete wifis[i];
    }
    delete [] wifis;
}