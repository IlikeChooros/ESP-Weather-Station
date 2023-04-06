#include "CustomButton.h"

namespace 
custom_button
{
    void 
    do_nothing(
        TFT_eSPI*, 
        uint16_t, 
        uint16_t, 
        uint16_t, 
        uint16_t
    )
    {
        return;
    }

    void 
    do_nothing_wh(
        TFT_eSPI*, 
        uint16_t, 
        uint16_t, 
        uint16_t, 
        uint16_t,
        uint16_t
    )
    {
        return;
    }
} // custom_button


CustomButton::
CustomButton(
    TFT_eSPI* tft, 
    int16_t x, 
    int16_t y, 
    int16_t width, 
    int16_t height,
    uint16_t color
): TouchButton(x,y,width,height),
tft(tft), touch_color_(color) {
    this->color = color;
    set_draw(custom_button::do_nothing);
    set_draw_wh(custom_button::do_nothing_wh);
}

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
set_draw_wh(
    void(*drawing)(
        TFT_eSPI*, 
        uint16_t, 
        uint16_t, 
        uint16_t, 
        uint16_t,
        uint16_t
))
{
    this->drawing_funct_wh = drawing;
    return this;
}

CustomButton*
CustomButton::
touch_color(uint16_t color){
    this->touch_color_ = color;
    return this;
}

void
CustomButton::
draw(bool forceDraw)
{
    if (!forceDraw){
        return;
    }
    draw_(color);
}

void
CustomButton::
on_touch(){
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

    drawing_funct_wh(
        tft,
        x,y,
        width,
        height,
        color
    );
   
}
