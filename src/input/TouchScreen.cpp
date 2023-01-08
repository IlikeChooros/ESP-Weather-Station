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
        //Serial.println("TOUCHING");
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
                //Serial.println("LEFT");
                //Serial.println("");
                this->_on_left();
            }
            else{
                //Serial.println("DOWN");
                //Serial.println("");
                this->_on_down();
            }
        }
        else{
            if ( y < -0.75f*x + 240)
            {
                //Serial.println("UP");
                //Serial.println("");
                this->_on_up();
            }
            else{
                //Serial.println("RIGHT");
                //Serial.println("");
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

//-----------------------------------
// Buttons must be alread initialized
//-----------------------------------
void TouchScreen::load_buttons(TouchButton** buttons, uint8_t number_of_buttons)
{
    this->buttons = buttons;
    this->number_of_buttons = number_of_buttons;
}

void TouchScreen::read_buttons()
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


        for (uint8_t i=0;i<number_of_buttons;i++)
        {
            buttons[i]->check(x,y);
        }
    }
    _lastState = state;
}