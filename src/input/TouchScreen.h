#ifndef TOUCH_SCREEN_H
#define TOUCH_SCREEN_H

#include <TFT_eSPI.h>
#include <SPI.h>

#include "TouchButton.h"

#define VERTICAL_VAL 15
#define HORIZONTAL_VAL 20

#define MIN_HORIZONTAL 30
#define MIN_VERTICAL 25

#define TOUCH_VAL 100 

#define SLEEP_TIME 60000

class TouchScreen
{
    TFT_eSPI* _tft;
    
    uint16_t max_interval;

    TouchButton** buttons;
    uint8_t number_of_buttons;

    bool _lastState;
    bool _state;
    bool isAsleep;

    uint64_t _lastDebounceTime;

    void (*_on_left)();
    void (*_on_right)();
    void (*_on_up)();
    void (*_on_down)();
    void (*_on_sleep)();
    void (*_on_wakeup)();

    public:
    TouchScreen(TFT_eSPI *tft ,uint16_t* touchData);
    void read();
    int16_t* read_touch();
    void on_left(void(*)(void));
    void on_right(void(*)(void));
    void on_up(void(*)(void));
    void on_down(void(*)(void));
    void on_sleep(void(*)());
    void on_wakeup(void(*)());
};



#endif