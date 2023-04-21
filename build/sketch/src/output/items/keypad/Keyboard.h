#line 1 "c:\\Users\\pawel\\arduino\\ESP-Weather-Station\\src\\output\\items\\keypad\\Keyboard.h"
#pragma once

#include "Keypad.h"
#include "../InputField.h"

#define IGNORE 0
#define DELETE 1
#define NORMAL_BUTTON 2

#define MAIN_QWERTY 0
#define NUMBERS 1
#define MAIN_QWERTY_CAPS 2

#define NUMBER_OF_KEYBOARDS 3

#define CAPS_LOCK 28
#define DELETE_IDX 20

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
    change_keypad();

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
    draw(bool forceDraw);

    KeyInfo*
    check(Point* pos);

    String
    get_str();
};