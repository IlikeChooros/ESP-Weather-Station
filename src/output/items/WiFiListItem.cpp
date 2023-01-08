#include "WiFiListItem.h"

WiFiListItem::WiFiListItem(TFT_eSPI* tft, int16_t x, int16_t y, int16_t width, int16_t height, String ssid, uint16_t bg_c)
{
    this->tft = tft;
    this->x = x;
    this->y = y;
    this->ssid = ssid;
    this->width = width;
    this->height = height;
    this->bg_c = bg_c;
    this->strenght = -50;
}

void WiFiListItem::set_strenght(int8_t str)
{
    this->strenght = str;
}

int8_t WiFiListItem::get_strenght()
{
    return this->strenght;
}

TouchButton* WiFiListItem::get_button()
{
    return new TouchButton(x,y,width,height);
}

void WiFiListItem::draw()
{
    tft->setTextColor(TFT_WHITE);
    tft->setTextSize(2);
    tft->setTextFont(2);
    tft->fillRect(x,y,width,height,BUTTON_BG);
    tft->drawRect(x,y,width,height,TFT_LIGHTGREY);
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