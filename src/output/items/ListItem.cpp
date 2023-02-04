#include "ListItem.h"

void
ListItem::
draw(bool forceDraw)
{
    if(!forceDraw)
    {
        return;
    }
    draw_(0x10A3);
}

void
ListItem::
draw_(uint16_t color)
{
    if(data.is_empty())
    {
        return;
    }
    uint16_t x = this->x, y = this->y;

    tft->fillRect(x, y, width, height, color);
    tft->drawRect(x, y, width, height, data.at(0).color);

    x+=5;

    for (uint8_t j=0; j< data.size(); j++)
    {
        tft->setTextColor(data.at(j).color);
        tft->setTextSize(data.at(j).size);
        tft->setTextFont(data.at(j).font);

        if (!data.at(j).same_line)
        {
            y += data.at(j).font*data.at(j).size*5+5;
            x = this->x+5;
        }

        String str = data.at(j).string,
        temp;
        if (str.length() < 17)
        {
            temp = str;
        }
        else{
            temp = str.substring(0, 14);
            temp += "...";
        }
        x += tft->drawString(temp, x, y);
        x += 10;
    }

    if (marked_)
    {
        drawPickIcon(tft, x+0.9f*width, y, height*0.8f, TFT_GREENYELLOW);
    }
}


void
ListItem::
on_touch()
{
    draw_(0x0861);
}


ListItem*
ListItem::
marked(bool marked)
{
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
    print_data* p = new print_data {str, font, text_size, text_color, same_line};
    Serial.println("PRINT_DATA: "+str);
    data.push_back(*p);
    delete p;
}