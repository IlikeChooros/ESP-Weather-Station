#include "GeoLocItem.h"

static int8_t pos = 0;

GeoLocItem::
GeoLocItem(
    TFT_eSPI* tft, 
    WeatherClient* wclient
): tft(tft), wclient(wclient)
{
    display = new GeoDisplayItem*[5]{
        0,
        0,
        0,
        0,
        0
    };
}

void
GeoLocItem::
draw(bool forceDraw)
{
    if(!forceDraw)
    {
        return;
    }

    display[pos]->draw();
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
            break;
        }

        data.push_back(*info);
        display[i] = new GeoDisplayItem(this->tft, *info,45, 40, 230, 180);
        delete info;
    }
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
}


void
GeoLocItem::
change(Move dir)
{
    if (dir == RIGHT)
    {
        pos = pos < data.size()-1 ? pos+1 : 0;
        return;
    }
    pos = pos > 0 ? pos - 1 : data.size()-1;
}