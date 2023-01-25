#include "ChartScreens.h"

void
ChartScreens::draw_bg()
{
    tft->fillScreen(bg_c);

    // Lines
    int16_t x_itr = 320 / 5,
            y_itr = 240 / 4;
    int16_t x = x_itr,
            y = y_itr;

    for (uint8_t i=1 ; i<5; i++)
    {
        tft->drawFastVLine(x, 0, 240, TFT_NAVY);

        if (i<4)
        {
            tft->drawFastHLine(0, y, 320, TFT_NAVY);
        }
        x+=x_itr;
        y+=y_itr;
    }
}