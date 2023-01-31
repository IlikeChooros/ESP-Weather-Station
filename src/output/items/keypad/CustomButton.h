#pragma once

#include "../../../input/TouchButton.h"

#include "../../icons/button_draw.h"

#include "TFT_eSPI.h"
#include "SPI.h"

class
CustomButton: public TouchButton
{
    TFT_eSPI *tft;

    uint16_t touch_color_;

    void (*drawing_funct)(
        TFT_eSPI*, 
        uint16_t, 
        uint16_t, 
        uint16_t, 
        uint16_t
    );

    void
    draw(uint16_t color);

public:
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
    }


    /**
     * @brief Set drawing fuction
     * 
     * @return CustomButton* pointer to this object
     */
    CustomButton*
    set_draw(
        void(*drawing)(
            TFT_eSPI*, 
            uint16_t, 
            uint16_t, 
            uint16_t, 
            uint16_t
    ));

    /**
     * @brief Set color change when button is touched
     * 
     * @param color rgb color in rgb565 format
     * @return CustomButton* pointer to this object
     */
    CustomButton*
    touch_color(uint16_t color);

    void 
    draw();

    /**
     * @brief Drawing fuction, activated when button is touched
     */
    void
    on_touch();
};