#include "InputField.h"

InputField::InputField(
    TFT_eSPI* tft, 
    int16_t x, 
    int16_t y, 
    int16_t width, 
    int16_t height
): _prev_state(false), _cache_time(500),
_last_check(millis()), tft(tft), _start_cursor(0), 
width(width), height(height), x(x), y(y),
input(""), to_print(""), _end_cursor(0) {}

void 
InputField::
draw(bool forceDraw){
    if(!forceDraw){
        return;
    }

    //tft->loadFont(LATIN);
    tft->setTextColor(TFT_WHITE, INPUT_FIELD_BG);

    tft->fillRect(x,y,width,height, INPUT_FIELD_BG);
    tft->drawRect(x,y,width,height, TFT_WHITE);

    uint16_t x = this->x + 3,
             y = this->y + (height - LATIN_HEIGHT)/2;

    tft->drawString(to_print, x, y);
    _cursor_x = tft->getCursorX();
    tft->unloadFont();
    blink(false);
}

void 
InputField::
add_input(String inp){
    this->input += inp;
    _end_cursor = input.length();
    tft->loadFont(LATIN);
    while (tft->textWidth(input.substring(_start_cursor, _end_cursor)) >= width - 30){
        _start_cursor++;
    }    
    to_print = input.substring(_start_cursor, _end_cursor);
    draw(true);
    tft->unloadFont();
}

void 
InputField::
del(){
    if (input == "" || input.length() == 0){
        return;
    }
    this->input.remove(_end_cursor-1);
    tft->loadFont(LATIN);
    _end_cursor = input.length();
    while (_start_cursor > 0 && tft->textWidth(input.substring(_start_cursor, _end_cursor)) <= width - 30){
        _start_cursor--;
    }
    to_print = input.substring(_start_cursor, _end_cursor);
    draw(true);
    tft->unloadFont();
}

String 
InputField::
get_input(){
    return this->input;
}

void
InputField::
blink(bool erase){
    uint16_t color = erase ? INPUT_FIELD_BG : TFT_WHITE;
    tft->setTextSize(2);
    tft->setTextColor(color);
    tft->drawString("|", _cursor_x, y + 5, 2);
}

void
InputField::
blink(){
    if (millis() - _last_check < _cache_time){
        return;
    }
    blink(_prev_state);
    _prev_state = !_prev_state;
    _last_check = millis();
}

