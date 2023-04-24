#pragma once

#include "../settings/SettingsScreen.h"
#include "../../../input/TouchScreen.h"
#include "../../items/memory/ReadMem.h"
#include "../../items/window/WindowItem.h"

namespace wifi{

class SavedWiFiScreen
{
    TFT_eSPI* tft;
    TouchScreen* ts;
    CustomButton* exit_button;
    CustomButton* erase_button;
    CustomButton* detail_button;
    settings::SettingsScreen* screen;
    window::WindowItem* window;

    uint16_t bg_c;
    ReadMem read_mem;

    bool change;

    void
    erase(settings::picked_list);

    void
    prepare();

    void
    set_window(String);

    void
    draw_title(bool forceDraw);

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

    bool
    changed();
};

}



