#include "SleepScreen.h"

void
RandomFigure::draw()
{
    if (millis() - time_ < 20) {return;}
    move();
    draw_by_idx();
    prev_x_ = x_;
    prev_y_ = y_;
    time_ = millis();
}

void
RandomFigure::draw_by_idx()
{
    switch(idx_)
    {
        case TRIANGLE_IDX:
            tft_->fillTriangle(prev_x_, prev_y_, prev_x_+width_, prev_y_ + height_, prev_x_ + width_/2, prev_y_ + height_/2, bg_c_);
            tft_->fillTriangle(x_, y_, x_+width_, y_ + height_, x_ + width_/2, y_ + height_/2, color_);
            return;
        case RECTANGLE_IDX:
            tft_->fillRect(prev_x_, prev_y_, width_, height_, bg_c_);
            tft_->fillRect(x_, y_, width_, height_, color_);
            return;
        case CIRCLE_IDX:
            tft_->fillCircle(prev_x_, prev_y_, width_, bg_c_);
            tft_->fillCircle(x_, y_, width_, color_);
            return;
        case L_IDX:
            tft_->fillRect(x_, y_, width_, height_, color_);
            tft_->fillRect(prev_x_, prev_y_, width_, height_, bg_c_);
            return;
        default:
            tft_->fillCircle(x_, y_, width_, color_);
            tft_->fillCircle(prev_x_, prev_y_, width_, bg_c_);
            return;
    }
}

void
RandomFigure::move()
{
    x_ += velocity_x_;
    y_ += velocity_y_;

    if (x_ <= offset_x_ || x_>= tft_->width() - width_)
    {
        velocity_x_ = -velocity_x_;
    }

    if (y_ <= offset_y_ || y_ >= tft_->height() - height_)
    {
        velocity_y_ = -velocity_y_;
    }
}

void
SleepScreen::draw()
{
    for(uint8_t i=0; i<rects.size(); i++)
    {
        rects.at(i).draw();
    }
}

void
SleepScreen::reset()
{
    while(!rects.is_empty())
    {
        rects.pop_back();
    }

    for (uint8_t i=0; i<NUMBER_OF_RECTS; i++)
    {
        RandomFigure* rect(static_cast<RandomFigure*>(::operator new(sizeof(RandomFigure))));
        rect
        ->bg_c(bg_c)
        ->color()
        ->tft(tft)
        ->height(4)
        ->width(4)
        ->x(esp_random()%(tft->width()+1))
        ->y(esp_random()%(tft->height()+1))
        ->rest();
        rects.push_back(*rect);
        delete rect;
    }
}