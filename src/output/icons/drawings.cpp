#include "drawings.h"

void  
drawCloud(
    TFT_eSPI *tft,
    uint16_t x, 
    uint16_t y, 
    uint16_t size, 
    uint16_t color,
    uint16_t fade_color,
    uint16_t background_color,
    uint16_t left_shade,
    uint16_t right_shade,
    uint16_t far_right_shade
)
{
    //Cloud drawing
    // circles on the right and left
    tft->fillSmoothCircle(x+0.2f*size, y + size*0.24f, 0.14f*size, color, background_color);
    tft->fillSmoothCircle(x+0.8f*size, y + size*0.24f, 0.14f*size, color, far_right_shade);

    // circle on the middle left
    tft->fillSmoothCircle(x+0.4f*size, y+0.2f*size, 0.18f*size, color, left_shade);

    // circle on the middle right
    tft->fillSmoothCircle(x+0.65f*size, y+0.15f*size, 0.15f*size, color, right_shade);
    
    tft->fillCircle(x+0.4f*size, y+0.2f*size+3, 0.18f*size+2, color);

    // rect, the filler
    tft->fillRect(x+0.2f*size+1, y+size*0.1f+1, 0.6f * size + 1, 0.3f * size-1, color);

    // Shading
    tft->fillSmoothCircle(x+0.4f*size, y+0.4f*size, 0.2f*size, fade_color, color);
    tft->fillSmoothCircle(x+0.65f*size, y+0.5f*size, 0.23f*size, fade_color, color);
    tft->fillCircle(x+0.4f*size, y+0.4f*size, 0.2f*size, fade_color);

    tft->fillRect(x, y + 0.38f*size, size, 0.4f * size, background_color);
}


void  
drawSun(
    TFT_eSPI *tft,
    uint16_t x, 
    uint16_t y, 
    uint16_t size, 
    uint16_t color, 
    uint16_t background_color
)
{
    tft->fillSmoothCircle(x+size/2, y+size/2, size/4, color, background_color);

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

        tft->drawWideLine(ax, ay,bx , by, roundf(0.05f * size), color, background_color);
    }
}

void  
drawMoon(
    TFT_eSPI *tft,
    uint16_t x, 
    uint16_t y, 
    uint16_t size, 
    uint16_t color, 
    uint16_t background_color,
    uint8_t offset
)
{
    tft->fillSmoothCircle(x+0.45f*size, y + 0.5f*size, 0.45f*size, color, background_color);
    tft->fillSmoothCircle(x+0.65f*size, y + 0.42f*size, 0.4f*size, background_color, color);
    tft->fillRect(x + 0.5f*size - offset, y, 0.5f*size + 2*offset, 0.2f*size, background_color);
    tft->fillRect(x + 0.8f*size - 1, y + 0.2f*size, 0.3f*size, 0.6f*size+1, background_color);
}


void  
drawSnowflake(
    TFT_eSPI *tft,
    uint16_t x, 
    uint16_t y, 
    uint16_t size, 
    uint16_t filler_circle_color, 
    uint16_t color, 
    uint16_t background_color
)
{
    uint16_t Ax,Ay,Bx,By, xc = 0.5f*size + x, yc = 0.5f*size + y;

    // 1st 'right up' part
    Ax = x + 0.8f*size;
    Bx = Ax + 0.15f*size;

    Ay = y + 0.5f*size;
    By = Ay + 0.15f*size;
    for (uint8_t i=0; i<9; i++)
    {
        float angle = i * PI/4;
        uint16_t
            ax = (Ax - xc) * cosf(angle) - (Ay - yc) * sinf(angle) + xc,
            ay = (Ax - xc) * sinf(angle) + (Ay - yc) * cosf(angle) + yc,
            bx = (Bx - xc) * cosf(angle) - (By - yc) * sinf(angle) + xc,
            by = (Bx - xc) * sinf(angle) + (By - yc) * cosf(angle) + yc;

        tft->drawWideLine(ax, ay,bx , by, 0.03f * size, color, background_color);
    }

    // 2nd 'right down' part
    Ax = x + 0.8f*size;
    Bx = Ax + 0.15f*size;

    Ay = y + 0.5f*size;
    By = Ay - 0.15f*size;
    for (uint8_t i=0; i<9; i++)
    {
        float angle = i * PI/4;
        uint16_t
            ax = (Ax - xc) * cosf(angle) - (Ay - yc) * sinf(angle) + xc,
            ay = (Ax - xc) * sinf(angle) + (Ay - yc) * cosf(angle) + yc,
            bx = (Bx - xc) * cosf(angle) - (By - yc) * sinf(angle) + xc,
            by = (Bx - xc) * sinf(angle) + (By - yc) * cosf(angle) + yc;

        tft->drawWideLine(ax, ay,bx , by, 0.03f * size, color, background_color);
    }


    // main framework

    Ax = 0.61f * size + x;
    Ay = y + size/2;
    Bx = Ax + 0.35f*size;
    By = Ay; 

    for (uint8_t i=0; i<9; i++)
    {
        float angle = i * PI/4;
        uint16_t
            ax = (Ax - xc) * cosf(angle) - (Ay - yc) * sinf(angle) + xc,
            ay = (Ax - xc) * sinf(angle) + (Ay - yc) * cosf(angle) + yc,
            bx = (Bx - xc) * cosf(angle) - (By - yc) * sinf(angle) + xc,
            by = (Bx - xc) * sinf(angle) + (By - yc) * cosf(angle) + yc;

        tft->drawWideLine(ax, ay,bx , by, 0.03f * size, color, background_color);
    }
 
    // middle circle
    tft->fillSmoothCircle(x+0.5f*size, y+0.5f*size, 0.1f*size, color, background_color);
    tft->fillCircle(x+0.5f*size, y+0.5f*size, 0.06f*size, filler_circle_color);
}

void  
drawMist (
    TFT_eSPI *tft,
    uint16_t x, 
    uint16_t y, 
    uint16_t size, 
    uint16_t color, 
    uint16_t background_color
)
{
    // lines going from down to up
    uint16_t ax = 0.3f*size + x,
            ay = 0.9f*size + y,
            bx = ax + 0.4f*size,
            by = ay;
    tft->drawWideLine(ax,ay,bx,by, 0.05f*size, color, background_color);

    ay -= 0.1f*size;
    by = ay;

    ax -= 0.1f*size;
    bx += 0.1f*size;
    tft->drawWideLine(ax,ay,bx,by, 0.05f*size, color, background_color);


    ay -= 0.1f*size;
    by = ay;

    ax = 0.05f*size + x;
    bx = 0.65f*size + x;
    tft->drawWideLine(ax,ay,bx,by, 0.05f*size, color, background_color);


    ay -= 0.1f*size;
    by = ay;

    ax = 0.25f*size + x;
    bx = 0.85f*size + x;
    tft->drawWideLine(ax,ay,bx,by, 0.05f*size, color, background_color);


    ay -= 0.1f*size;
    by = ay;

    ax = 0.07f*size + x;
    bx = 0.61f*size + x;
    tft->drawWideLine(ax,ay,bx,by, 0.05f*size, color, background_color);


    ay -= 0.1f*size;
    by = ay;

    ax = 0.4f*size + x;
    bx = 0.6f*size + x;
    tft->drawWideLine(ax,ay,bx,by, 0.05f*size, color, background_color);
}

void  
drawSingleWindString(
    TFT_eSPI *tft,
    uint16_t x, 
    uint16_t y, 
    uint16_t size,
    uint16_t lenght, 
    uint8_t thickness,
    uint16_t color, 
    uint16_t background_color, 
    bool reversed
)
{
    if (!reversed){
        tft->fillCircle(x + (size + lenght)*0.5f, y+0.3f*size, 0.2f*size, color);
        tft->fillCircle(x + (size + lenght)*0.5f, y+0.3f*size,0.2f*size - thickness, background_color);
        tft->fillRect(x+(size + lenght)*0.5f - 0.2f*size, y + 0.3f*size, 0.2f*size, 0.2f*size, background_color);
    }
    else{
        tft->fillCircle(x + (size + lenght)*0.5f, y+0.7f*size, 0.2f*size, color);
        tft->fillCircle(x + (size + lenght)*0.5f, y+0.7f*size,0.2f*size - thickness, background_color);
        tft->fillRect(x+(size + lenght)*0.5f - 0.2f*size, y + 0.5f*size, 0.2f*size, 0.2f*size, background_color);
    }
    
    tft->drawWideLine(x + (size - lenght)*0.5f, y+0.5f*size,x + (size + lenght)*0.5f, y+0.5f*size, thickness, color, background_color);
}

void  
drawDroplet(
    TFT_eSPI *tft,
    uint16_t x, 
    uint16_t y, 
    uint16_t size, 
    uint16_t color
)
{
    tft->fillCircle(x+size/2, y + size*0.7f, size*0.3f, color);
    tft->fillTriangle(x+0.2f*size, y + 0.7f*size, x + 0.8f*size, y + 0.7f*size, x + 0.5f*size, y, color);
}

void  
drawWifi(
    TFT_eSPI *tft,
    uint16_t x, 
    uint16_t y, 
    uint8_t size, 
    uint8_t strenght, 
    uint16_t background_color
)
{
    uint16_t 
    first  = TFT_WHITE,
    second = 0x52AA,
    third  = 0x52AA,
    fourth = 0x52AA;
    switch (strenght){
        case 4:
            first = 0x52AA;
            break;
        case 3:
            fourth = TFT_WHITE;
        case 2:
            third = TFT_WHITE;
        case 1:
            second = TFT_WHITE;
        default:
            break;
    }

    // first line
    tft->drawSmoothArc(x + 0.5f * size, y + 0.85 * size, roundf(0.75f*size), roundf(0.65f*size), 135, 235, fourth, background_color, true);

    // second line
    tft->drawSmoothArc(x + 0.5f * size, y + 0.85 * size, roundf(0.5f*size), roundf(0.4f*size) + 1, 135, 235, third, background_color, true);

    // third line
    tft->drawSmoothArc(x + 0.5f * size, y + 0.85 * size, roundf(0.25f*size) + 1, roundf(0.15f*size) + 2, 135, 235, second, background_color, true);

    // center circle
    tft->fillSmoothCircle(x + 0.5f * size, y + 0.85 * size - 1, 0.1f * size, first, background_color);
}

void  
drawLockOpened(
    TFT_eSPI *tft, 
    uint16_t x, 
    uint16_t y, 
    uint8_t size, 
    uint16_t color, 
    uint16_t background_color
)
{
    tft->fillRect(x,y,size,size,background_color);

    tft->fillCircle(x+0.3f*size, y+0.3f*size, 0.25f*size, color);
    tft->fillCircle(x+0.3f*size, y+0.3f*size, 0.2f*size, background_color);

    tft->drawCircle(x+0.3f*size, y+0.3f*size, 0.2f*size, color);

    tft->fillRect(x, y+0.3f*size, size, 0.3f*size, background_color);

    tft->fillRect(x+0.4f*size,y+0.3f*size,0.5f*size, 0.6f*size, color);
}

void 
drawLockLocked(
    TFT_eSPI *tft, 
    uint16_t x, 
    uint16_t y, 
    uint8_t size, 
    uint16_t color, 
    uint16_t background_color
)
{
    tft->fillRect(x,y,size,size,background_color);

    tft->fillCircle(x+0.7f*size, y+0.3f*size, 0.25f*size, color);
    tft->fillCircle(x+0.7f*size, y+0.3f*size, 0.2f*size, background_color);

    tft->fillRect(x, y+0.3f*size, size, 0.2f*size, background_color);    

    tft->fillRect(x+0.4f*size,y+0.3f*size,0.6f*size, 0.7f*size, color);
}

void
drawPickIcon(
    TFT_eSPI* tft,
    uint16_t x, 
    uint16_t y, 
    uint8_t size, 
    uint16_t color
)
{
    uint16_t st_y = y + 0.7f*size, end_x = x+0.6f*size;

    tft->drawWideLine(x, st_y, end_x, y+size, 0.3f*size, color);
    tft->drawWideLine(end_x, y+size, x+size, y, 0.3f*size, color);
}

void
drawSunGoingDown(
    TFT_eSPI* tft,
    uint16_t x, 
    uint16_t y, 
    uint8_t size, 
    uint16_t bg_c,
    uint16_t color
)
{
    drawSun(tft, x, y, size, color, bg_c);
    tft->fillRect(x, y + size*0.6f, size, size*0.4f, bg_c);
    tft->fillSmoothRoundRect(x, y + size*0.6f, size, size*0.15f, size*0.1f + 1, color, bg_c);
}

void
drawSunset(
    TFT_eSPI* tft,
    uint16_t x, 
    uint16_t y, 
    uint8_t size, 
    uint16_t bg_c
)
{
    drawSunGoingDown(tft, x, y, size, bg_c, 0xF240);
    tft->drawWideLine(
        float(x) + float(size)*0.5f, float(y) + float(size) * 0.75f,
        float(x) + float(size)*0.5f, float(y) + float(size),
        0.05f*size, 0xF240, bg_c);
    
    tft->drawWideLine(
        float(x) + float(size)*0.4f, float(y) + float(size) * 0.9f,
        float(x) + float(size)*0.5f, float(y) + float(size), 
        0.05f*size, 0xF240, bg_c);

    tft->drawWideLine(
        float(x) + float(size)*0.5f, float(y) + float(size),
        float(x) + float(size)*0.6f, float(y) + float(size)*0.9f,
        0.05f*size, 0xF240, bg_c);
}

void
drawSunrise(
    TFT_eSPI* tft,
    uint16_t x, 
    uint16_t y, 
    uint8_t size, 
    uint16_t bg_c
)
{
    drawSunGoingDown(tft, x, y, size, bg_c, 0xF4E3);
    tft->drawWideLine(
        float(x) + float(size)*0.5f, float(y) + float(size) * 0.75f,
        float(x) + float(size)*0.5f, float(y) + float(size),
        0.05f*size, 0xF4E3, bg_c);

    tft->drawWideLine(
        float(x) + float(size)*0.4f, float(y) + float(size) * 0.85f,
        float(x) + float(size)*0.5f, float(y) + float(size) * 0.75f,
        0.05f*size, 0xF4E3, bg_c);

    tft->drawWideLine(
        float(x) + float(size)*0.5f, float(y) + float(size) * 0.75f,
        float(x) + float(size)*0.6f, float(y) + float(size) * 0.85f,
        0.05f*size, 0xF4E3, bg_c);
}