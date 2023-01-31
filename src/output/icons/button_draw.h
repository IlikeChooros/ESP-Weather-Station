#pragma once

#include <Arduino.h>
#include <TFT_eSPI.h> 
#include <SPI.h>

/**
 * @brief Fuction drawing refresh button
 * 
 * @param tft 
 * @param x 
 * @param y 
 * @param size
 * @param color 
 */
inline
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

    tft->drawCircle(x+0.5f*size, y+0.5f*size, 0.3f*size, TFT_WHITE);
    tft->drawCircle(x+0.5f*size, y+0.5f*size, 0.2f*size, color);

    // on left
    tft->drawWideLine(x+0.1f*size, y+0.4f*size, x+0.2f*size, y+0.5f*size, size*0.05f, TFT_WHITE, TFT_WHITE);
    tft->drawWideLine(x+0.2f*size, y+0.5f*size, x+0.3f*size, y+0.4f*size, size*0.05f, TFT_WHITE, TFT_WHITE);

    // on right
    tft->drawWideLine(x+0.7f*size, y+0.6f*size, x+0.8f*size, y+0.5f*size, size*0.05f, TFT_WHITE, TFT_WHITE);
    tft->drawWideLine(x+0.8f*size, y+0.5f*size, x+0.9f*size, y+0.6f*size, size*0.05f, TFT_WHITE, TFT_WHITE);
}

inline
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

    uint16_t st_y = y + 0.4f*size, end_x = x+0.5f*size;

    tft->drawWideLine(x+0.2f*size, st_y, end_x, y+size*0.75f, 0.08f*size, TFT_WHITE, TFT_WHITE);
    tft->drawWideLine(end_x, y+size*0.75f, x+0.85f*size, y+0.15f*size, 0.08f*size, TFT_WHITE, TFT_WHITE);
}

inline
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
    tft->drawRect(x,y,size,size, TFT_WHITE);

    uint16_t gear_color = TFT_DARKGREY;
    tft->fillCircle(x+0.5f*size, y+0.5f*size, 0.3f*size, gear_color);
    tft->fillCircle(x+0.5f*size, y+0.5f*size, 0.2f*size, color);

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
}