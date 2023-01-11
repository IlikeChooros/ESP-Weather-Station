#ifndef KEYPAD_H
#define KEYPAD_H

#include "KeypadButton.h"

// #include "../screens/PasswordInputScreen.h"

#define NUMBER_OF_KEYPAD_BUTTONS 25
#define STARTING_Y 60
#define KEYPAD_BUTTON_WIDTH 30
#define KEYPAD_BUTTON_HEIGHT 40

class Keypad
{
    KeypadButton** buttons;
    KeypadButton** sliders;

    public:
    Keypad(TFT_eSPI* tft, String* button_data, String left_slider, String right_slider);
    void draw();
    void re_draw(uint8_t idx);
    int8_t check(int16_t* pos);
    void clear();
    String get_button_str(uint8_t idx);
    void set_on_press(void(*)(void), uint8_t idx);
    void set_color(uint16_t color, uint8_t idx);
};

#endif