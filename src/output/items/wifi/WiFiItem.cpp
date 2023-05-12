#include "WiFiItem.h"

WiFiItem::WiFiItem(
    TFT_eSPI *tft, 
    uint16_t x, 
    uint16_t y, 
    uint8_t size, 
    uint16_t background_color
): tft(tft), x(x), y(y), size(size), 
background_color(background_color),
idx(STRONG_WIFI), prev_idx(STRONG_WIFI) {}

void WiFiItem::
draw(bool forceDraw){
    std::unique_ptr<Icon> icon(matchIcon());
    if (!forceDraw && prev_idx == idx){
        return;
    }
    icon->draw();
}

Icon* WiFiItem::
matchIcon(){
    int8_t strenght = WiFi.RSSI();
    prev_idx = idx;    

    if (WiFi.status() != WL_CONNECTED){
        idx = LOST_WIFI;
        return new WiFiIconLost(tft, x, y, size, background_color);
    }
    // strenght (-35 to 0)
    if (strenght > -35){
        idx = SUPER_WIFI;
        return new WiFiIconSuperStrong(tft,x,y,size,background_color);
    }
    // strenght (-55 to -35)
    else if(strenght > - 55){
        idx = STRONG_WIFI;
        return new WiFiIconStrong(tft,x,y,size,background_color);
    }
    // strenght (-75 to -55)
    else if (strenght > -85){
        idx = MEDIUM_WIFI;
        return new WiFiIconMedium(tft,x,y,size,background_color);
    }
    // strenght (-128 to -55)
    else {
        idx = WEAK_WIFI;
        return new WiFiIconWeak(tft,x,y,size,background_color);
    }
}