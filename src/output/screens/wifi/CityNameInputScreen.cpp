#include "CityNameInputScreen.h"

extern bool waitForGeoLoc;
extern uint8_t geo_pos;

CityNameInputScreen::
CityNameInputScreen(
    TFT_eSPI* tft,
    uint16_t bg_c,
    WeatherClient* wc,
    TouchScreen* ts
): CityNameScreen(tft, bg_c, wc, ts)
{
    keyboard = new Keyboard(tft);
    inputfield = new InputField(tft, 40, 20, 235, 40);

    enter_button = new CustomButton(tft, 280, 20, 35, 40,0x3CE6);
    enter_button
    ->set_draw(drawTickButton)
    ->touch_color(0x19E2);

    return_button = new CustomButton(tft, 5, 5, 30, 30, 0x8040);
    return_button
    ->set_draw(drawExitButton)
    ->touch_color(0x30C2);
}

void
CityNameInputScreen::
draw(bool forceDraw){
    keyboard->draw(forceDraw);
    inputfield->draw(forceDraw);
    inputfield->blink();
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

    if(enter_button->check(pos->x, pos->y)){
        enter();
        return;
    }
}

void
CityNameInputScreen::
save_data()
{
    uint8_t num = EEPROM.read(CITY_NAME_IDX);
    EEPROM.writeString(num*(CITY_NAME_LEN+1) + CITY_NAME_IDX + 2, inputfield->get_input());
    EEPROM.write(CITY_NAME_IDX, num+1);
    EEPROM.commit();
}

void
CityNameInputScreen::
enter()
{
    load_main_ = draw_get(inputfield->get_input(), 0);

    if (!load_main_){
        return;
    }

    EEPROM.begin(EEPROM_SIZE);
    if (EEPROM.read(CITY_NAME_IDX) >= MAX_CITIES){   
        load_main_ = false;
        override_location();
        EEPROM.end();
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

    // set_loaction also resets waitForGeoLoc and picked flags
    geo_sc->set_location(inputfield->get_input());
    geo_sc->draw(true);

    while(waitForGeoLoc){
        geo_sc->check();
    }

    // User chose valid city 
    if (geo_sc->is_picked()){
        tft->fillScreen(bg_c);
        settings::PickOptionScreen* set_sc = new settings::PickOptionScreen(tft, ts);

        uint16_t address = CITY_NAME_IDX + 2;
        // Read from EEPROM saved cities
        uint8_t repeat = EEPROM.read(CITY_NAME_IDX);
        std::vector<print_data> data;
        for (uint8_t i=0; i < repeat; ++i, address += CITY_NAME_LEN + 1){
            data.push_back(print_data(EEPROM.readString(address), 2, 2, TFT_LIGHTGREY, true));
        }
        set_sc
        ->prepare(data)
        ->set_title(String(F("Pick city to override")))
        ->init();

        set_sc->draw(true);
        // Override screen
        while(!set_sc->load_main()){
            set_sc->check();
        }
        // User exited override
        if(!set_sc->picked()){
            delete set_sc;
            delete geo_sc;
            return;
        }
        // User chose city to override
        settings::picked_list pick = set_sc->get_picked();
        EEPROM.begin(EEPROM_SIZE);
        address = CITY_NAME_IDX + 1 + pick.idx * (CITY_NAME_LEN + 1);
        EEPROM.write(address, geo_pos);
        EEPROM.writeString(address + 1, inputfield->get_input());
        EEPROM.commit();
        wclient->_init_(inputfield->get_input(), geo_pos);
        delete set_sc;
        load_main_ = true;
    }
    delete geo_sc;
}