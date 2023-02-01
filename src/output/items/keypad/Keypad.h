#ifndef KEYPAD_H
#define KEYPAD_H

#include "KeypadButton.h"
#include "../../../data_structures/Point.h"

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

    /**
     * @brief Construct a new Keypad object, with 24 small buttons, 1 space, 2 sliders on right and left edges of the screen
     * 
     * @param tft 
     * @param button_data String [24] with button 'names'
     * @param left_slider  
     * @param right_slider 
     */
    Keypad(
        TFT_eSPI* tft, 
        String* button_data, 
        String left_slider, 
        String right_slider
    );
    void 
    draw(bool forceDraw);

    void 
    re_draw(uint8_t idx);

    int8_t 
    check(Point* pos);

    void 
    clear();

    String 
    get_button_str(uint8_t idx);

    void 
    set_on_press(
        void(*)(void), 
        uint8_t idx
    );

    void 
    set_color(
        uint16_t color, 
        uint8_t idx
    );

    void 
    set_on_touch_color(
        uint16_t color, 
        uint8_t idx
    );

    void 
    set_text_color(
        uint16_t color, 
        uint8_t idx
    );

    
};

#endif