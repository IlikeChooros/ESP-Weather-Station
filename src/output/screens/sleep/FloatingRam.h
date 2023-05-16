#pragma once

#include "TFT_eSPI.h"
#include "../../../data_structures/Hsv_to_rgb.h"


namespace floating
{

enum class Factors{
    velocity_x=2,
    velocity_y=2,
    slider_velocity=2,
    width=100,
    height=50
};


class FloatingRam{

    TFT_eSPI* _tft;
    TFT_eSprite img;
    uint16_t _bg_c;

    String _to_print;
    uint32_t _ram;

    int16_t _x;
    int16_t _y;
    int16_t _width;
    int16_t _height;

    int16_t _slider_y;
    int16_t _slider_x;
    int16_t _slider_width;
    int16_t _slider_velocity;
    std::unique_ptr<uint16_t[]> _colors;

    int16_t _velocity_x;
    int16_t _velocity_y;

    String _upper_text;
    String _down_text;

    uint64_t _time;    
    uint64_t _slider_time;    
    uint16_t _waiting_time;

    void
    setRamText();

    void 
    move();

    void 
    slide();

public:
    FloatingRam(TFT_eSPI* tft, uint16_t bg_c);
    ~FloatingRam()=default;

    FloatingRam*
    x(uint16_t x){
        _x = x;
        return this;
    }

    FloatingRam* 
    y(uint16_t y){
        _y = y;
        return this;
    }

    void 
    draw();
};

}// Floating


