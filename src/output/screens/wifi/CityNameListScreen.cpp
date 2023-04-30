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

CityNameListScreen::
~CityNameListScreen(){
    delete set_new_location;
    delete wifi;

    if (!number_of_saved_city_names){
        return;
    }
    for (uint8_t i=0; i < number_of_saved_city_names; ++i){
        delete city_list[i];
    }
    delete [] city_list;
}

void
CityNameListScreen::
init()
{
    city_info = read_mem.cities(true);
    number_of_saved_city_names = city_info.size();
    number_of_saved_city_names = number_of_saved_city_names < MAX_CITIES ? number_of_saved_city_names : MAX_CITIES;
    if (!city_info.empty()){
        city_list = new ListItem* [number_of_saved_city_names];
    }
    uint8_t count = 0;
    for (auto i : city_info){
        city_list[count] = new ListItem(tft, 20, 30+count*(LIST_HEIGHT+5), LIST_WIDTH, LIST_HEIGHT);
        count++;
    }
}

void
CityNameListScreen::
set_city_info()
{
    uint8_t count = 0;
    for (auto i : city_info){
        City_info* info = wclient->get_city_info(
            i.first, i.second
        );

        if (!info){
            city_list[count]
            ->set_data("No data", true, LATIN, TFT_LIGHTGREY);
            count++;
            continue;
        }

        city_list[count]
        ->set_data(info->name, true, EXTENDED_LATIN, TFT_LIGHTGREY)
        ->set_data(info->country, true, LATIN, TFT_LIGHTGREY)
        ->set_data(info->state, false, LATIN, TFT_LIGHTGREY);

        count++;
    }
}

void
CityNameListScreen::
check(Point* pos)
{
    change_ = set_new_location->check(pos->x, pos->y);
    for (uint8_t i=0; i<number_of_saved_city_names; ++i){
        if(city_list[i]->check(pos->x, pos->y)){
            std::pair<String, uint8_t> found;
            uint8_t j = 0;
            for (auto a : city_info){
                if (j != i){
                    j++;
                    continue;
                }
                found = a;
                break;
            }
            load_main_ = wclient->_init_(found.first, found.second);
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
    
    if (city_info.empty()){
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