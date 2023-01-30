#include "Keypad.h"

Keypad::Keypad(
    TFT_eSPI* tft, 
    String* button_data, 
    String left_slider, 
    String right_slider
)
{
    sliders = new KeypadButton* [2]{
        new KeypadButton(tft, 0, STARTING_Y+10, KEYPAD_BUTTON_WIDTH, 200-STARTING_Y, left_slider),
        new KeypadButton(
        tft, 320 - KEYPAD_BUTTON_WIDTH,
        STARTING_Y+10, KEYPAD_BUTTON_WIDTH,
        200 - STARTING_Y, right_slider)
    };

    sliders[0]->set_wrap();
    sliders[1]->set_wrap();

    buttons = new KeypadButton*[NUMBER_OF_KEYPAD_BUTTONS];
    buttons[NUMBER_OF_KEYPAD_BUTTONS-1] = new KeypadButton(
        tft, 70, 207, 180, 30, " "
    );
    

    for (uint8_t y=0; y<3; y++)
    {
        for(uint8_t x=0; x<8; x++)
        {
            buttons[y*8+x] = new KeypadButton(tft,
            (x+1)*(KEYPAD_BUTTON_WIDTH+2),
            y*(KEYPAD_BUTTON_HEIGHT+2)+STARTING_Y+20,
            KEYPAD_BUTTON_WIDTH,
            KEYPAD_BUTTON_HEIGHT,
            button_data[y*8 + x]);
        }
    }
}

String 
Keypad::
get_button_str(uint8_t idx)
{
    return buttons[idx]->get_str();
}

void Keypad::set_on_press(void(*on_press)(void), uint8_t idx)
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
draw()
{
    for (uint8_t i=0; i<NUMBER_OF_KEYPAD_BUTTONS; i++)
    {
        buttons[i]->draw();
    }
    sliders[0]->draw();
    sliders[1]->draw();
}

void 
Keypad::
re_draw(uint8_t idx)
{
    if (idx == 0)
    {
        sliders[0]->draw();
        return;
    }
    if (idx == NUMBER_OF_KEYPAD_BUTTONS+1)
    {
        sliders[1]->draw();
        return;
    }
    buttons[idx-1]->draw();
}

int8_t 
Keypad::
check(Point* pos)
{
    for (uint8_t i=0; i<NUMBER_OF_KEYPAD_BUTTONS; i++)
    {
        if (buttons[i]->check(pos->x, pos->y))
        {
            return i+1;
        }
    }

    if (sliders[0]->check(pos->x, pos->y))
    {
        return 0;
    }
    if (sliders[1]->check(pos->x, pos->y))
    {
        return NUMBER_OF_KEYPAD_BUTTONS+1;
    }

    return -1;
}

void 
Keypad::
clear()
{
    for (uint8_t i=0; i<NUMBER_OF_KEYPAD_BUTTONS; i++)
    {
        delete buttons[i];
    }
    delete [] buttons;
}