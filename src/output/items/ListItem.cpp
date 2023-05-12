#include "ListItem.h"

ListItem::
ListItem(
    TFT_eSPI* tft,
    int16_t x,
    int16_t y,
    int16_t width,
    int16_t height
): TouchButton(x, y, width, height), img(0),
tft(tft), wrap(true), prev_cursor(0) {}

ListItem::
~ListItem(){
    delete img;
}

void
ListItem::
draw(bool forceDraw){
    if(!forceDraw){
        return;
    }
    draw_(0x10A3);
}

void ListItem::
on_touch(){
    if (!img){
        draw_(0x0861);
        return;
    }
    img->drawRect(0, 0, width, height, TFT_GREEN);
    draw_(0x0861);
    img->drawRect(0, 0, width, height, TFT_LIGHTGREY); 
}

void ListItem::
draw_(uint16_t color)
{
    if(to_print.empty()){
        return;
    }

    if(img){
        img->pushSprite(x, y);
        return;
    }

    uint16_t x = this->x, y = this->y;

    tft->fillRect(x, y, width, height, color);
    tft->drawRect(x, y, width, height, to_print.at(0).color);

    x+=5;
    y+=7;
    uint16_t prev_height(0);
    for (auto i : to_print){
        tft->loadFont(i.font);
        tft->setTextColor(i.color, color);
        
        if (!i.same_line){
            y += prev_height+2;
            x = this->x+5;
        }
        x += tft->drawString(i.string, x, y);
        x += 10;
        prev_height = tft->fontHeight();
        tft->unloadFont();
    }
    
}

std::vector<print_data>& ListItem::
stored(){
    return data;
}

ListItem* ListItem::
createSprite(){
    if (img){
        return this;
    }
    img = new TFT_eSprite(tft);
    img->createSprite(width, height);
    img->fillSprite(0x10A3);
    img->drawRect(0, 0, width, height, to_print.at(0).color);
    uint16_t x = 5, y = 7, prev_height = 0;
    for (auto i : to_print){
        img->loadFont(i.font);
        img->setTextColor(i.color, 0x10A3);

        if (!i.same_line){
            y += prev_height+2;
            x = 5;
        }
        x += img->drawString(i.string, x, y);
        x += 10;
        prev_height = img->fontHeight();
        img->unloadFont();
    }
    return this;
}

ListItem* ListItem::
set_position(Point& pos){
    this->x = pos.x;
    this->y = pos.y;
    return this;
}

ListItem* ListItem::
wrap_text(bool wrap){
    this->wrap = wrap;
    return this;
}

ListItem* ListItem::
set_data(
    String str,
    bool same_line,
    String font,
    uint16_t text_color
)
{
    data.push_back(print_data(str, font, text_color, same_line)); 
    tft->loadFont(font);
    prev_cursor = same_line ? prev_cursor : 0;
    String temp;
    if (wrap){
        std::unique_ptr<TextWrapper> tw(new TextWrapper(tft));  
        temp = tw->prepare(width - prev_cursor, 10)->wrapBegin(std::forward<String>(str));
        temp += temp != str ? "..." : "";
    }    
    else{
        temp = str;
    }
    prev_cursor += tft->textWidth(temp) + 10;
    tft->unloadFont();    
    to_print.push_back(print_data(temp, font, text_color, same_line));     
    return this;
}