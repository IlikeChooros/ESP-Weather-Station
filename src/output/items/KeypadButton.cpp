#include "KeypadButton.h"

void KeypadButton::draw()
{
    tft->setTextColor(TFT_WHITE);
    tft->setTextSize(2);
    tft->fillRect(x,y,width,height,BUTTON_BG);
    tft->drawRect(x,y,width,height,TFT_LIGHTGREY);
    tft->drawCentreString(name, x+width/2, y, 2);
}

void KeypadButton::on_touch()
{
    tft->setTextColor(TFT_WHITE);
    tft->setTextSize(2);
    tft->fillRect(x,y,width,height,TFT_GREEN);
    tft->drawRect(x,y,width,height,TFT_LIGHTGREY);
    tft->drawCentreString(name, x+width/2, y, 2);
}

String KeypadButton::get_str()
{
    return this->name;
}