#include "ListItem.h"

ListItem::
ListItem(
    TFT_eSPI* tft,
    int16_t x,
    int16_t y,
    int16_t width,
    int16_t height
): TouchButton(x, y, width, height),
tft(tft), marked_(false), wrap(true) {}

void
ListItem::
draw(bool forceDraw)
{
    if(!forceDraw){
        return;
    }
    draw_(0x10A3);
}

void
ListItem::
draw_(uint16_t color)
{
    if(data.empty()){
        return;
    }
    uint16_t x = this->x, y = this->y;

    tft->fillRect(x, y, width, height, color);
    tft->drawRect(x, y, width, height, data.at(0).color);

    x+=5;
    y+=7;
    tft->loadFont(data.at(0).font);
    for (auto i : data)
    {
        tft->setTextColor(i.color, color);
        
        if (!i.same_line){
            y += tft->fontHeight();
            x = this->x+5;
        }

        String str = i.string, temp;

        if (!wrap){
            temp = str;
        }
        else{
            if (str.length() < 17){
                temp = str;
            }
            else{
                temp = str.substring(0, 14);
                temp += "...";
            }
        }
        x += tft->drawString(temp, x, y);
        x += 10;
    }
    tft->unloadFont();

    if (marked_){
        drawPickIcon(tft, x+0.9f*width, y, 0.1f*width, TFT_GREENYELLOW);
    }
}

std::vector<print_data>&
ListItem::stored(){
    return data;
}

void
ListItem::
on_touch(){
    draw_(0x0861);
}

ListItem*
ListItem::
set_position(Point& pos){
    this->x = pos.x;
    this->y = pos.y;
    return this;
}

ListItem*
ListItem::
marked(bool marked){
    this->marked_ = marked;
    return this;
}

ListItem*
ListItem::
wrap_text(bool wrap){
    this->wrap = wrap;
    return this;
}

ListItem*
ListItem::
set_data(
    String str,
    bool same_line,
    String font,
    uint16_t text_color
)
{
    tft->loadFont(font);
    std::unique_ptr<TextWrapper> tw(new TextWrapper(tft));  
    data.push_back(print_data(tw->prepare(width, 20)->wrapBegin(std::forward<String>(str)), font, text_color, same_line));
    tft->unloadFont();
    return this;
}