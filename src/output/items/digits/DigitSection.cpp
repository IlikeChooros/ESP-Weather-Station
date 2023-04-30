#include "DigitSection.h"

DigitSection::DigitSection(
    TFT_eSPI *tft, 
    int16_t x, 
    int16_t y,
    int16_t bg_c, 
    bool putColonOnTheEnd
)
{
    this->tft = tft;
    this-> x = x;
    this-> y = y;
    this-> colon = putColonOnTheEnd;
    digitsObj = new DigitObject* [NUMBER_OF_DIGITS]{
        new DigitObject(tft, x, y, bg_c),
        new DigitObject(tft, x+DIGIT_WIDTH, y, bg_c)
    };

}

void 
DigitSection::
draw(
    uint8_t digits, 
    bool forceDraw
)
{
    digitsObj[LEFT_DIGIT]->draw(digits / 10, forceDraw);
    digitsObj[RIGHT_DIGIT]->draw(digits % 10, forceDraw);

    if(colon && forceDraw){
        tft->drawString(String(':'), x+2*DIGIT_WIDTH, y);
    }
}

void
DigitSection::
set_x(int16_t x)
{
    this->x = x;
    digitsObj[LEFT_DIGIT]->set_x_y(x, y);
    digitsObj[RIGHT_DIGIT]->set_x_y(x + DIGIT_WIDTH, y);
}