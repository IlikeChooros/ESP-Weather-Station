#include "TextWrapper.h"

TextWrapper::
TextWrapper(TFT_eSPI* tft):
tft(tft), max_width(0), margin(0) {}


TextWrapper* TextWrapper::
prepare(uint16_t max_width, uint16_t margin){
    this->max_width = max_width;
    this->margin = margin;
    return this;
}

String TextWrapper::
wrapEnd(String&& text){
    end_cursor = text.length();
    start_cursor = 0;
    while (tft->textWidth(text.substring(start_cursor, end_cursor)) >= max_width - margin){
        start_cursor++;
    }    
    return text.substring(start_cursor, end_cursor);
}

String TextWrapper::
wrapBegin(String&& text){
    end_cursor = text.length();
    start_cursor = 0;
    while (tft->textWidth(text.substring(start_cursor, end_cursor)) >= max_width - margin){
        end_cursor--;
    }    
    return text.substring(start_cursor, end_cursor);
}