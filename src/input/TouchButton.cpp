#include "TouchButton.h"

TouchButton::TouchButton(int16_t x, int16_t y, int16_t width, int16_t height)
{
    data = new int16_t [4];
    data[X] = x;
    data[Y] = y;
    data[WID] = width;
    data[HEI] = height;
}

int16_t* TouchButton::get_data()
{
    return data;
}

void TouchButton::clear()
{
    delete [] this->data;
}

void TouchButton::set_on_press(void(*func_on_press)(void))
{
    this->on_press = func_on_press;
}

void TouchButton::check(int16_t x, int16_t y)
{
    if( (x >= data[X]) && (x <= data[X] + data[WID]))
    {
        if ((y>= data[Y]) && (y <= data[Y] + data[HEI]))
        {
            this->on_press();
        }
    }
}