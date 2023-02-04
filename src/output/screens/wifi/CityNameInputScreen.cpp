#include "CityNameInputScreen.h"

void
draw_rect(TFT_eSPI* tft)
{
    tft->fillRect(30, 30, 260, 180, TFT_BLACK);
    tft->drawRect(30, 30, 260, 180, TFT_WHITE);
    tft->setTextColor(TFT_LIGHTGREY);
    tft->setTextFont(2);
    tft->setTextSize(2);
    tft->setCursor(40,32);
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
enter()
{
    load_main_ = draw_get(inputfield->get_input());

    if (!load_main_)
    {
        return;
    }

    EEPROM.begin(EEPROM_SIZE);
    if (EEPROM.read(CITY_NAME_IDX-1) >= MAX_CITIES)
    {   
        override_location();
        return;
    }

    uint8_t num = EEPROM.read(CITY_NAME_IDX-1);
    EEPROM.writeString(num*CITY_NAME_LEN + CITY_NAME_IDX, inputfield->get_input());
    EEPROM.write(CITY_NAME_IDX-1, num+1);
    EEPROM.commit();
    EEPROM.end();   
}

void
CityNameInputScreen::
override_location()
{
    draw_rect(tft);
    tft->print("Do you want to");

    tft->setCursor(40,55);
    tft->print("override location?");

    uint8_t size =EEPROM.read(CITY_NAME_IDX-1);

    size = size < MAX_CITIES ? size : MAX_CITIES;

    ListItem** temp = new ListItem* [size];
    KeypadButton* exit = new KeypadButton(tft, 35, 175, 30,30, "X");
    exit->set_color(TFT_RED);

    CustomButton* enter = new CustomButton(tft, 235, 175, 30,30, 0x19E2);
    enter->set_draw(drawTickButton);

    uint8_t max_len=0;
    for (uint8_t i=0; i<size; ++i)
    {
        String str = EEPROM.readString(i*CITY_NAME_LEN + CITY_NAME_IDX);
        max_len = str.length() > max_len ? str.length() : max_len;
    }

    for (uint8_t i=0; i<size; ++i)
    {
        temp[i] = new ListItem(tft, 50, 90 + i*(35), max_len*12, 30);
        temp[i]->set_data(EEPROM.readString(i*CITY_NAME_LEN + CITY_NAME_IDX), true, 2, 1, TFT_WHITE);
        temp[i]->draw(true);
    }
    EEPROM.end();


    exit->draw(true);
    enter->draw(true);

    bool selected = false;
    int8_t idx_selected=-1;

    while(1)
    {
        Point* pos = ts->read_touch();

        if(!pos)
        {
            continue;
        }

        for (uint8_t i=0; i<size; i++)
        {
            if (temp[i]->check(pos->x, pos->y))
            {
                selected = true;
                idx_selected = i;
                enter->set_color(0x3CE6);
                enter->draw(true);
                break;
            }
        }

        if (exit->check(pos->x, pos->y))
        {
            draw_rect(tft);
            tft->print("Quiting...");
            delay(500);

            delete enter;
            delete exit;

            for(uint8_t i=0; i<size; ++i)
            {
                delete temp[i];
            }
            delete [] temp;

            delete pos;

            return;
        }

        if (selected && enter->check(pos->x, pos->y))
        {
            EEPROM.begin(EEPROM_SIZE);
            EEPROM.writeString(idx_selected*CITY_NAME_LEN + CITY_NAME_IDX, inputfield->get_input());
            EEPROM.commit();
            EEPROM.end();

            delete enter;
            delete exit;

            for(uint8_t i=0; i<size; ++i)
            {
                delete temp[i];
            }
            delete [] temp;

            delete pos;

            draw_rect(tft);
            tft->print("Overridding...");
            delay(500);
            return;
        }

        delete pos;
    }
}