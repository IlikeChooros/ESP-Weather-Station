#include "TouchScreen.h"

void do_nothing()
{
    return;
}

TouchScreen::TouchScreen(TFT_eSPI* tft, uint16_t* data)
{
    this->_tft = tft;
    _tft->setTouch(data);
    max_interval = 100;
    time_passed = 0;
    counter = 0;
    checked = false;
    check_on_relase = true;


    prev_x = 0;
    prev_y = 0;

    this->on_down(do_nothing);
    this->on_left(do_nothing);
    this->on_right(do_nothing);
    this->on_up(do_nothing);
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
            //Serial.println("X: "+String(x)+"  Y: "+String(y) + "   C: "+String(counter) + " Y_CH: "+String(y_change) + "  X_CH: "+String(x_change));
            counter++;

            prev_x = x;
            prev_y = y;

        }
        if(!check_on_relase)
        {
            check_on_relase = true;
        }
        time_passed = millis();
    }

    else if (check_on_relase && millis() - time_passed > max_interval)
    {
        if (counter > 5)
        {
            Serial.println("");
            if (isHorizontal(x_change, y_change))
            {
                if (x_change<0)
                {
                    this->_on_right();
                }
                else{
                    this->_on_left();
                }
            }

            else if (isVertical(x_change, y_change))
            {
                if (y_change < 0)
                {
                    this->_on_down();
                }
                else{
                    this->_on_up();
                }
            }
            //Serial.println(" C: "+String(counter) + " Y_CH: "+String(y_change) + "  X_CH: "+String(x_change));
            //Serial.println("");

            check_on_relase = false;
        }


        counter = 0;
        y_change = 0;
        x_change = 0;
    }
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