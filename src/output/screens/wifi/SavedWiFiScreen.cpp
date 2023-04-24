#include "SavedWiFiScreen.h"

namespace wifi{

bool exit_screen;

void exit(){
    exit_screen = true;
}

SavedWiFiScreen::
SavedWiFiScreen(
    TFT_eSPI* tft,
    TouchScreen* ts,
    uint16_t bg_c
): tft(tft), ts(ts),
bg_c(bg_c), change(false)
{
    exit_button   = new CustomButton(tft, 285, 10, 30, 30, 0x8040);
    detail_button = new CustomButton(tft, 285, 55, 30, 30, 0x5AEB);
    screen = new settings::SettingsScreen(tft, 20, 30, 250, 210);
    window = new window::WindowDelete(tft, 40, 40, 240, 160, TFT_DARKGREY, TFT_LIGHTGREY);

    exit_button
    ->set_draw(drawExitButton)
    ->touch_color(0x30C2)
    ->set_on_press(wifi::exit);

    detail_button
    ->set_draw(drawDetailsButton)
    ->touch_color(TFT_BLUE);

    exit_screen = false;
    prepare();
}

SavedWiFiScreen::
~SavedWiFiScreen(){
    delete exit_button;
    delete screen;
}

void
SavedWiFiScreen::
prepare(){
    auto wifis = read_mem.wifis(true);
    std::vector<print_data> to_print;
    to_print.resize(wifis.size());
    uint8_t count = 0;
    for (auto i : wifis){
        to_print.at(count) = print_data(
            i.first, 2, 2, TFT_LIGHTGREY, true
        );
        count++;
    }
    screen->prepare(to_print)->init();
}

void
SavedWiFiScreen::
set_window(String ssid){
    auto wifis = read_mem.wifis(true);
    for (auto i : wifis){
        if (i.first != ssid){
            continue;
        }
        std::vector<print_data> data;
        data.resize(4);
        data.at(0) = {
            "SSID:", 2, 1, TFT_WHITE, true
        };
        data.at(1) = {
            i.first, 2, 1, TFT_WHITE, true
        };
        data.at(2) = {
            "PASS:", 2, 1, TFT_WHITE, false
        };
        data.at(3) = {
            i.second, 2, 1, TFT_WHITE, true
        };
        window->prepare(data)->init();
        break;
    }
    window->draw(true);
    while(!window->exited()){
        Point* pos = ts->read_touch();
        if (!pos){
            continue;
        }
        window->check(pos);
        if(window->deleted()){
            Serial.println("DELETE");
            erase(ssid);
        }
        delete pos;
    }
    tft->fillScreen(bg_c);
    draw(true);
}

void
SavedWiFiScreen::
check(){
    Point* pos = ts->read_touch();

    if (!pos){
        return;
    }

    screen->check(pos);
    if (screen->picked()){
        if (detail_button->check(pos->x, pos->y)){
            Serial.println("IDX " + String(screen->picked_data().idx));
            set_window(screen->picked_data().data.string);
            delete pos;
            return;
        }
    }    
    exit_screen = exit_button->check(pos->x, pos->y);
    delete pos;
}

void
SavedWiFiScreen::
erase(String& data){
    Serial.println("ERASE: " + data);
    read_mem.deleteWifi(data);
    screen->clear();
    prepare();
    change = true;
}

void
SavedWiFiScreen::
draw(bool forceDraw){
    screen->draw(forceDraw);
    exit_button->draw(forceDraw);
    detail_button->draw(forceDraw);
    draw_title(forceDraw);
}

void
SavedWiFiScreen::
draw_title(bool forceDraw){
    if (!forceDraw){
        return;
    }
    tft->setTextColor(TFT_WHITE);
    tft->setTextSize(1);
    tft->drawCentreString("Manage networks", 145, 5, 2);
}

bool
SavedWiFiScreen::
exited(){
    return exit_screen;
}

bool 
SavedWiFiScreen::
changed(){
    return change;
}

}




