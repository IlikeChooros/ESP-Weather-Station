#ifndef PASSWORD_INPUT_SCREEN_H
#define PASSWORD_INPUT_SCREEN_H

#include "WiFiScreen.h"

#include "../../items/keypad/CustomButton.h"
#include "../../items/keypad/Keyboard.h"
#include "../../items/InputField.h"

class PasswordInputScreen: public WiFiScreen
{
    Keyboard* keyboard;
    InputField* inputfield;

    CustomButton* enter_button;
    CustomButton* exit_button;

    String wifi_name;

    uint8_t counter;

    bool change_;
    bool load_main_;

    void 
    enter_pwd();

    public:
    PasswordInputScreen(
        TFT_eSPI* tft, 
        uint16_t bg_c
    );

    ~PasswordInputScreen();

    void 
    draw(bool forceDraw);
    
    void 
    draw(String wifi_name);

    void 
    check(Point* pos);

    bool
    change();

    String 
    get_str();

    void 
    clear_buttons();

    bool 
    load_main();

    void 
    scan(){
        return;
    }
    
    void 
    init(){
        return;
    }
    
};

#endif