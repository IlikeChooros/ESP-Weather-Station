#include "TouchScreen.h"

void do_nothing()
{
    return;
}

TouchScreen::TouchScreen(TFT_eSPI* tft, uint16_t* data)
{
    this->_tft = tft;
    _tft->setTouch(data);
    max_interval = 20;
    time_passed = 0;
    _state = false;
    _lastState = false;
    _lastDebounceTime = 0;


    this->on_down(do_nothing);
    this->on_left(do_nothing);
    this->on_right(do_nothing);
    this->on_up(do_nothing);
}

void TouchScreen::read()
{
    uint16_t x=0,y=0;
    bool state = _tft->getTouch(&x,&y);

    if (_lastState!=state)
    {
        _lastDebounceTime = millis();
    }

    if (_state!=state && (millis()-_lastDebounceTime)> max_interval)
    {
        _state=state;
        if (y>TOUCH_VAL && y < 240 - TOUCH_VAL)
        {
            if (x<100)
            {
                this->_on_left();
            }
            else if(x>320 - TOUCH_VAL)
            {
                this->_on_right();
            }
        }
        else if (x>TOUCH_VAL && x < 320 - TOUCH_VAL)
        {
            if (y < TOUCH_VAL)
            {
                this->_on_up();
            }
            else if(y > 240 - TOUCH_VAL)
            {
                this->_on_down();
            }
        }
    }
    _lastState = state;
}

bool TouchScreen::isVertical(int16_t d_x, int16_t d_y)
{
    if (abs(d_x) < MIN_HORIZONTAL)
    {
        return abs(d_y) > VERTICAL_VAL;
    }
    return false;
}

bool TouchScreen::isHorizontal(int16_t d_x, int16_t d_y)
{
    if (abs(d_y) < MIN_VERTICAL)
    {
        return abs(d_x) > HORIZONTAL_VAL;
    }
    return false;
}

void TouchScreen::on_left(void(*left)(void))
{
    this->_on_left = left;
}

void TouchScreen::on_right(void(*right)(void))
{
    this->_on_right = right;
}

void TouchScreen::on_down(void(*down)(void))
{
    this->_on_down = down;
}

void TouchScreen::on_up(void(*up)(void))
{
    this->_on_up = up;
}