#ifndef TOUCH_SCREEN_H
#define TOUCH_SCREEN_H

#include <TFT_eSPI.h>
#include <SPI.h>

class TouchScreen
{
    TFT_eSPI* _tft;
    uint32_t time_passed;
    uint8_t counter;
    uint16_t max_interval;

    int16_t x_change;
    int16_t y_change;

    int16_t prev_x;
    int16_t prev_y;


    void (*_on_left)();
    void (*_on_right)();
    void (*_on_up)();
    void (*_on_down)();
    void do_nothing();
    public:
    TouchScreen(TFT_eSPI *tft ,uint16_t* touchData);
    void read();

    void on_left(void(*)(void));
    void on_right(void(*)(void));
    void on_up(void(*)(void));
    void on_down(void(*)(void));
};



#endif