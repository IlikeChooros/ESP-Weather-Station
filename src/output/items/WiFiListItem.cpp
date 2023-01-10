#include "WiFiListItem.h"

int16_t WiFiListItem::get_int()
{
    return this->strenght;
}

void WiFiListItem::draw()
{
    tft->setTextColor(TFT_WHITE);
    tft->setTextSize(2);
    tft->setTextFont(2);
    tft->fillRect(x,y,width,height,color);
    tft->drawRect(x,y,width,height,TFT_LIGHTGREY);
    tft->setCursor(x+0.05f*width, y+0.05f*height);

    String temp;
    if (ssid.length()<15)
    {
        temp = ssid;
    }
    else{
        temp = ssid.substring(0,14);
        temp += "...";
    }

    tft->print(temp);

    // strenght (-30 to 0)
    if (strenght > -45)
    {
        tft->fillRect(x + 0.92f*width, y+0.15f*height, 0.05f*width, 0.7f*height, TFT_GREEN);
    }
    // strenght (-60 to -30)
    else if (strenght > -75)
    {
        tft->fillRect(x + 0.92f*width, y+0.15f*height, 0.05f*width, 0.7f*height, TFT_ORANGE);
    }
    else 
    {
        tft->fillRect(x + 0.92f*width, y+0.15f*height, 0.05f*width, 0.7f*height, TFT_RED);
    }
}

void WiFiListItem::on_touch()
{
    tft->setTextColor(TFT_WHITE);
    tft->setTextSize(2);
    tft->setTextFont(2);
    tft->fillRect(x,y,width,height,TFT_LIGHTGREY);
    tft->drawRect(x,y,width,height,TFT_DARKGREY);
    tft->setCursor(x+0.05f*width, y);
    tft->print(ssid);

    // strenght (-30 to 0)
    if (strenght > -45)
    {
        tft->fillRect(x + 0.92f*width, y+0.15f*height, 0.05f*width, 0.7f*height, TFT_GREEN);
    }
    // strenght (-60 to -30)
    else if (strenght > -75)
    {
        tft->fillRect(x + 0.92f*width, y+0.15f*height, 0.05f*width, 0.7f*height, TFT_ORANGE);
    }
    else 
    {
        tft->fillRect(x + 0.92f*width, y+0.15f*height, 0.05f*width, 0.7f*height, TFT_RED);
    }
}
