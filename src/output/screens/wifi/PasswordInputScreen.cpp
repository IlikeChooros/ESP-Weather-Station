#include "PasswordInputScreen.h"

PasswordInputScreen::
PasswordInputScreen(
    TFT_eSPI* tft, 
    uint16_t bg_c
): WiFiScreen(tft, bg_c), counter(0), change_(false),
load_main_(false), wifi_name("") 
{
    enter_button = new CustomButton(tft, 275, 20, 35, 40,0x3CE6);
    enter_button
    ->set_draw(drawTickButton)
    ->touch_color(0x19E2);

    exit_button = new CustomButton(tft, 5, 5, 30, 30, 0x8040);
    exit_button
    ->set_draw(drawExitButton)
    ->touch_color(0x30C2);

    inputfield = new InputField(tft, 40, 20, 230, 40);
    keyboard = new Keyboard(tft);
}

PasswordInputScreen::
~PasswordInputScreen(){
    clear_buttons();
}

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
    KeyInfo* info = keyboard->check(pos);

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
    delete info;

    if(enter_button->check(pos->x, pos->y)){
        enter_pwd();
        return;
    }
    change_ = exit_button->check(pos->x, pos->y);
}

void 
PasswordInputScreen::
enter_pwd(){
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
    delete inputfield;
}