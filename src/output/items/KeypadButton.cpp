#include "KeypadButton.h"

void KeypadButton::draw()
{
    tft->setTextColor(TFT_WHITE);
    tft->setTextSize(2);
    tft->fillRect(x,y,width,height,color);
    tft->drawRect(x,y,width,height,TFT_LIGHTGREY);

    if (name == " ")
    {
        tft->drawCentreString("SPACE", x+width/2, y, 2);
        return;
    }

    if (wrap)
    {
        for (uint8_t i=0; i<name.length(); i++)
        {
            tft->setCursor(x+0.3f*width, y + i*25+height*0.1f);
            tft->print(name[i]);
        }
        return;
    }
    tft->drawCentreString(name, x+width/2, y, 2);
}

void KeypadButton::on_touch()
{
    tft->setTextColor(TFT_WHITE);
    tft->setTextSize(2);
    tft->fillRect(x,y,width,height,TFT_GREEN);
    tft->drawRect(x,y,width,height,TFT_LIGHTGREY);
    if (name == " ")
    {
        tft->drawCentreString("SPACE", x+width/2, y, 2);
        return;
    }
    tft->drawCentreString(name, x+width/2, y, 2);
}

String KeypadButton::get_str()
{
    return this->name;
}

void KeypadButton::set_wrap()
{
    this->wrap = true;
}