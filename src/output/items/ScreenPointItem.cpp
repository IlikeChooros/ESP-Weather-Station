#include "ScreenPointItem.h"

ScreenPointItem::ScreenPointItem(
    TFT_eSPI *tft, 
    uint16_t x, 
    uint16_t y, 
    uint16_t bg_c
)
{
    this->_tft = tft;
    this->x = x;
    this->y = y;
    this->bg_c = bg_c;
    this->prev_lenght = 0;
    colors = get_colors_grey_fade(3);
}


void
ScreenPointItem::draw(
    uint8_t numberOfAllInX,
    uint8_t numberOfAllInY, 
    uint8_t currentX, 
    uint8_t currentY
)
{
    _tft->drawRect(x,y,numberOfAllInX*SIZE_POINT,SIZE_POINT*0.4f,bg_c);
    int8_t itemsOnRight = numberOfAllInX - currentX;
    int8_t itemsOnLeft = currentX - 1;
    int8_t itrR = 1;

    uint8_t counter = 0;

    if (prev_lenght != numberOfAllInX)
    {
        delete [] colors;
        colors = get_colors_grey_fade(numberOfAllInX);
    }

    while(itemsOnLeft >= 0)
    {
        this->_tft->fillSmoothCircle(x + SIZE_POINT*counter,y,SIZE_POINT*0.3f,colors[itemsOnLeft], bg_c);
        itemsOnLeft--;
        counter++;
    }

    while(itrR <= itemsOnRight)
    {
        this->_tft->fillSmoothCircle(x + SIZE_POINT*counter,y,SIZE_POINT*0.3f,colors[itrR], bg_c);
        itrR++;
        counter++;
    }
}