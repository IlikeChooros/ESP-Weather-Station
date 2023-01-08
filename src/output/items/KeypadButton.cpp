#include "KeypadButton.h"

void KeypadButton::draw()
{
    tft->setTextSize(1);
    tft->drawCentreString(name, x+width/2, y, 2);
}

String KeypadButton::get_str()
{
    return this->name;
}