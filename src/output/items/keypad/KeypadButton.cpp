#include "KeypadButton.h"

void 
KeypadButton::
draw(bool forceDraw)
{
    if(!forceDraw){
        return;
    }
    draw_(this->color);
}

void 
KeypadButton::
draw_(uint16_t color)
{
    tft->setTextColor(text_color, color);
    tft->fillRect(x,y,width,height,color);
    tft->drawRect(x,y,width,height,text_color);

    if (name == " "){
        tft->drawCentreString("SPACE", x+width/2, y + (height - LATIN_HEIGHT)/2, 2);
        return;
    }

    if (wrap){
        for (uint8_t i=0; i<name.length(); i++){
            tft->setCursor(x+0.3f*width, y + i*25+height*0.1f);
            tft->print(name[i]);
        }
    }
    else{
        tft->drawCentreString(name, x+width/2, y + (height - LATIN_HEIGHT)/2, 2);
    }
}

void 
KeypadButton::
on_touch(){
    //tft->loadFont(Arial28);
    draw_(touch_color);
    //tft->unloadFont();
}

String 
KeypadButton::
get_str(){
    return this->name;
}

void 
KeypadButton::
set_wrap(){
    this->wrap = true;
}