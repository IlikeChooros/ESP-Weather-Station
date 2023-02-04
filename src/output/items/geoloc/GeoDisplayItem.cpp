#include "GeoDisplayItem.h"

GeoDisplayItem::
GeoDisplayItem(
    TFT_eSPI* tft,
    City_info& city_info,
    uint16_t x,
    uint16_t y,
    uint16_t w,
    uint16_t h
): tft(tft), info(city_info),
x(x), y(y), h(h), w(w)
{}

void
GeoDisplayItem::
draw()
{
    tft->fillRect(x,y,w,h,TFT_BLACK);
    tft->setTextFont(2);
    tft->setTextSize(1);
    tft->setTextColor(TFT_LIGHTGREY);

    uint16_t x = this->x + 5,
                y = this->y + 10;


    tft->setCursor(x,y);
    tft->print("Country:");
    y += tft->fontHeight();
    tft->print(info.country);

    if (info.state != "null")
    {
        y += tft->fontHeight();
        tft->print("State:");

        y += tft->fontHeight();
        tft->print(info.state);
    }

    y += tft->fontHeight();
    tft->print("Latitude:");
    y += tft->fontHeight();
    tft->print(info.lat, 4);

    y += tft->fontHeight();
    tft->print("Longitude:");
    y += tft->fontHeight();
    tft->print(info.lon, 4);
}
