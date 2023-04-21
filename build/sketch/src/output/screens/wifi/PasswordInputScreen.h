#line 1 "c:\\Users\\pawel\\arduino\\ESP-Weather-Station\\src\\output\\screens\\wifi\\PasswordInputScreen.h"
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
    ): WiFiScreen(tft, bg_c), counter(0), change_(false),
    load_main_(false), wifi_name("") 
    {
        enter_button = new CustomButton(tft, 275, 20, 35, 40,0x3CE6);
        enter_button
        ->set_draw(drawTickButton)
        ->touch_color(0x19E2);
        exit_button = new CustomButton(tft, 5, 5, 30, 30, 0x8040);
        exit_button
        ->set_draw(drawExitButton)
        ->touch_color(0x30C2);

        inputfield = new InputField(tft, 40, 20, 230, 40);
        keyboard = new Keyboard(tft);
    }

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