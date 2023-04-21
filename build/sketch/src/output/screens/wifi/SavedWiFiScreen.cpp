#line 1 "c:\\Users\\pawel\\arduino\\ESP-Weather-Station\\src\\output\\screens\\wifi\\SavedWiFiScreen.cpp"
#include "SavedWiFiScreen.h"

namespace wifi{

void exit(){

}

void erase(){

}

SavedWiFiScreen::
SavedWiFiScreen(
    TFT_eSPI* tft,
    TouchScreen* ts,
    uint16_t bg_c
): tft(tft), ts(ts),
bg_c(bg_c) 
{
    exit_button  = new CustomButton(tft, 285, 50, 30, 30, 0x8040);
    erase_button = new CustomButton(tft, 285, 90, 30, 30, TFT_DARKGREY);
    screen = new settings::SettingsScreen(tft, 20, 30, 240, 200);

    exit_button
    ->set_draw(drawExitButton)
    ->touch_color(0x30C2)
    ->set_on_press(wifi::exit);

    erase_button
    ->set_draw(drawTickButton)
    ->touch_color(0x30C2)
    ->set_on_press(wifi::erase);
}

void
SavedWiFiScreen::
check(){
    Point* pos = ts->read_touch();

    if (!pos){
        return;
    }

    
}


}




