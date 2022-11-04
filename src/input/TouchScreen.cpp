#include "TouchScreen.h"

TouchScreen::TouchScreen(TFT_eSPI* tft, uint16_t* data)
{
    this->_tft = tft;
    _tft->setTouch(data);
    max_interval = 100;
    time_passed = 0;
    counter = 0;


    prev_x = 0;
    prev_y = 0;
}

void TouchScreen::do_nothing()
{
    return;
}

void TouchScreen::read()
{
    uint16_t x=0,y=0;
    bool pressed = _tft->getTouch(&x,&y);

    if (pressed)
    {
        if (millis() - time_passed < max_interval)
        {
            if (counter)
            {
                x_change += (x - prev_x)/2;
                y_change += (y - prev_y)/2;
            }
            Serial.println("X: "+String(x)+"  Y: "+String(y) + "   C: "+String(counter) + " Y_CH: "+String(y_change) + "  X_CH: "+String(x_change));
            counter++;

            prev_x = x;
            prev_y = y;
        }
        else{
            counter = 0;
            y_change = 0;
            x_change = 0;
        }
        time_passed = millis();
    }
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