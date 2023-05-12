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
tft(tft), password_saved(password_saved),
strenght(strenght), bg_c(bg_c), ssid(ssid) {    
    std::unique_ptr<TextWrapper> tw(new TextWrapper(tft));      
    this->to_print = tw->prepare(width*0.7f, 5)->wrapBegin(std::forward<String>(ssid));
    to_print += to_print != ssid ? "..." : "";    
}

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
    
    WiFiStrenghtItem* wifi_str = new WiFiStrenghtItem (tft,x+0.91f*width, y+roundf(0.25f*height), 15, color);
    wifi_str->draw(strenght);
    delete wifi_str;

    //-------------------
    // drawing wifi ssid
    tft->setCursor(x+0.05f*width, y + (height - LATIN_HEIGHT)/2 + 2);
    tft->setTextColor(TFT_WHITE, color);
    tft->loadFont(LATIN);
    tft->print(to_print);
    tft->unloadFont();
}
