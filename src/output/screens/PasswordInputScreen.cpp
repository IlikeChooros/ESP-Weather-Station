#include "PasswordInputScreen.h"

void PasswordInputScreen::draw(String wifi_name)
{
    this->wifi_name = wifi_name;
    tft->setTextSize(1);
    tft->setTextColor(TFT_WHITE);
    tft->drawCentreString(wifi_name, 160, 0, 2);

    tft->fillRect(0,70, 320, 170, bg_c);
    keypads[current_keypad]->draw();
    enter_button->draw();
    exit_button->draw();
    inputfield->draw();
}

void PasswordInputScreen::re_draw()
{
    keypads[current_keypad]->re_draw(last_pressed);
}

void PasswordInputScreen::check(int16_t* pos)
{
    change_=false;
    int8_t idx = keypads[current_keypad]->check(pos);
    
    if (idx != -1)
    {
        switch(idx)
        {
            case 0:
                change_keypad(LEFT_KEYBUTTON);
                draw(wifi_name);
                return;
            case NUMBER_OF_KEYPAD_BUTTONS+1:
                change_keypad(RIGHT_KEYBUTTON);
                draw(wifi_name);
                return;
            case 8: // DEL
                inputfield->del();
                break;
            case 16: // CAPSLOCK
                if (current_keypad == 0)
                {
                    inputfield->add_input(keypads[current_keypad]->get_button_str(idx-1));
                    break;
                }
                caps();
                return;
            default:
                inputfield->add_input(keypads[current_keypad]->get_button_str(idx-1));
                break;
        }
        re_draw();
        last_pressed = idx;
        return;
    }


    if(enter_button->check(pos[0], pos[1]))
    {
        enter_pwd();
        return;
    }
    if (exit_button->check(pos[0], pos[1]))
    {
        this->change_ = true;
    }
}

void PasswordInputScreen::change_keypad(int8_t dir)
{
    if (current_keypad == MAIN_QWERTY_CAPS)
    {
        current_keypad = 1;
    }

    else if (current_keypad == NUMBERS_CAPS)
    {
        current_keypad = 2;
    }

    switch (dir)
    {
        case LEFT_KEYBUTTON:  
            current_keypad = current_keypad > 0? current_keypad - 1: 2;
            break;
        case RIGHT_KEYBUTTON:
            current_keypad = current_keypad < 2 ? current_keypad + 1 : 0;
            break;
    }
    keypads[current_keypad]->draw();
}

void PasswordInputScreen::enter_pwd()
{
    String password = inputfield->get_input();

    char* ssid = new char [wifi_name.length()+1];
    char* pass = new char [password.length()+1];

    password.toCharArray(pass, password.length()+1);
    wifi_name.toCharArray(ssid, wifi_name.length()+1);

    Serial.println("ssid: "+String(ssid)+ "  pass: "+String(pass)+ "  len: "+String(wifi_name.length())+"  "+String(password.length()));
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);

    tft->fillRect(55, 70, 210, 100, TFT_DARKGREY);
    tft->drawRect(55, 70, 210, 100, TFT_WHITE);

    tft->setTextSize(1);
    tft->setTextFont(2);
    tft->setTextColor(TFT_GREEN);
    tft->setCursor(90, 75);
    tft->print("Connecting to:");

    tft->drawCentreString(ssid, 160, 95, 2);
    tft->setCursor(120, 120);

    tft->setTextSize(3);
    tft->setTextColor(TFT_DARKGREEN);
    uint8_t number_of_tries = 0;

    uint32_t timer = millis();
    while(WiFi.status() != WL_CONNECTED)
    {
        if (millis() - timer > 1000)
        {
            tft->print(".");
            number_of_tries++;

            if (number_of_tries == 9){
                tft->setTextSize(1);
                tft->setTextColor(TFT_RED);
                tft->drawCentreString("Failed.", 160, 115, 2);
                delay(1000);
                delete [] ssid;
                delete [] pass;

                tft->fillScreen(bg_c);
                draw(wifi_name);
                return;
            }
            timer = millis();
        }
        
    }

    delete [] ssid;
    delete [] pass;

    load_main_ = true;
}

String PasswordInputScreen::get_str()
{   
    counter++;
    if (counter%2 == 1)
    {
        return wifi_name;
    }

    return inputfield->get_input();
}

bool PasswordInputScreen::load_main()
{
    return this->load_main_;
}

void PasswordInputScreen::caps()
{
    if (current_keypad == MAIN_QWERTY_CAPS)
    {
        current_keypad = 1;
        keypads[current_keypad]->draw();
        return;
    }
    if (current_keypad == NUMBERS_CAPS)
    {
        current_keypad = 2;
        keypads[current_keypad]->draw();
        return;
    }

    if (current_keypad == 1)
    {
        current_keypad = MAIN_QWERTY_CAPS;
    }
    else{
        current_keypad = NUMBERS_CAPS;
    }
    keypads[current_keypad]->draw();
}   

bool PasswordInputScreen::change()
{
    return this->change_;
}

void PasswordInputScreen::clear_buttons()
{
    for (int8_t i=0; i<NUMBER_OF_KEYBOARDS; i++)
    {
        keypads[i]->clear();
        delete keypads[i];
    }
    delete [] keypads;

    delete enter_button;
    delete exit_button;
}