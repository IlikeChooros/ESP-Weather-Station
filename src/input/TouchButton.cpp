#include "TouchButton.h"

TouchButton::TouchButton(int16_t x, int16_t y, int16_t width, int16_t height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

void TouchButton::set_on_press(void(*func_on_press)(void))
{
    this->on_press = func_on_press;
}

bool TouchButton::check(int16_t x, int16_t y)
{
    if( (x >= this->x) && (x <= this->x + height))
    {
        if ((y>= this->y) && (y <= this->y + height))
        {
            this->on_press();
            return true;
        }
    }
    return false;
}