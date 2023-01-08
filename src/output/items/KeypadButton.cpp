#include "KeypadButton.h"

KeypadButton::KeypadButton(TFT_eSPI* tft, int16_t x, int16_t y, int16_t width, int16_t height, String name)
{
    this->tft = tft;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->name = name;
}

void KeypadButton::set_button(void(*on_press)(void))
{
    button = new TouchButton(x,y,width,height);
    button->set_on_press(on_press);
}

void KeypadButton::draw()
{
    tft->drawCentreString(name, x+width/2, y, 2);
}

String KeypadButton::get_name()
{
    return this->name;
}