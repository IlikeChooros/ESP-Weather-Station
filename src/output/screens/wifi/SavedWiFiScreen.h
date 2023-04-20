#pragma once

#include "../settings/SettingsScreen.h"
#include "../../../input/TouchScreen.h"

namespace wifi{

class SavedWiFiScreen
{
    TFT_eSPI* tft;
    TouchScreen* ts;
    uint16_t bg_c;

    CustomButton* exit_button;
    CustomButton* erase_button;

    settings::SettingsScreen* screen;
public:
    SavedWiFiScreen(
        TFT_eSPI* tft, 
        TouchScreen* ts,
        uint16_t bg_c
    );
    
    ~SavedWiFiScreen();

    void
    check();

    void
    draw(bool);

    bool
    exited();


};

}



