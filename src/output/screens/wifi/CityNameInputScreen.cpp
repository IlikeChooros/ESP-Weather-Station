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
CityNameInputScreen::
~CityNameInputScreen(){
    delete enter_button;
    delete return_button;
    delete keyboard;
    delete inputfield;
}

void
CityNameInputScreen::
draw(bool forceDraw){
    keyboard->draw(forceDraw);
    inputfield->draw(forceDraw);
    inputfield->blink();
    enter_button->draw(forceDraw);
    return_button->draw(forceDraw);
    draw_title(forceDraw);
}

void
CityNameInputScreen::
draw_title(bool forceDraw){
    if (!forceDraw){
        return;
    }
    tft->loadFont(NOTE_FONT12);
    tft->setTextColor(TFT_WHITE, bg_c);
    tft->drawCentreString("Enter desired location", 160, 5, 2);
    tft->unloadFont();
}


void 
CityNameInputScreen::
check(Point* pos){
    change_ = false;
    
    if (return_button->check(pos->x, pos->y)){
        change_ = true;
        return;
    }
    if(enter_button->check(pos->x, pos->y)){
        enter();
        return;
    }
    std::unique_ptr<KeyInfo> info(keyboard->check(pos));

    switch(info->info)
    {
        case IGNORE:
            break;
        case DELETE:
            inputfield->del();
            break;
        case NORMAL_BUTTON:
            inputfield->add_input(info->str);
            break;
    }  
}

void
CityNameInputScreen::
enter()
{
    load_main_ = draw_get(inputfield->get_input());

    // On failed location search
    if (!load_main_){
        tft->fillRect(55, 70, 210, 100, bg_c);
        keyboard->draw(true);
        return;
    }
    EEPROM.begin(EEPROM_SIZE);
    uint8_t number_of_cities = EEPROM.read(CITY_NAME_IDX);
    EEPROM.end();
    if (number_of_cities >= MAX_CITIES){   
        load_main_ = false;
        override_location();        
        return;
    }
    set_new_location();
}

void
CityNameInputScreen::
set_new_location(){
    std::unique_ptr<GeoLocScreen> geo_sc(new GeoLocScreen(tft, wclient, ts));
    
    // set_loaction also resets waitForGeoLoc and picked flags
    geo_sc->set_location(inputfield->get_input());
    tft->fillScreen(bg_c);
    geo_sc->draw(true);

    while(waitForGeoLoc){
        geo_sc->check();
    }
    // User chose valid city 
    if (geo_sc->is_picked()){
        read_mem.writeNewCity(inputfield->get_input(), geo_pos);
        wclient->_init_(inputfield->get_input(), geo_pos);
        load_main_ = true;
    }
    else{
        tft->fillScreen(bg_c);
        draw(true);
    }
}

void
CityNameInputScreen::
override_location(){
    std::unique_ptr<GeoLocScreen> geo_sc(new GeoLocScreen(tft, wclient, ts));

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
        using setscreen = settings::PickOptionScreen;
        std::unique_ptr<setscreen> set_sc(new setscreen(tft, ts));

        // Read from EEPROM saved cities
        auto cities = read_mem.cities(false);
        std::vector<print_data> data;
        for (auto i : cities){
            data.push_back(print_data(i.first, LATIN, TFT_LIGHTGREY, true));
        }
        set_sc
        ->prepare(data)
        ->set_title(String("Pick city to override"))
        ->init();

        set_sc->draw(true);
        // Override screen
        while(!set_sc->load_main()){
            set_sc->check();
        }
        // User exited override
        if(!set_sc->picked()){
            tft->fillScreen(bg_c);
            draw(true);
            return;
        }
        // User chose city to override
        settings::picked_list pick = set_sc->get_picked();
        read_mem.overwriteCity(inputfield->get_input(), geo_pos, pick.idx);
        wclient->_init_(inputfield->get_input(), geo_pos);
        load_main_ = true;
    }
    else{
        tft->fillScreen(bg_c);
        draw(true);
    }  
}