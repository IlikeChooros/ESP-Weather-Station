#include "CityNameInputScreen.h"

void
draw_rect(TFT_eSPI* tft)
{
    tft->fillRect(40, 40, 240, 160, TFT_BLACK);
    tft->drawRect(40, 40, 240, 160, TFT_WHITE);
    tft->setTextColor(TFT_DARKGREY);
    tft->setTextFont(2);
    tft->setTextSize(2);
    tft->setCursor(50,50);
}

void
CityNameInputScreen::
draw()
{
    keyboard->draw();
    inputfield->draw();
    enter_button->draw();
    return_button->draw();
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


    if (EEPROM.read(CITY_NAME_IDX-1) >= MAX_CITIES)
    {   
        override_location();
        return;
    }

    EEPROM.begin(EEPROM_SIZE);
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

    tft->setCursor(50,70);
    tft->print("override location?");

    uint8_t size =EEPROM.read(CITY_NAME_IDX-1);
    ListItem** temp = new ListItem* [size];
    KeypadButton* exit_button = new KeypadButton(tft, 45, 175, 40,20, "EXIT");
    exit_button->set_color(TFT_RED);

    KeypadButton* enter_button = new KeypadButton(tft, 235, 175, 40,20, "PICK");
    exit_button->set_color(TFT_DARKGREEN);

    EEPROM.begin(EEPROM_SIZE);
    for (uint8_t i=0; i<size; ++i)
    {
        temp[i] = new ListItem(tft, 50, 90 + i*(35), 150, 30);
        temp[i]->set_data(EEPROM.readString(i*CITY_NAME_LEN + CITY_NAME_IDX), true, 2, 1, TFT_WHITE);
        temp[i]->draw();
    }
    EEPROM.end();

    bool selected = false;
    int8_t idx_selected;

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
                break;
            }
        }

        if (exit_button->check(pos->x, pos->y))
        {
            draw_rect(tft);
            tft->print("Quiting...");
            delay(500);

            delete enter_button;
            delete exit_button;

            for(uint8_t i=0; i<size; ++i)
            {
                delete temp[i];
            }
            delete [] temp;

            delete pos;

            return;
        }

        if (selected && enter_button->check(pos->x, pos->y))
        {
            EEPROM.begin(EEPROM_SIZE);
            EEPROM.writeString(idx_selected*CITY_NAME_LEN + CITY_NAME_IDX, inputfield->get_input());
            EEPROM.commit();
            EEPROM.end();

            delete enter_button;
            delete exit_button;

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