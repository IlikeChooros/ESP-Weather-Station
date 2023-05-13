#include "GeoLocItem.h"

extern int8_t geo_pos = 0;
extern uint8_t total_geo_size = 0;

GeoLocItem::
GeoLocItem(
    TFT_eSPI* tft, 
    WeatherClient* wclient,
    uint16_t x,
    uint16_t y,
    uint16_t bg_c
): tft(tft), wclient(wclient),
x(x), y(y), bg_c(bg_c), display(0) {}

GeoLocItem::
~GeoLocItem(){
    clear();
}

void
GeoLocItem::
draw(bool forceDraw)
{
    // Probably should scale this
    if (data.empty()){
        tft->fillRect(45, 40, 230, 160, bg_c);
        tft->loadFont(NOTE_FONT16);
        tft->setTextColor(TFT_LIGHTGREY, bg_c);
        tft->setCursor(45,40);
        tft->print("No data...");
        tft->unloadFont();
    }

    if(!(forceDraw && display[geo_pos])){
        return;
    }

    display[geo_pos]->draw();
}

void GeoLocItem::
set_loctation(String city_name){
    clear();
        
    display = new GeoDisplayItem* [5];
    data = wclient->get_all_cities_info(city_name);
    uint8_t j = 0;
    for(auto i : data){
        display[j] = new GeoDisplayItem(tft, i, x, y, bg_c);
        ++j;
    }
    total_geo_size = data.size();
}

void GeoLocItem::
clear(){
    data.clear();
    if (!display){
        return;
    }

    for (uint8_t i=0; i<5; ++i){
        if (!display[i]){
            break;
        }
        delete display[i];
    }
    delete [] display;
}

void GeoLocItem::
change(Move dir){
    if (data.empty()){
        return;
    }
    display[geo_pos]->clear();
    if (dir == Move::RIGHT){
        geo_pos = geo_pos < data.size()-1 ? geo_pos+1 : 0;
        return;
    }
    geo_pos = geo_pos > 0 ? geo_pos - 1 : data.size()-1;
}