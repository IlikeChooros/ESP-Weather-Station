#pragma once

#include <TFT_eSPI.h>
#include <SPI.h>

#include "TouchButton.h"
#include "../data_structures/Point.h"

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
    TouchScreen(
        TFT_eSPI *tft ,
        uint16_t* touchData
    );
    /**
     * @brief Will read the TFT screen, if touched, based on the screen fragmentation, the following fuctions will be called:
     * on_left, on_right, on_up, on_down, if they werent set, nothing will happen
     */
    void 
    read();

    /**
     * @brief Reads for pixel coordinates of touch
     * 
     * @return Point* if touch screen wasnt touched Point* = 0, else it was allocated via operator new, so it must be deleted
     */
    Point* 
    read_touch();

    /**
     * @brief Set function to be called when screens is touched on the left side
     * 
     * @return TouchScreen* pointer to this object
     */
    TouchScreen* 
    on_left(void(*)(void));

    /**
     * @brief Set function to be called when screens is touched on the right side
     * 
     * @return TouchScreen* pointer to this object
     */
    TouchScreen* 
    on_right(void(*)(void));

    /**
     * @brief Set function to be called when screens is touched on the upper side
     * 
     * @return TouchScreen* pointer to this object
     */
    TouchScreen* 
    on_up(void(*)(void));

    /**
     * @brief Set function to be called when screens is touched on the down side
     * 
     * @return TouchScreen* pointer to this object
     */
    TouchScreen*
    on_down(void(*)(void));

    /**
     * @brief When screen isnt touched for at least 1 minute, the parsed function will be activated, only once in the 'sleep mode'
     * 
     * @return TouchScreen* pointer to this object
     */
    TouchScreen*
    on_sleep(void(*)());

    /**
     * @brief When in 'sleep mode', after touching the screen parsed function will be activated, note that other on touch function wont be activaed:
     * on_left, on_right etc.
     * 
     * @return TouchScreen* pointer to this object
     */
    TouchScreen* 
    on_wakeup(void(*)());

};