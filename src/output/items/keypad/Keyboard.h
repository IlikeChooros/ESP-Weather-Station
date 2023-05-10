#pragma once

#include "Keypad.h"
#include "../InputField.h"
#include "CustomButton.h"

#define IGNORE 0
#define DELETE 1
#define NORMAL_BUTTON 2

#define MAIN_QWERTY 0
#define MAIN_QWERTY_CAPS 1
#define NUMBERS 2


#define NUMBER_OF_KEYBOARDS 3

#define CAPS_LOCK 27
#define DELETE_IDX 28
#define SPACE 29

struct 
KeyInfo
{
    uint8_t info;
    String str;
};

class Keyboard
{
    TFT_eSPI* tft;
    Keypad** keypads;
    CustomButton* delete_button;
    CustomButton* caps_button;
    KeypadButton* space_button;
    TouchButton** buttons;

    uint8_t current_keypad;
    uint8_t last_pressed;

    void
    change_keypad();

    void
    caps();

    void
    re_draw();

public:
    Keyboard(
        TFT_eSPI *tft
    );

    ~Keyboard();

    void 
    draw(bool forceDraw);

    KeyInfo*
    check(Point* pos);

    String
    get_str();
};