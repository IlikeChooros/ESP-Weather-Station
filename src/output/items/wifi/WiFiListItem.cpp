#include "WiFiListItem.h"
WiFiListItem::
WiFiListItem(
    TFT_eSPI* tft, 
    int16_t x, 
    int16_t y, 
    int16_t width, 
    int16_t height, 
    String ssid, 
    bool password_saved,
    int8_t strenght, 
    uint16_t bg_c
): TouchButton(x,y,width,height),
tft(tft), ssid(ssid), password_saved(password_saved),
strenght(strenght), bg_c(bg_c) {}

int8_t 
WiFiListItem::
get_strenght(){
    return this->strenght;
}

void
WiFiListItem::
set_save(bool saved){
    password_saved = saved;
}

bool 
WiFiListItem::
is_saved(){
    return this->password_saved;
}

String 
WiFiListItem::
get_ssid(){
    return this->ssid;
}

void 
WiFiListItem::
draw(bool forceDraw)
{
    if(!forceDraw){
        return;
    }
    tft->setTextColor(TFT_WHITE);
    tft->setTextSize(2);
    tft->setTextFont(2);
    tft->fillRect(x,y,width,height,color);
    tft->drawRect(x,y,width,height,TFT_LIGHTGREY);
    
    Icon* icon;
    if (this->password_saved){
        icon = new LockerOpened(tft, x+0.82f*width, y+0.15f*height, 0.08f*width, color);
    }
    else{
        icon = new LockerLocked(tft, x+0.82f*width, y+0.15f*height, 0.08f*width, color);
    }
    icon->draw();
    delete icon;
    
    WiFiStrenghtItem* wifi_str = new WiFiStrenghtItem (tft,x+0.91f*width, y+roundf(0.2f*height), 0.08f*width, color);
    wifi_str->draw(strenght);
    delete wifi_str;

    //-------------------
    // drawing wifi ssid
    tft->setCursor(x+0.05f*width, y);

    String temp;
    if (ssid.length()<14){
        temp = ssid;
    }
    else{
        temp = ssid.substring(0,11);
        temp += "...";
    }
    tft->print(temp);
}
