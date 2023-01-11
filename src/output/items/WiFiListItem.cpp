#include "WiFiListItem.h"

int8_t WiFiListItem::get_strenght()
{
    return this->strenght;
}

bool WiFiListItem::is_saved()
{
    return this->password_saved;
}

String WiFiListItem::get_ssid()
{
    return this->ssid;
}

void WiFiListItem::draw()
{
    tft->setTextColor(TFT_WHITE);
    tft->setTextSize(2);
    tft->setTextFont(2);
    tft->fillRect(x,y,width,height,color);
    tft->drawRect(x,y,width,height,TFT_LIGHTGREY);
    
    Icon* icon;
    if (this->password_saved)
    {
        icon = new LockerOpened(tft, x+0.82f*width, y+0.1f*height, 0.08f*width, color);
    }
    else
    {
        icon = new LockerLocked(tft, x+0.82f*width, y+0.1f*height, 0.08f*width, color);
    }
    icon->draw();
    delete icon;
    
    WiFiStrenghtItem* wifi_str = new WiFiStrenghtItem(tft,x+0.92f*width, y+0.1f*height, 0.08f*width, color);
    wifi_str->draw(strenght);
    delete wifi_str;

    //-------------------
    // drawing wifi ssid
    tft->setCursor(x+0.05f*width, y+0.05f*height);

    String temp;
    if (ssid.length()<14)
    {
        temp = ssid;
    }
    else{
        temp = ssid.substring(0,11);
        temp += "...";
    }

    tft->print(temp);
}
