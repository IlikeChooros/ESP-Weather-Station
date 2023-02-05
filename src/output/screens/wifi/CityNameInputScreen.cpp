#include "CityNameInputScreen.h"

extern bool waitForGeoLoc;
CityNameInputScreen::
CityNameInputScreen(
    TFT_eSPI* tft,
    uint16_t bg_c,
    WeatherClient* wc,
    TouchScreen* ts
): CityNameScreen(tft, bg_c, wc, ts)
{
    keyboard = new Keyboard(tft);
    inputfield = new InputField(tft, 40, 20, 230, 40);

    enter_button = new CustomButton(tft, 275, 20, 35, 40,0x3CE6);
    enter_button
    ->set_draw(drawTickButton)
    ->touch_color(0x19E2);

    return_button = new KeypadButton(tft, 5, 5, 30, 30, "x");
    return_button->set_color(TFT_RED);
}

void
CityNameInputScreen::
draw(bool forceDraw)
{
    keyboard->draw(forceDraw);
    inputfield->draw(forceDraw);
    enter_button->draw(forceDraw);
    return_button->draw(forceDraw);
}

void 
CityNameInputScreen::
check(Point* pos)
{
    change_ = return_button->check(pos->x, pos->y);
    KeyInfo* info = keyboard->check(pos);

    if (info)
    {
        switch(info->info)
        {
            case IGNORE:
                return;
            case DELETE:
                inputfield->del();
                return;
            case NORMAL_BUTTON:
                inputfield->add_input(info->str);
                return;
        }
    }

    if(enter_button->check(pos->x, pos->y))
    {
        enter();
        return;
    }
}

void
CityNameInputScreen::
save_data()
{
    uint8_t num = EEPROM.read(CITY_NAME_IDX);

    if (num > MAX_CITIES)
    {
        EEPROM.write(CITY_NAME_IDX, 0);
        return;
    }

    EEPROM.writeString(num*(CITY_NAME_LEN+1) + CITY_NAME_IDX + 2, inputfield->get_input());
    EEPROM.write(CITY_NAME_IDX, num+1);
    EEPROM.commit();
}

void
CityNameInputScreen::
enter()
{
    load_main_ = draw_get(inputfield->get_input());

    if (!load_main_)
    {
        return;
    }

    EEPROM.begin(EEPROM_SIZE);
    if (EEPROM.read(CITY_NAME_IDX) >= MAX_CITIES)
    {   
        override_location();
        EEPROM.end();
        load_main_ = false;
        tft->fillScreen(bg_c);
        draw(true);
        return;
    }

    save_data();  
    EEPROM.end();
}

void
CityNameInputScreen::
override_location()
{
    GeoLocScreen* geo_sc = new GeoLocScreen(tft, wclient, ts);
    tft->fillScreen(bg_c);
    geo_sc->draw(true);
    while(waitForGeoLoc)
    {
        geo_sc->check();
    }

    if (geo_sc->is_picked())
    {
        save_data();
    }

    geo_sc->~GeoLocScreen();
    tft->fillScreen(bg_c);

    delete geo_sc;
}