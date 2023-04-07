#include "ChartFrame.h"

void 
draw_arrow_up(
    TFT_eSPI* tft, 
    ui16 starting_x, 
    ui16 starting_y, 
    ui16 height, 
    ui8 arrow_lenght, 
    ui16 color
)
{
    tft->drawFastVLine(starting_x, starting_y-height, height, color);

    float y = float(starting_y - height + SQRT_2_DIV_2*arrow_lenght);
    tft->drawLine(starting_x - SQRT_2_DIV_2 * arrow_lenght, y, starting_x, starting_y - height, color);
    tft->drawLine(starting_x + SQRT_2_DIV_2*arrow_lenght, y, starting_x, starting_y - height, color);
}

void 
draw_arrow_down(
    TFT_eSPI* tft, 
    ui16 starting_x, 
    ui16 starting_y, 
    ui16 height, 
    ui8 arrow_lenght, 
    ui16 color
)
{
    tft->drawFastVLine(starting_x, starting_y, height, color);

    float y = float(starting_y + height - SQRT_2_DIV_2*arrow_lenght);
    tft->drawLine(starting_x - SQRT_2_DIV_2 * arrow_lenght, y, starting_x, starting_y + height, color);
    tft->drawLine(starting_x + SQRT_2_DIV_2*arrow_lenght, y, starting_x, starting_y + height, color);
}

void 
draw_arrow_left(
    TFT_eSPI* tft, 
    ui16 starting_x, 
    ui16 starting_y, 
    ui16 width, 
    ui8 arrow_lenght, 
    ui16 color
)
{
    tft->drawFastHLine(starting_x, starting_y, width, color);

    float x = float(starting_x + width - SQRT_2_DIV_2 * arrow_lenght);
    tft->drawLine(x, float(starting_y - SQRT_2_DIV_2 * arrow_lenght) , starting_x+width, starting_y, color);
    tft->drawLine(x, float(starting_y + SQRT_2_DIV_2 * arrow_lenght), starting_x+width, starting_y, color);
}


void
ChartFrameVFull::
draw(bool forceDraw)
{
    if (!forceDraw)
    {
        return;
    }

    // drawing arrow
    draw_arrow_up(this->tft, starting_x_, MIDDLE_Y, MAX_POSITIVE, 5, color);
    tft->drawFastVLine(starting_x_, MIDDLE_Y, MAX_NEGATIVE, color);


    // drawing scale numbers
    float value = 0,
    mx_val = max_value,
    min_val = min_value,
    num_of_sec = number_of_sections,
    neg_value = 0;

    float neg_value_itr = min_val/num_of_sec;
    float value_itr = mx_val/num_of_sec;


    tft->setTextFont(1);
    tft->setTextSize(1);
    tft->setTextColor(color);
    tft->drawCentreString(String(0), starting_x_-STARTING_X/2, MIDDLE_Y-3, 1);

    tft->setCursor(starting_x_, MIDDLE_Y - MAX_POSITIVE - 8);
    tft->print(name);

    for (ui8 i=0; i< number_of_sections; i++)
    {
        neg_value += neg_value_itr;
        value += value_itr;

        tft->drawCentreString(String((i8)neg_value), 8, get_y(neg_value), 1);
        tft->drawCentreString(String((i8)value), 8, get_y(value), 1);
    }
}

ui16
ChartFrameVFull::
get_y(i16 data)
{
    return data > 0 ? (MIDDLE_Y - data*scale_positive) : (MIDDLE_Y - data*scale_negative);
}

ui16
ChartFrameVUp::
get_y(i16 data)
{
    return MIDDLE_Y - data*scale;
}

void
ChartFrameVUp::
draw(bool forceDraw)
{
    if (!forceDraw)
    {
        return;
    }

    // drawing arrow
    draw_arrow_up(this->tft, starting_x_, MIDDLE_Y, MAX_POSITIVE, 5, color);

    // drawing scale numbers
    float value = 0,
    mx_val = max_value,
    n_of_sec = number_of_sections;
    float value_itr = mx_val/n_of_sec;

    tft->setTextFont(1);
    tft->setTextSize(1);
    tft->setTextColor(color);
    tft->drawCentreString(String(0), starting_x_+STARTING_X/2+3, MIDDLE_Y-7, 1);

    tft->setCursor(starting_x_, MIDDLE_Y - MAX_POSITIVE - 8);
    tft->print(name);

    for (ui8 i=0; i< number_of_sections; i++)
    {
        value += value_itr;
        tft->drawCentreString(String((i8)value), starting_x_+STARTING_X/2+4, get_y(value), 1);
    }
}



void 
ChartFrameTime::
draw(bool forceDraw)
{
    if(!forceDraw)
    {
        return;
    }

    tft->drawFastHLine(STARTING_X, MIDDLE_Y, 288, color);

    String hours [7] = {"3:00", "6:00", "9:00", "12:00",
                        "15:00", "18:00", "21:00"};

    ui16 x = STARTING_X,y = MIDDLE_Y+3;
    
    tft->setTextSize(1);
    tft->setTextColor(color);

    for (ui8 i=0; i<7; i++)
    {
        x += 3*HOURS_PIXELS;
        tft->drawCentreString(hours[i], x, y, 1);
    }
}
