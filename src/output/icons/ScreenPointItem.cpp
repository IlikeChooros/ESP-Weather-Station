#include "ScreenPointItem.h"

ScreenPointItem::ScreenPointItem(TFT_eSPI *tft, uint16_t x, uint16_t y, uint16_t bg_c)
{
    this->_tft = tft;
    this->x = x;
    this->y = y;
    this->bg_c = bg_c;
    this->colors = new uint16_t [3];
    colors[0] = TFT_WHITE;
    colors[1] = GREY_SCREEN_POINT;
    colors[2] = DARK_SCREEN_POINT;
}
//--------------------------------------
// currentX,Y as 1,2,3,...
//--------------------------------------
void ScreenPointItem::draw(uint8_t numberOfAllInX, uint8_t numberOfAllInY, uint8_t currentX, uint8_t currentY)
{
    _tft->drawRect(x,y,3*SIZE_POINT,SIZE_POINT*0.4f,bg_c);
    int8_t itemsOnRight = numberOfAllInX - currentX;
    int8_t itemsOnLeft = currentX - 1;
    int8_t itrR = 1;

    if (itemsOnLeft > 2)
    {
        itemsOnLeft = 2;
    }
    if (itemsOnRight > 2)
    {
        itemsOnRight = 2;
    }

    uint8_t counter = 0;

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