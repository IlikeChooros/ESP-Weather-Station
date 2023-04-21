#line 1 "c:\\Users\\pawel\\arduino\\ESP-Weather-Station\\src\\output\\items\\digits\\DigitObject.cpp"
#include "DigitObject.h"

void 
DigitObject::
draw(
    int8_t digit, 
    bool forceDraw
)
{
    if (!forceDraw && digit == prevDigit)
    {
        return;
    }
    currentDigit = digit;

    this->tft->setTextSize(size);
    // Clearing previous number
    this->tft->setTextColor(bg_c);
    this->tft->drawNumber(prevDigit, x,y,font);
    // Drawing new one
    this->tft->setTextColor(TFT_WHITE);
    this->tft->drawNumber(currentDigit, x, y, font);

    prevDigit = currentDigit;
}
void 
DigitObject::
set_digit(
    int8_t digit
)
{
    prevDigit = currentDigit;
    currentDigit = digit;
}

void 
DigitObject::
set_x_y(
    int16_t x, 
    int16_t y
)
{
    this->x = x;
    this->y = y;
}
