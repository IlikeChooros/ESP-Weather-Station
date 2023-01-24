#include "ChartFrame.h"

void draw_arrow_up(TFT_eSPI* tft, ui16 starting_x, ui16 starting_y, ui16 height, ui8 arrow_lenght, ui16 color)
{
    tft->drawFastVLine(starting_x, starting_y-height, height, color);

    float y = float(starting_y - height + SQRT_2_DIV_2*arrow_lenght);
    tft->drawLine(starting_x - SQRT_2_DIV_2 * arrow_lenght, y, starting_x, starting_y - height, color);
    tft->drawLine(starting_x + SQRT_2_DIV_2*arrow_lenght, y, starting_x, starting_y - height, color);
}

void draw_arrow_down(TFT_eSPI* tft, ui16 starting_x, ui16 starting_y, ui16 height, ui8 arrow_lenght, ui16 color)
{
    tft->drawFastVLine(starting_x, starting_y, height, color);

    float y = float(starting_y + height - SQRT_2_DIV_2*arrow_lenght);
    tft->drawLine(starting_x - SQRT_2_DIV_2 * arrow_lenght, y, starting_x, starting_y + height, color);
    tft->drawLine(starting_x + SQRT_2_DIV_2*arrow_lenght, y, starting_x, starting_y + height, color);
}

void draw_arrow_left(TFT_eSPI* tft, ui16 starting_x, ui16 starting_y, ui16 width, ui8 arrow_lenght, ui16 color)
{
    tft->drawFastHLine(starting_x, starting_y, width, color);

    float x = float(starting_x + width - SQRT_2_DIV_2 * arrow_lenght);
    tft->drawLine(x, float(starting_y - SQRT_2_DIV_2 * arrow_lenght) , starting_x+width, starting_y, color);
    tft->drawLine(x, float(starting_y + SQRT_2_DIV_2 * arrow_lenght), starting_x+width, starting_y, color);
}


void
ChartFrameVFull::draw(bool forceDraw)
{
    if (!forceDraw)
    {
        return;
    }

    // drawing arrow
    draw_arrow_up(this->tft, STARTING_X, MIDDLE_Y, MAX_POSITIVE, 5, color);
    tft->drawFastVLine(STARTING_X, MIDDLE_Y, MAX_NEGATIVE, color);

    // drawing scale
    float value = 0;
    float neg_value = 0;

    float neg_value_itr = -1;
    float value_itr = 1;


    tft->setCursor(11, MIDDLE_Y);
    tft->setTextFont(1);
    tft->setTextSize(1);
    tft->setTextColor(color);
    tft->print(0);

    i16 y;
    for (ui8 i=0; i< number_of_sections; i++)
    {
        neg_value += neg_value_itr;
        value += value_itr;

        y = get_y(neg_value);
        // if (y < MIN_HEIGHT_ || y > MAX_HEIGHT_)
        // {
        //     return;
        // }
        tft->drawCentreString(String((i8)neg_value), 8, y, 1);

        y = get_y(value);
        // if (y < MIN_HEIGHT_ || y > MAX_HEIGHT_)
        // {
        //     return;
        // }
        tft->drawCentreString(String((i8)value), 8, y, 1);
    }
}

ui16
ChartFrameVFull::get_y(i16 data)
{
    return data > 0 ? (MIDDLE_Y - data*scale_positive) : (MIDDLE_Y - data*scale_negative);
}