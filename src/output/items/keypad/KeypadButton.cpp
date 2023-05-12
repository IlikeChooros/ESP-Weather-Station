#include "KeypadButton.h"

KeypadButton::
KeypadButton(
    TFT_eSPI* tft, 
    int16_t x, 
    int16_t y, 
    int16_t width, 
    int16_t height, 
    String name
): TouchButton(x,y,width,height),
name(name), tft(tft),
touch_color(0x2104),
text_color(TFT_LIGHTGREY) {}

void KeypadButton::
draw(bool){
    draw_(this->color);
}

void KeypadButton::
draw_(uint16_t color){
    tft->setTextColor(text_color, color);
    tft->fillRect(x,y,width,height,color);
    tft->drawRect(x,y,width,height,text_color);

    if (name == " "){
        tft->drawCentreString("SPACE", x+width/2, y + (height - LATIN_HEIGHT)/2 + 3, 2);
        return;
    }

    tft->drawCentreString(name, x+width/2, y + (height - LATIN_HEIGHT)/2, 2);
    
}


KeypadButton* KeypadButton::
custom_font(String font){
    this->font = font;
    return this;
}

void KeypadButton::
on_touch(){
    if (font.isEmpty())
        tft->loadFont(LATIN);
    else
        tft->loadFont(font);
    draw_(touch_color);
    tft->unloadFont();
}

String KeypadButton::
get_str(){
    return this->name;
}