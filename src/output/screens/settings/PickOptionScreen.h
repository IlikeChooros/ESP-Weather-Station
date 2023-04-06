#pragma once

#include "SettingsScreen.h"
#include "../../../input/TouchScreen.h"
namespace settings{
// Screen class with SettingsScreen (list display module) and pick buttons
class PickOptionScreen
{
    TFT_eSPI* tft;
    TouchScreen* ts;
    CustomButton* _exit;
    CustomButton* _confirm;
    SettingsScreen* _sc;
public:
    PickOptionScreen(
        TFT_eSPI* tft, 
        TouchScreen* ts
    );
    ~PickOptionScreen();

    PickOptionScreen*
    prepare(const print_data&);

    PickOptionScreen*
    prepare(const std::vector<print_data>&);

    void
    init();

    void
    draw(bool forceDraw);
    
    void
    check();

    bool
    load_main();

    bool
    picked();

    picked_list
    get_picked();
};

}


