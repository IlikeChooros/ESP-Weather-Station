#include "Keypad.h"

Keypad::Keypad(
    TFT_eSPI* tft, 
    String* button_data, 
    String slider 
)
{
    buttons = new KeypadButton*[NUMBER_OF_KEYPAD_BUTTONS];
    for (uint8_t y=0; y < 2; ++y){
        for (uint8_t i=0; i < 10; ++i){
            buttons[i + y*10] = new KeypadButton(
                tft, i*(KEYPAD_BUTTON_WIDTH+2) + 2,
                y*(KEYPAD_BUTTON_HEIGHT + 2) + STARTING_Y+20,
                KEYPAD_BUTTON_WIDTH,
                KEYPAD_BUTTON_HEIGHT,
                button_data[i + y*10]
            );
        }
    }

    for (uint8_t i=0; i < 8; ++i){
        buttons[20 + i] = new KeypadButton(
            tft, (i + 1) * (KEYPAD_BUTTON_WIDTH + 2) + 2,
            2*(KEYPAD_BUTTON_HEIGHT + 2) + STARTING_Y + 20,
            KEYPAD_BUTTON_WIDTH,
            KEYPAD_BUTTON_HEIGHT,
            button_data[20 + i]
        );
    }

    this->slider = new KeypadButton(
        tft, 320 - KEYPAD_BUTTON_WIDTH, 2*KEYPAD_BUTTON_HEIGHT + STARTING_Y + 24,
        KEYPAD_BUTTON_WIDTH, KEYPAD_BUTTON_HEIGHT, slider);
    
    this->slider
    ->set_color(0x5836);

    buttons[NUMBER_OF_KEYPAD_BUTTONS-1] = new KeypadButton(
        tft, 70, 207, 180, 30, " "
    );
    
}

String 
Keypad::
get_button_str(uint8_t idx){
    return buttons[idx]->get_str();
}

void 
Keypad::
set_on_press(
    void(*on_press)(void), 
    uint8_t idx
)
{
    buttons[idx]->set_on_press(on_press);
}

void 
Keypad::
set_color(
    uint16_t color, 
    uint8_t idx
)
{
    buttons[idx]->set_color(color);
}

void 
Keypad::
set_on_touch_color(
    uint16_t color, 
    uint8_t idx
)
{
    buttons[idx]->set_on_touch_color(color);
}

void 
Keypad::
set_text_color(
    uint16_t color, 
    uint8_t idx
)
{
    buttons[idx]->set_text_color(color);
}

void 
Keypad::
draw(bool forceDraw)
{
    for (uint8_t i=0; i < NUMBER_OF_KEYPAD_BUTTONS; i++){
        buttons[i]->draw(forceDraw);
    }
    slider->draw(forceDraw);
}

void 
Keypad::
re_draw(uint8_t idx)
{
    if (idx == 0){
        slider->draw(true);
        return;
    }
    buttons[idx-1]->draw(true);
}

int8_t 
Keypad::
check(Point* pos)
{
    for (uint8_t i=0; i < NUMBER_OF_KEYPAD_BUTTONS; i++){
        if (buttons[i]->check(pos->x, pos->y)){
            return i+1;
        }
    }
    if (slider->check(pos->x, pos->y)){
        return 0;
    }
    return -1;
}

void 
Keypad::
clear()
{
    for (uint8_t i=0; i < NUMBER_OF_KEYPAD_BUTTONS; i++){
        delete buttons[i];
    }
    delete [] buttons;
}