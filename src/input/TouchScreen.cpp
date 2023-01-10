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

        // if this is an realse, then igonre
        if (!state)
        {
            _lastState = state;
            return;
        }

        // dividing screen to 4 triangles
        if (y > 0.75f*x)
        {
            if ( y < -0.75f*x + 240)
            {
                this->_on_left();
            }
            else{
                this->_on_down();
            }
        }
        else{
            if ( y < -0.75f*x + 240)
            {
                this->_on_up();
            }
            else{
                this->_on_right();
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

int16_t* TouchScreen::read_touch()
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

        // if this is an realse, then igonre
        if (!state)
        {
            _lastState = state;
            return 0;
        }

        return new int16_t [2] {x,y};
    }
    _lastState = state;
    return 0;
}