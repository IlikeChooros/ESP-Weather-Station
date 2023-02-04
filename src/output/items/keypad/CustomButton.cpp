#include "CustomButton.h"


CustomButton*
CustomButton::
set_draw(
    void(*drawing)(
        TFT_eSPI*, 
        uint16_t, 
        uint16_t, 
        uint16_t, 
        uint16_t
))
{
    this->drawing_funct = drawing;
    return this;
}

CustomButton*
CustomButton::
touch_color(uint16_t color)
{
    this->touch_color_ = color;
}

void
CustomButton::
draw(bool forceDraw)
{
    if (!forceDraw)
    {
        return;
    }
    draw_(color);
}

void
CustomButton::
on_touch()
{
    draw_(touch_color_);
}

void
CustomButton::
draw_(uint16_t color)
{
    drawing_funct(
        tft,
        x,y,
        width,
        color
    );
}
