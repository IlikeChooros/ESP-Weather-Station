#include "ScreenPointItem.h"

ScreenPointItem::ScreenPointItem(
    TFT_eSPI *tft, 
    uint16_t x, 
    uint16_t y, 
    uint16_t bg_c,
    uint8_t size
): _tft(tft), x(x), y(y), bg_c(bg_c), prev_lenght(3),
colors(get_colors_grey_fade(3)), size(size) {}

ScreenPointItem::
~ScreenPointItem(){
    delete [] colors;
}

void
ScreenPointItem::draw(
    uint8_t numberOfAllInX,
    uint8_t numberOfAllInY, 
    uint8_t currentX, 
    uint8_t currentY
)
{
    // _tft->drawRect(x, y, numberOfAllInX * size,size * 0.4f, bg_c);
    int8_t itemsOnRight = numberOfAllInX - currentX;
    int8_t itemsOnLeft = currentX - 1;
    int8_t itrR = 1;
    uint16_t st_x;

    st_x = x - (float)((numberOfAllInX-1)/2 * size);

    uint8_t counter = 0;

    if (prev_lenght != numberOfAllInX){
        delete [] colors;
        colors = get_colors_grey_fade(numberOfAllInX);
    }

    while(itemsOnLeft >= 0){
        _tft->fillSmoothCircle(st_x + size * counter, y, size * 0.3f, colors[itemsOnLeft], bg_c);
        itemsOnLeft--;
        counter++;
    }

    while(itrR <= itemsOnRight){
        _tft->fillSmoothCircle(st_x + size * counter, y, size * 0.3f, colors[itrR], bg_c);
        itrR++;
        counter++;
    }
}