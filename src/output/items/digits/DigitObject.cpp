#include "DigitObject.h"

DigitObject::DigitObject(
    TFT_eSPI *tft, 
    int16_t x, 
    int16_t y, 
    uint8_t size, 
    uint8_t font, 
    int16_t bg_c
)
{
    this->tft = tft;
    this->x = x;
    this->y = y;
    this->size = size;
    this->font = font;
    this->bg_c = bg_c;
    currentDigit = 0;
    prevDigit = 0;
}


void 
DigitObject::draw(
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
DigitObject::set_digit(
    int8_t digit
)
{
    prevDigit = currentDigit;
    currentDigit = digit;
}

void 
DigitObject::set_x_y(
    int16_t x, 
    int16_t y
)
{
    this->x = x;
    this->y = y;
}
