#include "CityNameListScreen.h"


CityNameListScreen::
CityNameListScreen(
    TFT_eSPI* tft,
    uint16_t bg_c,
    WeatherClient* wc,
    TouchScreen* ts
): CityNameScreen(tft, bg_c, wc, ts)
{
    input_city = new CustomButton(tft, 0, 180, 320, 60, 0x10A3);
    input_city
    ->touch_color(0x0861)
    ->set_draw(drawSetLocationButton);
    wifi = new WiFiItem(tft, 5,5,20, bg_c);
}

void
CityNameListScreen::
init()
{
    EEPROM.begin(EEPROM_SIZE);

    number_of_saved_city_names = EEPROM.read(CITY_NAME_IDX);

    number_of_saved_city_names = number_of_saved_city_names < MAX_CITIES ? number_of_saved_city_names : MAX_CITIES;

    if (number_of_saved_city_names>0)
    {
        saved_city_names = new ListItem* [number_of_saved_city_names];
    }

    uint16_t address = CITY_NAME_IDX+2;
    for (uint8_t i=0; i<number_of_saved_city_names; i++)
    {
        String name = EEPROM.readString(address);
        city_names.push_back(name);
        saved_city_names[i] = new ListItem(tft, 20, 30+i*(LIST_HEIGHT+5), LIST_WIDTH, LIST_HEIGHT);
        address += 1 + CITY_NAME_LEN;
    }

    EEPROM.end();
}

void
CityNameListScreen::
set_city_info()
{
    EEPROM.begin(EEPROM_SIZE);

    uint16_t address = CITY_NAME_IDX + 1;
    for (uint8_t i=0; i<number_of_saved_city_names; i++)
    {
        City_info* info =
        wclient->get_city_info(
            city_names.at(i), 
            EEPROM.read(address)
        );

        if (!info)
        {
            saved_city_names[i]
            ->set_data(city_names.at(i), true, 2, 2, TFT_LIGHTGREY)
            ->set_data(String("NULL"), true, 2, 2, TFT_LIGHTGREY)
            ->set_data(String(0), true, 2, 2, TFT_LIGHTGREY)
            ->set_data(String(0), true, 2, 2, TFT_LIGHTGREY)
            ->set_data(String("NULL"), false, 2, 1, TFT_LIGHTGREY);
            EEPROM.end();
            break;
        }
        city_info.push_back(*info);
        Serial.println("---------------------------");
        Serial.println("NAME: "+info->name);
        Serial.println("COUNTRY: "+info->country);
        Serial.println("LAT: "+String(info->lat));
        Serial.println("LON: "+String(info->lon));
        Serial.println("STATE: "+info->state);

        if (info->state == "null")
        {
            info->state = "";
        }

        saved_city_names[i]
        ->set_data(info->name, true, 2, 2, TFT_LIGHTGREY)
        ->set_data(info->country, true, 2, 2, TFT_LIGHTGREY)
        ->set_data(info->state, false, 2, 2, TFT_LIGHTGREY);
        delete info;

        address += CITY_NAME_LEN + 1;
    }

    EEPROM.end();
}

void
CityNameListScreen::
check(Point* pos)
{
    change_ = input_city->check(pos->x, pos->y);
    for (uint8_t i=0; i<number_of_saved_city_names; ++i)
    {
        if(saved_city_names[i]->check(pos->x, pos->y))
        {
            load_main_ = wclient->_init_(city_names.at(i));
            return;
        }
    }
}

void
CityNameListScreen::
draw(bool forceDraw)
{
    wifi->draw(forceDraw);

    for (uint8_t i=0; i<number_of_saved_city_names; ++i)
    {
        saved_city_names[i]->draw(forceDraw);
    }

    if (number_of_saved_city_names<1)
    {
        tft->setCursor(10, 20);
        tft->setTextColor(TFT_DARKGREY);
        tft->setTextFont(2);
        tft->setTextSize(2);
        tft->print("No saved locations.");
    }
    input_city->draw(forceDraw);
}