#include "InputField.h"

InputField::InputField(
    TFT_eSPI* tft, 
    int16_t x, 
    int16_t y, 
    int16_t width, 
    int16_t height
)
{
    this->tft = tft;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->input = "";
}

void 
InputField::
draw(bool forceDraw)
{
    if(!forceDraw)
    {
        return;
    }
    tft->setTextSize(2);
    tft->setTextFont(2);
    tft->setTextColor(TFT_WHITE);

    tft->fillRect(x,y,width,height, INPUT_FIELD_BG);
    tft->drawRect(x,y,width,height, TFT_WHITE);

    tft->setCursor(x,y);

    String temp;
    if (this->input.length()<14)
    {
        temp = input;
    }
    else{
        temp = input.substring(input.length()-13,input.length());
    }
    tft->print(temp);
}


void 
InputField::
add_input(
    String input
)
{
    this->input += input;
    draw(true);
}

String 
InputField::
get_input()
{
    return this->input;
}

void 
InputField::
del()
{
    if (input == "" || input.length() == 0)
    {
        return;
    }
    this->input.remove(input.length()-1);
    draw(true);
}


