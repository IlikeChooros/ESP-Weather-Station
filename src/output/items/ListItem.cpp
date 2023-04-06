#include "ListItem.h"

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

    for (auto i : data)
    {
        tft->setTextColor(i.color);
        tft->setTextSize(i.size);
        tft->setTextFont(i.font);

        if (!i.same_line){
            y += i.font*i.size*5+5;
            x = this->x+5;
        }

        String str = i.string, temp;
        if (str.length() < 17){
            temp = str;
        }
        else{
            temp = str.substring(0, 14);
            temp += "...";
        }
        x += tft->drawString(temp, x, y);
        x += 10;
    }

    if (marked_){
        drawPickIcon(tft, x+0.9f*width, y, height*0.8f, TFT_GREENYELLOW);
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
ListItem::set_position(Point& pos){
    x = pos.x;
    y = pos.y;
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
set_data(
    String str,
    bool same_line,
    uint8_t font,
    uint8_t text_size,
    uint16_t text_color
)
{
    data.push_back(print_data(str, font, text_size, text_color, same_line));
    return this;
}