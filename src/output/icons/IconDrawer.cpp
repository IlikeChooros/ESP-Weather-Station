#include "IconDrawer.h"

Icon::Icon(TFT_eSPI *tft, uint16_t x, uint16_t y, uint8_t size, uint16_t background_color)
{
    this->size = size;
    this->x = x;
    this->y = y;
    this->_tft = tft;
    this->background_color = background_color;
}

void Sunny::draw()
{
    _tft->fillRect(x,y,size,size,background_color);
    _tft->fillSmoothCircle(x+size/2, y+size/2, size/2 * 0.50f, SUNNY, background_color);

    // 
    uint16_t 
        xc = x + size/2,
        yc = y + size/2,
        Ax = 0.85f * size + x,
        Ay = y + size/2,
        Bx = 0.95f*size + x,
        By = Ay; 

    for (uint8_t i=0; i<9; i++)
    {
        float angle = i * PI/4;
        uint16_t
            ax = (Ax - xc) * cosf(angle) - (Ay - yc) * sinf(angle) + xc,
            ay = (Ax - xc) * sinf(angle) + (Ay - yc) * cosf(angle) + yc,
            bx = (Bx - xc) * cosf(angle) - (By - yc) * sinf(angle) + xc,
            by = (Bx - xc) * sinf(angle) + (By - yc) * cosf(angle) + yc;

        _tft->drawWideLine(ax, ay,bx , by, 0.05f * size, SUNNY, background_color);
    }

}