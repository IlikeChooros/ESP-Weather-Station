#include "GeoLocScreen.h"

extern bool waitForGeoLoc = true;
extern uint8_t total_geo_size;
extern uint8_t geo_pos;

static uint8_t current_pos = 255;
static bool picked = false;
static uint8_t prev_pos = 0;

void
geo_pick(void)
{
    picked = false;
}

void
finish_geo_setup(void)
{
    waitForGeoLoc = false;
    picked = true;
}

GeoLocScreen::
~GeoLocScreen()
{
    for (uint8_t i=0; i<4; ++i)
    {
        delete buttons[i];
    }

    delete buttons;
    geoitem->clear();
    delete geoitem;
}

GeoLocScreen::
GeoLocScreen(
    TFT_eSPI *tft,
    WeatherClient* wclient,
    TouchScreen* ts
): tft(tft), ts(ts)
{
    buttons = new CustomButton* [4]{
        new CustomButton(tft, 45, 10, 30, 30, 0x3CE6), // enter button
        new CustomButton(tft, 245, 10, 30, 30, TFT_RED),  // exit button
        new CustomButton(tft, 45, 210, 40, 25, TFT_WHITE),
        new CustomButton(tft, 235, 210, 40, 25, TFT_WHITE)
    };

    buttons[0]
    ->set_draw(drawTickButton)
    ->set_on_press(finish_geo_setup);

    buttons[1]
    ->set_draw(drawExitButton)
    ->set_on_press(geo_pick);

    buttons[2]
    ->set_draw_wh(drawLeftArrow);

    buttons[3]
    ->set_draw_wh(drawRightArrow);

    geoitem = new GeoLocItem(
        tft, wclient,
        45, 40, 230, 160);
}

void
GeoLocScreen::
check(void)
{
    Point* pos = ts->read_touch();

    if (!pos)
    {
        return;
    }

    for (uint8_t i=0; i<4; ++i)
    {
        if(!buttons[i]->check(pos->x, pos->y))
        {
            continue;
        }

        if (i == 2 || i == 3)
        {
            geoitem->change(Move(i-2));
        }
        return;
    }
}

void
GeoLocScreen::
draw_window(bool forceDraw)
{
    Serial.println
    ("DRAW WINDOW: "+String(total_geo_size)+
    " current_pos: "+String(current_pos)+
    "  geo: "+String(geo_pos));

    if(forceDraw)
    {
        Serial.println("force = true");
        tft->fillRect(40, 5, 240, 230, 0x18E3);
        tft->drawRect(40, 5, 240, 230, 0x2985);
    }

    if (!total_geo_size || (current_pos == geo_pos))
    {
        return;
    }

    tft->setTextColor(TFT_WHITE, 0x18E3, true);
    tft->setTextSize(2);
    tft->drawCentreString(String(geo_pos+1)+" / "+String(total_geo_size), 160, 20, 2);

    Serial.println("END DRAW WINDOW");
}

void
GeoLocScreen::
draw(bool forceDraw)
{
    draw_window(forceDraw);
    for (uint8_t i=0; i<4; ++i)
    {
        Serial.println("buttons-> draw "+String(i));
        buttons[i]->draw(forceDraw);
    }
    Serial.println("AFTER FOR");
    geoitem->draw(forceDraw);
    Serial.println("END DRAW");
}

void
GeoLocScreen::
set_location(String location)
{
    geoitem->set_loctation(location);
}

bool
GeoLocScreen::
is_picked(void)
{
    return picked;
}