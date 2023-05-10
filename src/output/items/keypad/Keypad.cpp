#include "Keypad.h"

Keypad::Keypad(
    TFT_eSPI* tft, 
    String* button_data, 
    String slider 
): tft(tft)
{
    buttons = new KeypadButton*[NUMBER_OF_KEYPAD_BUTTONS];

    for (uint8_t i=0; i < 10; ++i){
        buttons[i] = new KeypadButton(
            tft, i*(KEYPAD_BUTTON_WIDTH+2) + 2,
            STARTING_Y+20,
            KEYPAD_BUTTON_WIDTH,
            KEYPAD_BUTTON_HEIGHT,
            button_data[i]
        );
    }

    for (uint8_t i=0; i < 9; ++i){
        buttons[i + 10] = new KeypadButton(
            tft, i*(KEYPAD_BUTTON_WIDTH+2) + 2 + KEYPAD_BUTTON_WIDTH/2 - 1,
            STARTING_Y+20 + KEYPAD_BUTTON_HEIGHT + 2,
            KEYPAD_BUTTON_WIDTH,
            KEYPAD_BUTTON_HEIGHT,
            button_data[i+ 10]
        );
    }

    for (uint8_t i=0; i < 7; ++i){
        buttons[19 + i] = new KeypadButton(
            tft, (i + 1) * (KEYPAD_BUTTON_WIDTH + 2) + 2,
            2*(KEYPAD_BUTTON_HEIGHT + 2) + STARTING_Y + 20,
            KEYPAD_BUTTON_WIDTH,
            KEYPAD_BUTTON_HEIGHT,
            button_data[19 + i]
        );
    }

    this->slider = new KeypadButton(
        tft, 320 - 2*KEYPAD_BUTTON_WIDTH - 7, 207,
        2*KEYPAD_BUTTON_WIDTH + 5, 30, slider);
    
    this->slider
    ->set_color(0x5836);   
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
draw(){
    tft->loadFont(LATIN);
    for (uint8_t i=0; i < NUMBER_OF_KEYPAD_BUTTONS; i++){
        buttons[i]->draw(true);
    }
    slider->draw(true);
    tft->unloadFont();
}

void 
Keypad::
re_draw(uint8_t idx)
{
    // slider
    if (idx == 0){
        return;
    }
    tft->loadFont(LATIN);
    buttons[idx-1]->draw(true);
    tft->unloadFont();
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
    delete slider;
}