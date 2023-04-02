#include "GeoLocItem.h"

extern int8_t geo_pos = 0;
extern uint8_t total_geo_size = 0;

GeoLocItem::
GeoLocItem(
    TFT_eSPI* tft, 
    WeatherClient* wclient,
    uint16_t x,
    uint16_t y,
    uint16_t w,
    uint16_t h
): tft(tft), wclient(wclient)
{
    display = new GeoDisplayItem*[5]{};
}

void
GeoLocItem::
draw(bool forceDraw)
{
    if (data.empty())
    {
        tft->fillRect(45, 40, 230, 160,TFT_BLACK);
        tft->setTextFont(2);
        tft->setTextSize(1);
        tft->setTextColor(TFT_LIGHTGREY);
        tft->setCursor(45,40);
        tft->print("No data...");
    }

    if(!(forceDraw && display[geo_pos]))
    {
        Serial.println("NO GEO POS");
        return;
    }


    display[geo_pos]->draw();
}

void
GeoLocItem::
set_loctation
(String city_name)
{
    for (uint8_t i=0; i<5; ++i)
    {
        City_info* info = wclient->get_city_info(city_name, i);

        if (!info || info->country == "null")
        {
            delete info;
            break;
        }
        data.push_back(*info);
        display[i] = new GeoDisplayItem(this->tft, *info, x, y, w, h);
        delete info;
    }

    total_geo_size = data.size();
}

void
GeoLocItem::
clear()
{
    data.clear();
    for (uint8_t i=0; i<5; ++i)
    {
        delete display[i];
    }
    delete [] display;
}


void
GeoLocItem::
change(Move dir)
{
    if (data.empty())
    {
        return;
    }

    if (dir == Move::RIGHT)
    {
        geo_pos = geo_pos < data.size()-1 ? geo_pos+1 : 0;
        draw(true);
        return;
    }
    geo_pos = geo_pos > 0 ? geo_pos - 1 : data.size()-1;
    draw(true);
}