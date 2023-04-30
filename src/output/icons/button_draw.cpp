#include "button_draw.h"

/**
 * @brief Fuction drawing refresh button
 * 
 * @param tft 
 * @param x 
 * @param y 
 * @param size
 * @param color 
 */
void
drawRefreshButton(
    TFT_eSPI* tft,
    uint16_t x,
    uint16_t y,
    uint16_t size,
    uint16_t color 
)
{
    tft->fillRect(x,y,size,size,color);
    tft->drawRect(x,y,size,size, TFT_WHITE);

    tft->drawSmoothCircle(x+0.5f*size, y+0.5f*size, 0.3f*size, TFT_WHITE, color);

    // on left
    tft->drawWideLine(x+0.1f*size, y+0.4f*size, x+0.2f*size, y+0.5f*size, size*0.03f, TFT_WHITE, TFT_WHITE);
    tft->drawWideLine(x+0.2f*size, y+0.5f*size, x+0.3f*size, y+0.4f*size, size*0.03f, TFT_WHITE, TFT_WHITE);

    // on right
    tft->drawWideLine(x+0.7f*size, y+0.6f*size, x+0.8f*size, y+0.5f*size, size*0.03f, TFT_WHITE, TFT_WHITE);
    tft->drawWideLine(x+0.8f*size, y+0.5f*size, x+0.9f*size, y+0.6f*size, size*0.03f, TFT_WHITE, TFT_WHITE);
}

void
drawTickButton(
    TFT_eSPI* tft,
    uint16_t x, 
    uint16_t y, 
    uint16_t size, 
    uint16_t color
)
{
    tft->fillRect(x,y,size,size,color);
    tft->drawRect(x,y,size,size, TFT_LIGHTGREY);

    uint16_t st_y = y + 0.5f*size, end_x = x+0.5f*size;

    tft->drawWideLine(x+0.25f*size, st_y, end_x, y+size*0.75f, 0.05f*size, TFT_WHITE, color);
    tft->drawWideLine(end_x, y+size*0.75f, x+0.75f*size, y+0.25f*size, 0.05f*size, TFT_WHITE, color);
}

void
drawSetLocationButton(
    TFT_eSPI* tft,
    uint16_t x,
    uint16_t y,
    uint16_t size,
    uint16_t color 
)
{
    tft->loadFont(LATIN);
    tft->fillRect(x, y, 320, size, color);
    tft->drawFastHLine(x, y, 320, TFT_DARKGREY);

    tft->setTextColor(TFT_DARKGREY, color);
    tft->drawCentreString("Set new location.", 160, y+10, 2);
    tft->unloadFont();
}

void
drawRightArrow(
    TFT_eSPI* tft,
    uint16_t x,
    uint16_t y,
    uint16_t w,
    uint16_t h,
    uint16_t color 
)
{
    tft->drawRoundRect(x, y, w, h, 0.1f*h, TFT_DARKGREY);
    tft->fillTriangle(x+0.7f*w, y, x+w, y+0.5f*h, x+0.7f*w, y+h, color);
    tft->fillRect(x, y+0.3f*h, 0.7*w, 0.4f*h, color);
}

void
drawLeftArrow(
    TFT_eSPI* tft,
    uint16_t x,
    uint16_t y,
    uint16_t w,
    uint16_t h,
    uint16_t color 
)
{
    tft->drawRoundRect(x, y, w, h, 0.1f*h, TFT_DARKGREY);
    tft->fillTriangle(x+0.3f*w, y, x, y+0.5f*h, x+0.3f*w, y+h, color);
    tft->fillRect(x+0.3f*h, y+0.3f*h, 0.7*w, 0.4f*h, color);
}

void
drawExitButton(
    TFT_eSPI* tft,
    uint16_t x,
    uint16_t y,
    uint16_t size,
    uint16_t color
)
{
    tft->fillRect(x,y,size,size,color);
    tft->drawRect(x,y,size,size,TFT_DARKGREY);

    tft->drawWideLine(x+0.1f*size, y+0.1f*size, x+0.9f*size, y+0.9f*size, 0.05f*size, TFT_WHITE, color);
    tft->drawWideLine(x+0.1f*size, y+0.9f*size, x+0.9f*size, y+0.1f*size, 0.05f*size, TFT_WHITE, color);
}

void
drawSettingsButton(
    TFT_eSPI* tft,
    uint16_t x,
    uint16_t y,
    uint16_t size,
    uint16_t color 
)
{
    tft->fillRect(x,y,size,size,color);

    uint16_t gear_color = 0x4228;

    uint16_t 
    xc = x + size/2,
    yc = y + size/2,
    Ax = 0.75f * size + x,
    Ay = y + size/2,
    Bx = 0.9f*size + x,
    By = Ay; 

    for (uint8_t i=0; i<9; i++)
    {
        float angle = i * PI/4;
        uint16_t
            ax = (Ax - xc) * cosf(angle) - (Ay - yc) * sinf(angle) + xc,
            ay = (Ax - xc) * sinf(angle) + (Ay - yc) * cosf(angle) + yc,
            bx = (Bx - xc) * cosf(angle) - (By - yc) * sinf(angle) + xc,
            by = (Bx - xc) * sinf(angle) + (By - yc) * cosf(angle) + yc;

        tft->drawWideLine(ax, ay,bx , by, 0.15f * size, gear_color, color);
    }

    tft->fillCircle(x+0.5f*size, y+0.5f*size, 0.3f*size, gear_color);
    tft->fillSmoothCircle(x+0.5f*size, y+0.5f*size, 0.2f*size, color, gear_color);
    tft->drawRect(x,y,size,size, TFT_WHITE);
}

void
drawScrollUpButton(
    TFT_eSPI* tft,
    uint16_t x,
    uint16_t y,
    uint16_t w,
    uint16_t h,
    uint16_t color 
)
{
    tft->fillRect(x, y, w, h, color);
    tft->drawRect(x, y, w, h, TFT_DARKGREY);

    tft->drawLine(x + 0.1f*w, y + 0.7f*h, x + 0.5f*w, y + 0.3f*h, TFT_DARKGREY);
    tft->drawLine(x + 0.5f*w, y + 0.3f*h, x + 0.9f*w, y + 0.7f*h, TFT_DARKGREY);
}

void
drawScrollDownButton(
    TFT_eSPI* tft,
    uint16_t x,
    uint16_t y,
    uint16_t w,
    uint16_t h,
    uint16_t color 
)
{
    tft->fillRect(x, y, w, h, color);
    tft->drawRect(x, y, w, h, TFT_DARKGREY);

    tft->drawLine(x + 0.1f*w, y + 0.3f*h, x + 0.5f*w, y + 0.7f*h, TFT_DARKGREY);
    tft->drawLine(x + 0.5f*w, y + 0.7f*h, x + 0.9f*w, y + 0.3f*h, TFT_DARKGREY);
}

void
drawEraseButton(
    TFT_eSPI* tft,
    uint16_t x,
    uint16_t y,
    uint16_t size,
    uint16_t color 
)
{
    tft->fillRect(x, y, size, size, color);
    tft->drawRect(x, y, size, size, TFT_WHITE);

    tft->fillRect(x + 0.25f*size, y+0.3f*size, size*0.5f + 1, size*0.6f, color);
    tft->drawRect(x + 0.25f*size, y+0.3f*size, size*0.5f + 1, size*0.6f, TFT_LIGHTGREY);

    tft->drawWideLine(x + 0.35f*size, y + 0.75f*size, x + 0.35f*size, y + 0.45f*size, 0.075f*size, TFT_DARKGREY, color);
    tft->drawWideLine(x + 0.5f*size, y + 0.75f*size, x + 0.5f*size, y + 0.45f*size, 0.075f*size, TFT_DARKGREY, color);
    tft->drawWideLine(x + 0.65f*size, y + 0.75f*size, x + 0.65f*size, y + 0.45f*size, 0.075f*size, TFT_DARKGREY, color);

    tft->fillRect(x + 0.2f*size, y+0.15f*size, size*0.6f, size*0.2f, color);
    tft->drawRect(x + 0.2f*size, y+0.15f*size, size*0.6f, size*0.2f, TFT_LIGHTGREY);
}

void
drawDetailsButton(
    TFT_eSPI* tft,
    uint16_t x,
    uint16_t y,
    uint16_t size,
    uint16_t color 
)
{
    tft->fillRect(x, y, size, size, color);
    tft->drawRect(x, y, size, size, TFT_WHITE);

    tft->fillEllipse(x + size*0.5f, y + size*0.5f, size*0.4f, size*0.3f, TFT_LIGHTGREY);
    tft->fillEllipse(x + size*0.5f, y + size*0.5, size*0.3f, size*0.2f, color);

    tft->fillCircle(x + size*0.5f, y + size*0.5f, size*0.3f, TFT_LIGHTGREY);
    tft->fillSmoothCircle(x + size*0.5f, y + size*0.5f, size*0.2f, color, TFT_LIGHTGREY);
}