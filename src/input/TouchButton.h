#pragma once

#include "Arduino.h"

#define X 0
#define Y 1
#define WID 2
#define HEI 3
#define IDX 4

class
TouchButton
{

    public:
    /**
     * @brief Virtual class that helps with creating personalized touchscreen button
     * 
     * @param x 
     * @param y 
     * @param width 
     * @param height 
     */
    explicit 
    TouchButton(
        int16_t x, 
        int16_t y, 
        int16_t width, 
        int16_t height
    );

    /**
     * @brief This function will be called before on_touch(), after the button area gets touched
     * 
     */
    void 
    set_on_press(void(*)(void));

    /**
     * @brief Checks wheter the button is touched
     * 
     * @param x 
     * @param y 
     * @return true 
     * @return false 
     */
    bool 
    check(
        int16_t x, 
        int16_t y
    );

    /**
     * @brief Set the color
     * 
     * @param color 
     */
    void 
    set_color(uint16_t color);

    virtual void 
    draw(bool forceDraw) = 0;
    
    virtual void 
    on_touch() = 0;
    

    protected:
    uint16_t color;
    int16_t x;
    int16_t y;
    int16_t width;
    int16_t height;
    void (*on_press)();

};
