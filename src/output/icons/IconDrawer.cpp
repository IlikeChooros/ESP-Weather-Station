#include "IconDrawer.h"

Icon::Icon(TFT_eSPI *tft, uint16_t x, uint16_t y, uint8_t size, uint16_t background_color)
{
    this->size = size;
    this->x = x;
    this->y = y;
    this->_tft = tft;
    this->background_color = background_color;
}

void Sun::draw()
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

void Clouds::draw()
{
    _tft->fillRect(x,y,size,size,background_color);

    //Cloud drawing

    drawCloud(_tft, x,y,size, CLOUDY, LIGHT_DARK_CLOUDS,background_color);
}

void ManyClouds::draw()
{
    _tft->fillRect(x,y,size,size,background_color);

    //on right
    drawCloud(_tft,x+0.3f*size,y+0.2f*size, 0.5f*size, MIDDLE_DARK_CLOUDS, DARK_CLOUDS,background_color);

    //on left
    drawCloud(_tft, x,y+0.25f*size, 0.4f*size, LIGHT_DARK_CLOUDS, MIDDLE_DARK_CLOUDS,background_color);

    //bottom
    drawCloud(_tft, x, y+0.3f*size, 0.75f*size, CLOUDY, LIGHT_DARK_CLOUDS,background_color);
}

void Storm::draw()
{
    _tft->fillRect(x,y,size,size,background_color);
    //Cloud drawing
    drawCloud(_tft, x, y, size, ALMOST_DARK_CLOUDS, DARK_CLOUDS,background_color);

    // lightning drawing

    uint16_t ax = x+0.5f*size,
            ay = y + 0.2f*size,
            bx = ax - 0.05f*size,
            by = ay + 0.2f*size;
    _tft->drawWideLine(ax, ay, bx, by, 0.05f*size, SUNNY, background_color);

    ax = bx;
    ay = by;

    ax += 0.1f*size;
    by +=0.2f*size;
    bx += 0.05f*size;

    _tft->drawWideLine(ax, ay, bx, by, 0.03f*size, SUNNY, background_color);

    ax -= 0.02f*size;
    bx = ax;
    by = ay;
    ax -= 0.08f*size;
    
    _tft->drawWideLine(ax, ay, bx, by, 0.045f*size, SUNNY, SUNNY);
}


void Rain::draw()
{
    _tft->fillRect(x,y,size,size,background_color);
    //Cloud drawing

    drawCloud(_tft, x, y, size, CLOUDY,LIGHT_DARK_CLOUDS ,background_color);

    draw_droplet(x + 0.25f*size, y+ 0.53f*size, 0.08f*size);
    draw_droplet(x + 0.46f*size, y+ 0.48f*size, 0.1f*size);
    draw_droplet(x + 0.27f*size, y+0.41f*size, 0.1f*size);
    //draw_droplet(x + 0.55f*size, y+0.42f*size, 0.1f*size);
    draw_droplet(x + 0.64f*size, y+0.38f*size, 0.15f*size);
    draw_droplet(x + 0.73f*size, y+0.54f*size, 0.08f*size);
    //draw_droplet(x+0.58f*size, y+ 0.52f*size, 0.1f*size);
    draw_droplet(x+0.41f*size, y+ 0.58f*size, 0.1f*size);
    draw_droplet(x+0.61f*size, y+ 0.6f*size, 0.1f*size);
}

void Rain::draw_droplet(uint16_t x, uint16_t y, uint16_t size)
{
    _tft->fillCircle(x + 0.5f*size, y + 0.7f*size, 0.25f*size, WATER);
    //_tft->fillTriangle(x+ 0.5f*size, y + 0.1f*size,    x+ 0.27f*size, y + 0.6*size,    x + 0.75f*size, y+ 0.6f * size, WATER);
}


void BigRain::draw()
{
    _tft->fillRect(x,y,size,size,background_color);
    //Cloud drawing

    drawCloud(_tft, x, y, size, LIGHT_DARK_CLOUDS,MIDDLE_DARK_CLOUDS ,background_color);


    uint16_t ax = x + 0.3f*size,
            ay = y+0.45f*size,
            bx = ax - 0.15f*size,
            by = ay + 0.25f*size;

    for (uint8_t a = 0;a<3;a++)
    {
        _tft->drawWideLine(ax,ay,bx,by,0.03f*size, WATER, background_color);
        ax += 0.2f*size;
        bx += 0.2f*size;
    }
}