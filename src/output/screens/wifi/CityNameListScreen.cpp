#include "CityNameListScreen.h"

CityNameListScreen::
CityNameListScreen(
    TFT_eSPI* tft,
    uint16_t bg_c,
    WeatherClient* wc,
    TouchScreen* ts
): CityNameScreen(tft, bg_c, wc, ts)
{
    set_new_location = new CustomButton(tft, 0, 180, 320, 60, 0x10A3);
    set_new_location
    ->touch_color(0x0861)
    ->set_draw(drawSetLocationButton);
    wifi = new WiFiItem(tft, 5,5,20, bg_c);
}

void
CityNameListScreen::
init()
{
    auto cities = read_mem.cities(true);
    number_of_saved_city_names = cities.size();
    number_of_saved_city_names = number_of_saved_city_names < MAX_CITIES ? number_of_saved_city_names : MAX_CITIES;
    if (!cities.empty()){
        city_list = new ListItem* [number_of_saved_city_names];
    }
    uint8_t count = 0;
    for (auto i : cities){
        city_names.push_back(i.first);
        city_list[count] = new ListItem(tft, 20, 30+count*(LIST_HEIGHT+5), LIST_WIDTH, LIST_HEIGHT);
        count++;
    }
}

void
CityNameListScreen::
set_city_info()
{
    EEPROM.begin(EEPROM_SIZE);

    uint16_t address = CITY_NAME_IDX + 1;
    for (uint8_t i=0; i<number_of_saved_city_names; i++){
        City_info* info =
        wclient->get_city_info(
            city_names.at(i), 
            EEPROM.read(address)
        );

        if (!info){
            number_of_saved_city_names = i;
            break;
        }

        city_info.push_back(std::forward<City_info>(*info));
        if (info->state == "null"){
            info->state = "";
        }

        city_list[i]
        ->set_data(city_names.at(i), true, LATIN, TFT_LIGHTGREY)
        ->set_data(info->country, true, LATIN, TFT_LIGHTGREY)
        ->set_data(info->state, false, LATIN, TFT_LIGHTGREY);

        address += CITY_NAME_LEN + 1;
    }
    EEPROM.end();
}

void
CityNameListScreen::
check(Point* pos)
{
    change_ = set_new_location->check(pos->x, pos->y);
    for (uint8_t i=0; i<number_of_saved_city_names; ++i){
        if(city_list[i]->check(pos->x, pos->y)){
            load_main_ = wclient->_init_(city_names.at(i), i);
            return;
        }
    }
}

void
CityNameListScreen::
draw_wifi_name(bool forceDraw){
    if(!forceDraw){
        return;
    }
    tft->setCursor(30,8);
    tft->setTextColor(TFT_LIGHTGREY, bg_c);
    tft->loadFont(NOTE_FONT16);
    tft->print(WiFi.SSID());
    tft->unloadFont();
}

void
CityNameListScreen::
draw(bool forceDraw)
{
    wifi->draw(forceDraw);
    draw_wifi_name(forceDraw);
    set_new_location->draw(forceDraw);
    
    if (number_of_saved_city_names < 1){
        tft->setCursor(10, 40);
        tft->setTextColor(TFT_DARKGREY, bg_c);
        tft->loadFont(LATIN);
        tft->print("No saved locations.");
        tft->unloadFont();
        return;
    }
    
    for (uint8_t i=0; i<number_of_saved_city_names; ++i){
        city_list[i]->draw(forceDraw);
    }   
}