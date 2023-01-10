#ifndef SCREEN_POINT_ITEM_H
#define SCREEN_POINT_ITEM_H


#include "TFT_eSPI.h"
#include "SPI.h"
#include "Arduino.h"

#define DARK_SCREEN_POINT 0x632C
#define GREY_SCREEN_POINT 0x8C71
#define SIZE_POINT 10

class ScreenPointItem
{
    TFT_eSPI *_tft;
    uint16_t x;
    uint16_t y;
    uint16_t bg_c;
    uint16_t* colors;
    public:
    ScreenPointItem(TFT_eSPI *tft, uint16_t x, uint16_t y, uint16_t bg_c);
    void draw(uint8_t numberOfAllInX, uint8_t numberOfAllInY, uint8_t currentX, uint8_t currentY);

};



#endif