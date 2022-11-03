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
    drawSun(_tft, x, y, size, SUNNY, background_color);
}

void Moon::draw()
{
    _tft->fillRect(x,y,size,size,background_color);

    drawMoon(_tft,x,y,size, MOON, background_color);
}

void FewCloudsDay::draw()
{
    _tft->fillRect(x,y,size,size,background_color);

    drawSun(_tft, x + 0.38f*size, y, size*0.6f, SUNNY, background_color);
    drawCloud(_tft, x, y + 0.28f*size, 0.9f*size, CLOUDY, LIGHT_DARK_CLOUDS, background_color);
}

void FewCloudsNight::draw()
{
    _tft->fillRect(x,y,size,size,background_color);

    drawMoon(_tft, x + 0.5f*size, y, size*0.4f, MOON, background_color);
    drawCloud(_tft, x, y + 0.28f*size, 0.9f*size, CLOUDY, LIGHT_DARK_CLOUDS, background_color);
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

    uint16_t ax = x + 0.3f*size,
            ay = y+0.45f*size,
            bx = ax - 0.07f*size,
            by = ay + 0.08f*size;

    for (uint8_t a = 0;a<3;a++)
    {
        draw_droplet(ax,ay,bx,by, 0.03f*size);
        ax += 0.2f*size;
        bx += 0.2f*size;
    }


    ay += 0.11f*size;
    ax = x+ 0.3f*size;
    bx = ax - 0.07f*size,
    by = ay + 0.08f*size;
    for (uint8_t a = 0;a<3;a++)
    {
        draw_droplet(ax,ay,bx,by, 0.03f*size);
        ax += 0.2f*size;
        bx += 0.2f*size;
    }
}

void Rain::draw_droplet(uint16_t ax, uint16_t ay,uint16_t bx, uint16_t by ,uint16_t size)
{
    //_tft->fillCircle(x + 0.5f*size, y + 0.7f*size, 0.25f*size, WATER);
    //_tft->fillTriangle(x+ 0.5f*size, y + 0.1f*size,    x+ 0.27f*size, y + 0.6*size,    x + 0.75f*size, y+ 0.6f * size, WATER);

    _tft->drawWideLine(ax,ay,bx,by,size, WATER, background_color);
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

void Snow::draw()
{
    _tft->fillRect(x,y,size,size,background_color);

    drawCloud(_tft, x,y, size, CLOUDY, LIGHT_DARK_CLOUDS, background_color);

    drawSnowflake(_tft, x + 0.3f*size, y+0.4f*size, size*0.4f, background_color, SNOW_FLAKE, WATER);
    //drawSnowflake(_tft, x+0.1f*size, y, size*0.8f, CLOUDY, SNOW_FLAKE, WATER);
}

void MistNight::draw()
{
    _tft->fillRect(x,y,size,size,background_color);

    drawMoon(_tft, x + 0.3f*size, y + 0.1f*size, size*0.5f, MOON, background_color);
    drawMist(_tft, x+0.1f*size, y+ 0.2f*size, size*0.8f,MIST, background_color);
}

void MistDay::draw()
{
    _tft->fillRect(x,y,size,size,background_color);

    drawSun(_tft, x + 0.22f*size, y + 0.13f*size, size*0.55f, SUNNY, background_color);
    drawMist(_tft, x+0.1f*size, y+ 0.17f*size, size*0.8f,MIST, background_color);
}

