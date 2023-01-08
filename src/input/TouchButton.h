#ifndef TOUCH_BUTTON_H
#define TOUCH_BUTTON_H

#include "Arduino.h"

#define X 0
#define Y 1
#define WID 2
#define HEI 3

class TouchButton
{
    int16_t* data;
    void (*on_press)();
    public:
    TouchButton(int16_t x, int16_t y, int16_t width, int16_t height);
    void set_on_press(void(*)(void));
    int16_t* get_data();
    void check(int16_t x, int16_t y);
    void clear();
};

#endif