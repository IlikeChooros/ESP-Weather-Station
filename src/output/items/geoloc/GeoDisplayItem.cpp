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
x(x), y(y), h(h), w(w) {}

void
GeoDisplayItem::
draw()
{
    tft->fillRect(x,y,w,h,TFT_BLACK);
    constexpr uint8_t offset = 10;

    tft->setTextColor(TFT_LIGHTGREY, TFT_BLACK);

    uint16_t x = this->x + 5,
             y = this->y + 5;

    tft->loadFont(LATIN);
    tft->drawCentreString(info.name, x+w/2, y, 2);
    tft->unloadFont();

    tft->loadFont(WEATHER_FONT);
    y += tft->fontHeight() + 5;
    tft->setCursor(x,y);
    tft->print("Country:");
    y += tft->fontHeight();
    tft->setCursor(x+offset,y);
    tft->print(info.country);
    y += tft->fontHeight();

    if (info.state != "null"){
        tft->setCursor(x,y);
        y += tft->fontHeight();
        tft->print("State:");

        tft->setCursor(x+offset,y);
        y += tft->fontHeight();
        tft->print(info.state);
    }

    tft->setCursor(x,y);
    y += tft->fontHeight();
    tft->print("Latitude:");

    tft->setCursor(x+offset,y);
    y += tft->fontHeight();
    tft->print(info.lat, 4);

    tft->setCursor(x,y);
    y += tft->fontHeight();
    tft->print("Longitude:");

    tft->setCursor(x+offset,y);
    y += tft->fontHeight();
    tft->print(info.lon, 4);
    tft->unloadFont();
}
