#include "GeoLocItem.h"

extern int8_t geo_pos = 0;
extern uint8_t total_geo_size = 0;

GeoLocItem::
GeoLocItem(
    TFT_eSPI* tft, 
    WeatherClient* wclient
): tft(tft), wclient(wclient)
{
    display = new GeoDisplayItem*[5]{};
}

void
GeoLocItem::
draw(bool forceDraw)
{
    if (data.size())
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
        display[i] = new GeoDisplayItem(this->tft, *info,45, 40, 230, 160);
        delete info;
    }

    total_geo_size = data.size();
}

void
GeoLocItem::
clear()
{
    while(!data.is_empty())
    {
        data.pop_back();
    }
    data.~Vector();

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
    if (data.is_empty())
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