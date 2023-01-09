#ifndef PASSWORD_INPUT_SCREEN_H
#define PASSWORD_INPUT_SCREEN_H

#include <WiFi.h>
#include "WiFiScreen.h"

#include "../items/Keypad.h"
#include "../items/InputField.h"

#define LEFT_KEYBUTTON 0
#define RIGHT_KEYBUTTON 1

#define MAIN_QWERTY_CAPS 4
#define NUMBERS_CAPS 3

#define NUMBER_OF_KEYBOARDS 5

class PasswordInputScreen: public WiFiScreen
{
    Keypad** keypads;
    InputField* inputfield;

    TouchButton* enter_button;
    TouchButton* exit_button;

    int8_t current_keypad;
    uint8_t last_pressed;

    String wifi_name;

    bool change_;
    bool load_main_;

    void re_draw();
    void enter_pwd();
    void caps();
    void change_keypad(int8_t dir);
    public:
    PasswordInputScreen(TFT_eSPI* tft, uint16_t bg_c): WiFiScreen(tft, bg_c){

        String main_qwerty [24] = {"q", "w", "e" ,"r", "t","y","u" ,"<<",     "a", "s", "d","f","g","h","j", "^",     "z", "x","c","v", "b","n","m","o"};
        String numbers [24] = {"i", "p", "k", "l", "0", "1", "2", "<<",   "3","4","5","6","7","8","9", "^",    "!", "?", "$", "%", "^", "&","*","@"};
        String main_qwerty_C [24] = {"Q", "W", "E" ,"R", "T","Y","U" ,"<<",     "A", "S", "D","F","G","H","J", "^",     "Z", "X","C","V", "B","N","M","O"};
        String numbers_C [24] = {"I", "P", "K", "L", "0", "1", "2", "<<",   "3","4","5","6","7","8","9", "^",    "!", "?", "$", "%", "^", "&","*","@"};
        String special [24] = {"(", ")", "[", "]", "{", "}", ";", "<<",   ":","'","\"",",",".","<",">", "\\",    "|", "+", "-", "#", "", "","",""};

        change_ = false;
        load_main_ = false;
        last_pressed = 0;

        enter_button = new KeypadButton(tft, 275, 20, 35, 40, "+");
        enter_button->set_color(TFT_DARKGREEN);

        exit_button = new KeypadButton(tft, 5, 5, 30, 30, "x");
        exit_button->set_color(TFT_RED);

        keypads = new Keypad* [NUMBER_OF_KEYBOARDS]{
            new Keypad(tft, special, "1234", "Aabc"), 
            new Keypad(tft, main_qwerty, "$#@!", "1234"),
            new Keypad(tft, numbers, "AaBc", "$#@!"),
            new Keypad(tft, numbers_C, "AaBc", "$#@!"),
            new Keypad(tft, main_qwerty_C, "$#@!", "1234")
        };
        this->inputfield = new InputField(tft, 40, 20, 230, 40);

        for (uint8_t i=0; i<NUMBER_OF_KEYBOARDS; i++)
        {
            keypads[i]->set_color(TFT_RED, 7);
        }
        keypads[1]->set_color(TFT_DARKCYAN ,15);
        keypads[2]->set_color(TFT_DARKCYAN ,15);
        keypads[3]->set_color(TFT_DARKCYAN ,15);
        keypads[4]->set_color(TFT_DARKCYAN ,15);
        current_keypad = 1;
    }

    void draw()
    {
        return;
    }
    void draw(String wifi_name);
    void check(int16_t* pos);
    bool change();
    String get_str()
    {
        return "";
    }
    void scan()
    {
        return;
    }
    void clear_buttons();
    bool load_main();
};

#endif