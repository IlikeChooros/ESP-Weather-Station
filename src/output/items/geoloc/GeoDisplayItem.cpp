#include "GeoDisplayItem.h"

GeoDisplayItem::
GeoDisplayItem(
    TFT_eSPI* tft,
    City_info& city_info,
    uint16_t x,
    uint16_t y,
    uint16_t bg_c
): tft(tft), info(city_info),
x(x), y(y), bg_c(bg_c),
state(city_info.state != "null") {

    std::unique_ptr<TextWrapper> tw(new TextWrapper(tft));
    tft->loadFont(EXTENDED_LATIN);
    uint16_t len;
    to_print = tw->prepare(240, 10)->wrapBegin(std::forward<String>(city_info.name));
    to_print += " " + info.country;
    len = tft->textWidth(to_print);
    y += tft->fontHeight() + 7;
    tft->unloadFont();
    
    if (state){
        tft->loadFont(EXTENDED_LATIN_SMALL);
        len = tft->textWidth(info.state) > len ? tft->textWidth(info.state) : len;
        y += tft->fontHeight() + 5;
        tft->unloadFont();
    }
    this->w = len + 4;
    this->h = y - this->y;        
}

void GeoDisplayItem::
draw(){
    tft->setTextColor(TFT_LIGHTGREY, bg_c);
    tft->loadFont(EXTENDED_LATIN);
    uint16_t y(this->y + 5), w(this->w - 4);
    tft->drawCentreString(to_print, x, y, 2);
    y += tft->fontHeight();
    tft->unloadFont();

    if (state){
        tft->loadFont(EXTENDED_LATIN_SMALL);  
        tft->drawCentreString(info.state, x, y + 5, 2);
        tft->unloadFont();
    }
    tft->drawFastHLine(x - w/2, y, w, TFT_DARKGREY);    
}

void GeoDisplayItem::
clear(){
    tft->fillRect(x - w/2, y, w, h, bg_c);
}
