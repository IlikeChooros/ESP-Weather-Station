#include "KeypadButton.h"

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