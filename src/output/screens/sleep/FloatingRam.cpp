#include "FloatingRam.h"


namespace floating{

FloatingRam::
FloatingRam(TFT_eSPI* tft, uint16_t bg_c):
_tft(tft), _bg_c(bg_c), img(tft),
_velocity_x((uint16_t)Factors::velocity_x),
_velocity_y((uint16_t)Factors::velocity_y), 
_waiting_time(20){
    setRamText();
}

FloatingRam::
~FloatingRam(){

}
void FloatingRam::
setRamText(){
    img.deleteSprite();

    img.setTextSize(2);
    img.setTextFont(2);

    _height = 0;
    _slider_x = 0;
    _slider_velocity = -(int16_t)Factors::slider_velocity;

    _upper_text = "Free memory: "+String(ESP.getFreeHeap()/1000)+" kB";
    _width = img.textWidth(_upper_text);
    _height += img.fontHeight(2);
    _slider_y = _height;
    img.setTextSize(1);
    _height += img.fontHeight(2);
    _down_text = "To be exact: " + String(ESP.getFreeHeap()) + " Bytes (without this screen: " + String(ESP.getFreeHeap() + _width*_height*2 + sizeof(*this)) +  " Bytes)";
    _slider_width = img.textWidth(_down_text);

    img.setTextColor(TFT_LIGHTGREY);
    img.createSprite(_width, _height);
    img.fillSprite(_bg_c);
    img.setTextSize(2);
    img.drawString(_upper_text, 0, 0);
    img.setTextSize(1);
    img.drawString(_down_text, _slider_x, _slider_y);
    
}

void FloatingRam::
move(){
    _x += _velocity_x;
    _y += _velocity_y;

    if (_x <= 0 || _x >= _tft->width() - _width){
        _velocity_x = -_velocity_x;
    }

    if (_y <= 0 || _y >= _tft->height() - _height){
        _velocity_y = -_velocity_y;
    }
}

void FloatingRam::
slide(){
    if (millis() - _slider_time < _waiting_time)
        return;

    _waiting_time = 12;
    img.setTextFont(2);
    img.setTextSize(1);
    img.setTextColor(TFT_GREEN);

    // Refresh slider
    img.fillRect(0, _slider_y, _width, img.fontHeight(), _bg_c);
    _slider_x += _slider_velocity;

    if (_slider_x <= _width - _slider_width){
        _slider_velocity = (int16_t)Factors::slider_velocity;
        _waiting_time = 500;
    }
    else if (_slider_x >= 0){
        _slider_velocity = -(int16_t)Factors::slider_velocity;
        _waiting_time = 500;
        setRamText();
        _slider_time = millis();
        return;
    }
    img.drawString(_down_text, _slider_x, _slider_y);
    _slider_time = millis();
}

void FloatingRam::
draw(){
    slide();
    if (millis() - _time < 12)
        return;
    
    _tft->fillRect(_x - _velocity_x, _y - _velocity_y, _width + 4, _height + 4, _bg_c);
    img.pushSprite(_x, _y);    
    move();   
    _time = millis();
}

}