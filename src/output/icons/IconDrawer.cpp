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
    // circles on the right and left
    _tft->fillSmoothCircle(x+0.2f*size, y + size*0.24f, 0.14f*size, CLOUDY, background_color);
    _tft->fillSmoothCircle(x+0.8f*size, y + size*0.24f, 0.14f*size, CLOUDY, background_color);

    // circle on the middle left
    _tft->fillSmoothCircle(x+0.4f*size, y+0.2f*size, 0.18f*size, CLOUDY, background_color);

    // circle on the middle right
    _tft->fillSmoothCircle(x+0.65f*size, y+0.15f*size, 0.15f*size, CLOUDY, CLOUDY);

    // rect, the filler
    _tft->fillRoundRect(x+0.2f*size, y+size*0.1f, 0.6f * size, 0.3f * size, 0.05f*size, CLOUDY);
}

void ManyClouds::draw()
{
    _tft->fillRect(x,y,size,size,background_color);

    //on right
    draw_cloud(x+0.3f*size,y+0.2f*size, 0.5f*size, MIDDLE_DARK_CLOUDS);

    //on left
    draw_cloud(x,y+0.25f*size, 0.4f*size, LIGHT_DARK_CLOUDS);

    //bottom
    draw_cloud(x, y+0.3f*size, 0.75f*size, CLOUDY);
}

void ManyClouds::draw_cloud(uint16_t x, uint16_t y, uint16_t size, uint16_t color)
{
    //Cloud drawing
    // circles on the right and left
    _tft->fillSmoothCircle(x+0.2f*size, y + size*0.24f, 0.14f*size, color, background_color);
    _tft->fillSmoothCircle(x+0.8f*size, y + size*0.24f, 0.14f*size, color, background_color);

    // circle on the middle left
    _tft->fillSmoothCircle(x+0.4f*size, y+0.2f*size, 0.18f*size, color, background_color);

    // circle on the middle right
    _tft->fillSmoothCircle(x+0.65f*size, y+0.15f*size, 0.15f*size, color, color);

    // rect, the filler
    _tft->fillRoundRect(x+0.2f*size, y+size*0.1f, 0.6f * size, 0.3f * size, 0.05f*size, color);
}

void Storm::draw()
{
    _tft->fillRect(x,y,size,size,background_color);
    //Cloud drawing

    // circles on the right and left
    _tft->fillSmoothCircle(x+0.2f*size, y + size*0.24f, 0.14f*size, DARK_CLOUDS, background_color);
    _tft->fillSmoothCircle(x+0.8f*size, y + size*0.24f, 0.14f*size, DARK_CLOUDS, background_color);

    // circle on the middle left
    _tft->fillSmoothCircle(x+0.4f*size, y+0.2f*size, 0.18f*size, DARK_CLOUDS, background_color);

    // circle on the middle right
    _tft->fillSmoothCircle(x+0.65f*size, y+0.15f*size, 0.15f*size, DARK_CLOUDS, DARK_CLOUDS);

    // rect, the filler
    _tft->fillRoundRect(x+0.2f*size, y+size*0.1f, 0.6f * size, 0.3f * size, 0.05f*size, DARK_CLOUDS);

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


    bx = ax;
    by = ay;
    ax -= 0.1f*size;
    
    _tft->drawWideLine(ax, ay, bx, by, 0.045f*size, SUNNY, background_color);
}


void Rain::draw()
{
    _tft->fillRect(x,y,size,size,background_color);
    //Cloud drawing

    // circles on the right and left
    _tft->fillSmoothCircle(x+0.2f*size, y + size*0.24f, 0.14f*size, LIGHT_DARK_CLOUDS, background_color);
    _tft->fillSmoothCircle(x+0.8f*size, y + size*0.24f, 0.14f*size, LIGHT_DARK_CLOUDS, background_color);

    // circle on the middle left
    _tft->fillSmoothCircle(x+0.4f*size, y+0.2f*size, 0.18f*size, LIGHT_DARK_CLOUDS, background_color);

    // circle on the middle right
    _tft->fillSmoothCircle(x+0.65f*size, y+0.15f*size, 0.15f*size, LIGHT_DARK_CLOUDS, LIGHT_DARK_CLOUDS);

    // rect, the filler
    _tft->fillRoundRect(x+0.2f*size, y+size*0.1f, 0.6f * size, 0.3f * size, 0.05f*size, LIGHT_DARK_CLOUDS);


    draw_droplet(x + 0.6f*size, y+ 0.5f*size, 0.15f*size);
    draw_droplet(x + 0.3f*size, y+0.4f*size, 0.15f*size);
    draw_droplet(x + 0.4f*size, y+0.5f*size, 0.15f*size);
    draw_droplet(x+0.5f*size, y+ 0.45f*size, 0.15f*size);
}

void Rain::draw_droplet(uint16_t x, uint16_t y, uint16_t size)
{
    _tft->fillCircle(x + 0.5f*size, y + 0.7f*size, 0.25f*size, WATER);
    _tft->fillTriangle(x+ 0.5f*size, y + 0.1f*size,    x+ 0.25f*size, y + 0.6*size,    x + 0.75f*size, y+ 0.6f * size, WATER);
}