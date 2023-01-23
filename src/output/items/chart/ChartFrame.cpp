#include "ChartFrame.h"

void draw_arrow_up(TFT_eSPI* tft, uint16_t starting_x, uint16_t starting_y, uint16_t height, uint8_t arrow_lenght, uint16_t color)
{
    tft->drawFastVLine(starting_x, starting_y-height, height, color);

    float y = float(starting_y - height + SQRT_2_DIV_2*arrow_lenght);
    tft->drawLine(starting_x - SQRT_2_DIV_2 * arrow_lenght, y, starting_x, starting_y - height, color);
    tft->drawLine(starting_x + SQRT_2_DIV_2*arrow_lenght, y, starting_x, starting_y - height, color);
}

void draw_arrow_down(TFT_eSPI* tft, uint16_t starting_x, uint16_t starting_y, uint16_t height, uint8_t arrow_lenght, uint16_t color)
{
    tft->drawFastVLine(starting_x, starting_y, height, color);

    float y = float(starting_y + height - SQRT_2_DIV_2*arrow_lenght);
    tft->drawLine(starting_x - SQRT_2_DIV_2 * arrow_lenght, y, starting_x, starting_y + height, color);
    tft->drawLine(starting_x + SQRT_2_DIV_2*arrow_lenght, y, starting_x, starting_y + height, color);
}

void draw_arrow_left(TFT_eSPI* tft, uint16_t starting_x, uint16_t starting_y, uint16_t width, uint8_t arrow_lenght, uint16_t color)
{
    tft->drawFastHLine(starting_x, starting_y, width, color);

    float x = float(starting_x + width - SQRT_2_DIV_2 * arrow_lenght);
    tft->drawLine(x, float(starting_y - SQRT_2_DIV_2 * arrow_lenght) , starting_x+width, starting_y, color);
    tft->drawLine(x, float(starting_y + SQRT_2_DIV_2 * arrow_lenght), starting_x+width, starting_y, color);
}


void ChartFrameVFull::draw(bool forceDraw)
{
    if (!forceDraw)
    {
        return;
    }

    // drawing arrow
    draw_arrow_up(this->tft, STARTING_X, MIDDLE_Y, MAX_POSITIVE, 5, color);
    tft->drawFastVLine(STARTING_X, MIDDLE_Y, MAX_NEGATIVE, color);

    // drawing scale
    float itr_pos = MAX_POSITIVE*0.2f;
    float itr_neg = MAX_NEGATIVE*0.2f;

    float y_pos_positive = MIDDLE_Y;
    float y_pos_negative = MIDDLE_Y;

    float value = 0;
    float neg_value = 0;

    float neg_value_itr = min_value*0.18f;
    float value_itr = max_value*0.18f;


    tft->setCursor(0, MIDDLE_Y);
    tft->setTextFont(1);
    tft->setTextSize(1);
    tft->setTextColor(color);
    tft->print(0);

    for (uint8_t i=0; i< NUMBER_OF_SECTIONS; i++)
    {
        neg_value += neg_value_itr;
        value += value_itr;

        y_pos_negative += itr_neg;
        y_pos_positive -= itr_pos;

        tft->setCursor(0, y_pos_negative);
        tft->print((int8_t)neg_value);

        tft->setCursor(0, y_pos_positive);
        tft->print((int8_t)value);
    }
}