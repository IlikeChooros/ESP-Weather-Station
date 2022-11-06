#ifndef TOUCH_SCREEN_H
#define TOUCH_SCREEN_H

#include <TFT_eSPI.h>
#include <SPI.h>

#define VERTICAL_VAL 15
#define HORIZONTAL_VAL 20

#define MIN_HORIZONTAL 30
#define MIN_VERTICAL 25

#define TOUCH_VAL 100 

class TouchScreen
{
    TFT_eSPI* _tft;
    uint32_t time_passed;
    uint16_t max_interval;

    bool _lastState;
    bool _state;
    uint32_t _lastDebounceTime;

    bool isVertical(int16_t d_x, int16_t d_y);
    bool isHorizontal(int16_t d_x, int16_t d_y);

    void (*_on_left)();
    void (*_on_right)();
    void (*_on_up)();
    void (*_on_down)();
    public:
    TouchScreen(TFT_eSPI *tft ,uint16_t* touchData);
    void read();
    void on_left(void(*)(void));
    void on_right(void(*)(void));
    void on_up(void(*)(void));
    void on_down(void(*)(void));
};



#endif