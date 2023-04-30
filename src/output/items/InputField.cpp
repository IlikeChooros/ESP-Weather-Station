#include "InputField.h"

InputField::InputField(
    TFT_eSPI* tft, 
    int16_t x, 
    int16_t y, 
    int16_t width, 
    int16_t height
): _prev_state(false), 
_cache_time(500), cursor(""),
_last_check(millis()), tft(tft), x(x), 
y(y), width(width), height(height),
input(""), last_lenght(0), last_print(0) {}

void 
InputField::
draw(bool forceDraw){
    if(!forceDraw){
        return;
    }

    tft->loadFont(LATIN);
    tft->setTextColor(TFT_WHITE, INPUT_FIELD_BG);

    tft->fillRect(x,y,width,height, INPUT_FIELD_BG);
    tft->drawRect(x,y,width,height, TFT_WHITE);

    uint16_t x = this->x + 3,
             y = this->y + (height - LATIN_HEIGHT)/2;

    String temp;
    if (input.length() < 13){
        temp = input;
    }
    else{
        temp = input.substring(input.length()-12,input.length());
    }
    last_lenght = tft->drawString(temp, x, y);
    _cursor_x = tft->getCursorX();
    tft->unloadFont();
    blink(false);
}

void 
InputField::
add_input(String input){
    this->input += input;
    cursor = input;
    draw(true);
}

String 
InputField::
get_input(){
    return this->input;
}

void 
InputField::
del(){
    if (input == "" || input.length() == 0){
        return;
    }
    cursor = String(input.charAt(input.length()-1));
    this->input.remove(input.length()-1);
    draw(true);
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

