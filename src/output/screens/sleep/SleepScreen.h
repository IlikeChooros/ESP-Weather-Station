#pragma once


#include "RandomFigures.h"
#include "FloatingRam.h"


class SleepScreen
{
    TFT_eSPI* tft;
    uint16_t bg_c;

    std::vector<Figure::RandomFigure> rects;
    std::unique_ptr<floating::FloatingRam> floating_ram;

    public:
    /**
     * @brief Screen that converse tft screen usage
     * 
     * @param tft 
     */
    SleepScreen(
        TFT_eSPI* tft,
        uint16_t bg_c
    );

    /**
     * @brief Draws rectangles to tft screen
     * 
     */
    void
    draw();

    /**
     * @brief Resets previous data, ready to draw again
     * 
     */
    void 
    reset();
};