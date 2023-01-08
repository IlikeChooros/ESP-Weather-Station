#ifndef TOUCH_BUTTON_H
#define TOUCH_BUTTON_H

#include "Arduino.h"

#define X 0
#define Y 1
#define WID 2
#define HEI 3
#define IDX 4

class TouchButton
{
    public:
    explicit TouchButton(int16_t x, int16_t y, int16_t width, int16_t height);
    void set_on_press(void(*)(void));
    bool check(int16_t x, int16_t y);
    virtual void draw() = 0;
    virtual String get_str() = 0;
    virtual int16_t get_int() = 0;

    protected:
    int16_t x;
    int16_t y;
    int16_t width;
    int16_t height;
    void (*on_press)();
};

#endif