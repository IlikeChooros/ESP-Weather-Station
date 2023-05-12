#ifndef SCREEN_POINT_ITEM_H
#define SCREEN_POINT_ITEM_H


#include "TFT_eSPI.h"
#include "SPI.h"
#include "Arduino.h"

#include "../../data_structures/Hsv_to_rgb.h"

#define DARK_SCREEN_POINT 0x632C
#define GREY_SCREEN_POINT 0x8C71
#define SIZE_POINT 10

class ScreenPointItem
{
    TFT_eSPI *_tft;
    uint16_t x;
    uint16_t y;
    uint16_t bg_c;
    uint8_t size;
    uint8_t prev_lenght;
    uint16_t* colors;
    public:

    ScreenPointItem(
        TFT_eSPI *tft,
        uint16_t x,
        uint16_t y,
        uint16_t bg_c,
        uint8_t size
    );

    ~ScreenPointItem();

    /**
     * @brief draws dots on screen
     * 
     * @param numberOfAllInX X_SCREENS or X_1_SCREENS
     * @param numberOfAllInY 2
     * @param currentX screen_point.x+1
     * @param currentY screen_point.y+1
     */
    void
    draw(
        uint8_t numberOfAllInX,
        uint8_t numberOfAllInY,
        uint8_t currentX,
        uint8_t currentY
    );

};



#endif