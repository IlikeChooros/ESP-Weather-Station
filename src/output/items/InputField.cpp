#include "InputField.h"

InputField::InputField(
    TFT_eSPI* tft, 
    int16_t x, 
    int16_t y, 
    int16_t width, 
    int16_t height
): _prev_state(false), 
_cache_time(500),
_last_check(millis()),
tft(tft), x(x), y(y),
width(width), height(height),
input("") {}

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

    tft->setCursor(x + 3,y);

    String temp;
    if (this->input.length()<14){
        temp = input;
    }
    else{
        temp = input.substring(input.length()-13,input.length());
    }
    tft->print(temp);
    _cursor_x = tft->getCursorX();
    tft->unloadFont();
}


void 
InputField::
add_input(String input){
    this->input += input;
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
    this->input.remove(input.length()-1);
    draw(true);
}

void
InputField::
blink(){
    if (millis() - _last_check < _cache_time){
        return;
    }

    uint16_t color = _prev_state ? INPUT_FIELD_BG : TFT_WHITE;
    _prev_state = !_prev_state;
    tft->loadFont(LATIN);
    tft->setTextColor(color, INPUT_FIELD_BG);
    tft->drawString("|", _cursor_x, y + (height - LATIN_HEIGHT)/2, 2);
    _last_check = millis();
    tft->unloadFont();
}

