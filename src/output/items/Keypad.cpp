#include "Keypad.h"

//-----------------------
// button_data -> 12 buttons
// 3:3:4
// idx = 0 -> left_slider
// idx = 13 -> right_slider
Keypad::Keypad(TFT_eSPI* tft, String* button_data, String left_slider, String right_slider)
{
    buttons = new TouchButton*[NUMBER_OF_KEYPAD_BUTTONS];
    buttons[0] = new KeypadButton(tft, 0, STARTING_Y, KEYPAD_BUTTON_WIDTH-10, 200-STARTING_Y, left_slider);
    buttons[NUMBER_OF_KEYPAD_BUTTONS-1] = new KeypadButton(
        tft, 310 - KEYPAD_BUTTON_WIDTH,
        STARTING_Y, KEYPAD_BUTTON_WIDTH-10,
        200 - STARTING_Y, right_slider);

    for (uint8_t y=0; y<3; y++)
    {
        for(uint8_t x=0; x<4; x++)
        {
            buttons[y*4+x+1] = new KeypadButton(tft,
            (x+1)*(KEYPAD_BUTTON_WIDTH+5),
            (y+1)*(KEYPAD_BUTTON_HEIGHT+2),
            KEYPAD_BUTTON_WIDTH,
            KEYPAD_BUTTON_HEIGHT,
            button_data[y*4 + x]);
        }
    }
}

//------------------------
// Idx = <1;12>
//------------------------
void Keypad::set_on_press(void(*on_press)(void), uint8_t idx)
{
    buttons[idx]->set_on_press(on_press);
}

void Keypad::draw()
{
    for (uint8_t i=0; i<NUMBER_OF_KEYPAD_BUTTONS; i++)
    {
        buttons[i]->draw();
    }
}

void Keypad::check(int16_t* pos)
{
    for (uint8_t i=0; i<NUMBER_OF_KEYPAD_BUTTONS; i++)
    {
        buttons[i]->check(pos[0], pos[1]);
    }
}