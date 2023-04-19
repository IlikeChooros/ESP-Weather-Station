#include "PasswordInputScreen.h"

void 
PasswordInputScreen::
draw(String wifi_name)
{
    this->wifi_name = wifi_name;
    tft->setTextSize(1);
    tft->setTextColor(TFT_WHITE);
    tft->drawCentreString(wifi_name, 160, 0, 2);

    tft->fillRect(0,70, 320, 170, bg_c);

    keyboard->draw(true);
    enter_button->draw(true);
    exit_button->draw(true);
    inputfield->draw(true);
    inputfield->blink();
}

void
PasswordInputScreen::
draw(bool forceDraw){
    inputfield->blink();
}

void 
PasswordInputScreen::
check(Point* pos){
    change_ = false;
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
        enter_pwd();
        return;
    }
    change_ = exit_button->check(pos->x, pos->y);

    inputfield->blink();
}

void 
PasswordInputScreen::
enter_pwd()
{
    String password = inputfield->get_input();

    char* ssid = new char [wifi_name.length()+1];
    char* pass = new char [password.length()+1];

    password.toCharArray(pass, password.length()+1);
    wifi_name.toCharArray(ssid, wifi_name.length()+1);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);

    load_main_ = draw_connecting_to_wifi(wifi_name, ssid, pass);
}

String 
PasswordInputScreen::
get_str(){   
    counter++;
    if (counter%2 == 1){
        return wifi_name;
    }

    return inputfield->get_input();
}

bool PasswordInputScreen::load_main(){
    return this->load_main_;
}

bool 
PasswordInputScreen::
change(){
    return this->change_;
}

void 
PasswordInputScreen::
clear_buttons(){
    delete keyboard;
    delete enter_button;
    delete exit_button;
}