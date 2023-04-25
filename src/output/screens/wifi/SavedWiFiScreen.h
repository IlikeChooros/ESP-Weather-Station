#pragma once

#include "../settings/SettingsScreen.h"
#include "../../../input/TouchScreen.h"
#include "../../items/memory/ReadMem.h"
#include "../../items/window/WindowDelete.h"

namespace wifi{

class SavedWiFiScreen
{
    TFT_eSPI* tft;
    TouchScreen* ts;
    CustomButton* exit_button;
    CustomButton* detail_button;
    settings::SettingsScreen* screen;
    window::WindowDelete* window;

    uint16_t bg_c;
    ReadMem read_mem;
    String to_erase;
    bool change;

    void
    erase(String&);

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

    String 
    erased();
};

}



