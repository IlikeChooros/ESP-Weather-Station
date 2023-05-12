#include "CityNameListScreen.h"

CityNameListScreen::
CityNameListScreen(
    TFT_eSPI* tft,
    uint16_t bg_c,
    WeatherClient* wc,
    TouchScreen* ts
): CityNameScreen(tft, bg_c, wc, ts),
choose_location(tft), wifi_name(tft){
    set_new_location = new CustomButton(tft, 0, 180, 320, 60, 0x10A3);
    set_new_location
    ->touch_color(0x0861)
    ->set_draw(drawSetLocationButton);
    wifi = new WiFiItem(tft, 5,5,15, bg_c);
}

CityNameListScreen::
~CityNameListScreen(){
    delete set_new_location;
    delete wifi;
    choose_location.deleteSprite();
    wifi_name.deleteSprite();

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
        ->set_data(info->state, false, EXTENDED_LATIN_SMALL, TFT_LIGHTGREY);

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

    if(!wifi_name.created()){
        wifi_name.loadFont(NOTE_FONT12);
        std::unique_ptr<TextWrapper> tw(new TextWrapper(tft));
        String wrap = tw->prepare(85, 0)->wrapBegin(WiFi.SSID());
        wrap += wrap != WiFi.SSID() ? "..." : "";
        wifi_name.createSprite(wifi_name.textWidth(wrap), wifi_name.fontHeight());
        wifi_name.setTextColor(TFT_LIGHTGREY, bg_c);     
        wifi_name.fillSprite(bg_c);   
        wifi_name.drawString(wrap, 0, 0);
        wifi_name.unloadFont();

        choose_location.loadFont(NOTE_FONT16);
        uint16_t len = choose_location.textWidth("Choose location");
        choose_location.createSprite(len, choose_location.fontHeight());
        choose_location.setTextColor(TFT_LIGHTGREY, bg_c);
        choose_location.fillSprite(bg_c);
        choose_location.drawString("Choose location", 0, 0);
        choose_location.unloadFont();
        choose_location_x = 160 - len/2 - 2;
    }
    choose_location.pushSprite(choose_location_x, 7);
    wifi_name.pushSprite(27, 9);
}

void
CityNameListScreen::
draw(bool forceDraw){
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