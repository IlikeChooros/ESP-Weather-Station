#include "DigitObject.h"

DigitObject::
DigitObject(
    TFT_eSPI* tft, 
    int16_t x, 
    int16_t y, 
    int16_t bg_c
): currentDigit(0), prevDigit(0),
tft(tft), x(x), y(y), bg_c(bg_c) {}

void 
DigitObject::
draw(
    int8_t digit, 
    bool forceDraw
)
{
    if (!forceDraw && digit == prevDigit){
        return;
    }
    currentDigit = digit;
    // Clearing previous number
    this->tft->setTextColor(bg_c, bg_c);
    this->tft->drawNumber(prevDigit, x,y);
    // Drawing new one
    this->tft->setTextColor(TFT_WHITE, bg_c);
    this->tft->drawNumber(currentDigit, x, y);
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
