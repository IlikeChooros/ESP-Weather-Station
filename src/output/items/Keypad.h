#ifndef KEYPAD_H
#define KEYPAD_H

#include "KeypadButton.h"

#define NUMBER_OF_KEYPAD_BUTTONS 14
#define STARTING_Y 60
#define KEYPAD_BUTTON_WIDTH 50
#define KEYPAD_BUTTON_HEIGHT 45

class Keypad
{
    TouchButton** buttons;
    public:
    Keypad(TFT_eSPI* tft, String* button_data, String left_slider, String right_slider);
    void draw();
    void check(int16_t* pos);
    String get_button_str(uint8_t );
    void set_on_press(void(*)(void), uint8_t idx);
};

#endif