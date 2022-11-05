#ifndef TOUCH_SCREEN_H
#define TOUCH_SCREEN_H

#include <TFT_eSPI.h>
#include <SPI.h>

#define VERTICAL_VAL 25
#define HORIZONTAL_VAL 25

#define MIN_HORIZONTAL 25
#define MIN_VERTICAL 25

class TouchScreen
{
    TFT_eSPI* _tft;
    uint32_t time_passed;
    uint8_t counter;
    uint16_t max_interval;

    bool check_on_relase;
    bool checked;
    int16_t x_change;
    int16_t y_change;

    int16_t prev_x;
    int16_t prev_y;

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