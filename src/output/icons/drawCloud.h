#ifndef DRAW_CLOUD_H
#define DRAW_CLOUD_H

#include <Arduino.h>
#include <TFT_eSPI.h> 
#include <SPI.h>

void inline drawCloud(TFT_eSPI *tft,uint16_t x, uint16_t y, uint16_t size, uint16_t color, uint16_t background_color)
{
    //Cloud drawing
    // circles on the right and left
    tft->fillSmoothCircle(x+0.2f*size, y + size*0.24f, 0.14f*size, color, background_color);
    tft->fillSmoothCircle(x+0.8f*size, y + size*0.24f, 0.14f*size, color, background_color);

    // circle on the middle left
    tft->fillSmoothCircle(x+0.4f*size, y+0.2f*size, 0.18f*size, color, background_color);

    // circle on the middle right
    tft->fillSmoothCircle(x+0.65f*size, y+0.15f*size, 0.15f*size, color, color);

    // rect, the filler
    tft->fillRoundRect(x+0.2f*size, y+size*0.1f, 0.6f * size, 0.3f * size, 0.05f*size, color);
}

#endif