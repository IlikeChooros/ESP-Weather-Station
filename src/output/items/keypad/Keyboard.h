#pragma once

#include "Keypad.h"
#include "../InputField.h"

#define IGNORE 0
#define DELETE 1
#define NORMAL_BUTTON 2

#define LEFT_KEYBUTTON 0
#define RIGHT_KEYBUTTON 1
#define MAIN_QWERTY_CAPS 4
#define NUMBERS_CAPS 3

#define NUMBER_OF_KEYBOARDS 5

#define CAPS_LOCK 16
#define DELETE_IDX 8

struct 
KeyInfo
{
    uint8_t info;
    String str;
};

class Keyboard
{
    Keypad** keypads;

    uint8_t current_keypad;
    uint8_t last_pressed;

    void
    change_keypad(uint8_t idx);

    void
    caps();

    void
    re_draw();

public:
    Keyboard(
        TFT_eSPI *tft
    );

    ~Keyboard()
    {
        for(uint8_t i=0; i<NUMBER_OF_KEYBOARDS; i++)
        {
           keypads[i]->clear();
           delete keypads[i];
        }
        delete [] keypads;
    }

    void 
    draw();

    KeyInfo*
    check(Point* pos);

    String
    get_str();

    
};