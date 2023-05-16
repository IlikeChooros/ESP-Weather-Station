#pragma once

#include "TFT_eSPI.h" 

#include "../../../data_structures/Point.h"
#include "../../../data_structures/Hsv_to_rgb.h"
#include <vector>

namespace Figure
{
    

enum fig{
    VELOCITY_X=6,
    VELOCITY_Y=3,
    NUMBER_OF_RECTS=6,
    TRIANGLE_IDX=0,
    RECTANGLE_IDX=1,
    CIRCLE_IDX=2,
    L_IDX=3,
    MOON_IDX=4
};

class RandomFigure{
    TFT_eSPI* tft_;

    uint8_t height_;
    uint8_t width_;

    uint16_t color_;
    uint16_t bg_c_;

    int8_t velocity_x_;
    int8_t velocity_y_;

    uint16_t x_;
    uint16_t y_;

    uint16_t prev_x_;
    uint16_t prev_y_;

    uint8_t offset_x_;
    uint8_t offset_y_;

    uint64_t time_;

    uint8_t idx_;

    void 
    draw_by_idx();

    void 
    move();

    public:
    RandomFigure* tft(TFT_eSPI *tft) {
        this->tft_ = tft; 
        return this;
    }
    RandomFigure* height(uint8_t max_height) {
        this->height_ = esp_random()%max_height + 8;
        return this;
    }
    RandomFigure* width(uint8_t max_width) {
        this->width_ = esp_random()%max_width + 8;
        return this;
    }
    RandomFigure* x(uint16_t starting_x) {
        this->x_ = starting_x;
        return this;
    }
    RandomFigure* y(uint16_t starting_y) {
        this-> y_ = starting_y;
        return this;
    }
    RandomFigure* color() {
        HSV* hsv = new HSV;
        hsv->hue = esp_random()%180 + 160;
        hsv->satrutaion = 50 + esp_random()%50;
        hsv->value = 50 + esp_random()%50;
        color_ = HSV_RGB(*hsv);
        delete hsv;
        return this;
    }
    RandomFigure* bg_c(uint16_t bg_c) {
        this-> bg_c_ = bg_c;
        return this;
    }
    RandomFigure* rest() {
        this->velocity_x_ = Figure::VELOCITY_X;
        this->velocity_y_ = Figure::VELOCITY_Y;
        this->prev_x_ = x_;
        this->prev_y_ = y_;
        this->time_ = 0;
        this->idx_ = esp_random()%5;
        this->offset_x_ = 0;
        this->offset_y_ = 0;

        if (idx_ == Figure::CIRCLE_IDX){
            width_ /=2;
            width_ -= 1;
            height_ = width_;
            offset_x_ = width_;
            offset_y_ = width_;
        }
        return this;
    }

    void
    draw();
};

} // namespace Figure

