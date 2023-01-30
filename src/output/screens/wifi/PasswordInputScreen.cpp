#include "PasswordInputScreen.h"

void 
PasswordInputScreen::
draw(
    String wifi_name
)
{
    this->wifi_name = wifi_name;
    tft->setTextSize(1);
    tft->setTextColor(TFT_WHITE);
    tft->drawCentreString(wifi_name, 160, 0, 2);

    tft->fillRect(0,70, 320, 170, bg_c);

    keyboard->draw();
    enter_button->draw();
    exit_button->draw();
    inputfield->draw();
}

// void 
// PasswordInputScreen::
// re_draw()
// {
//     keypads[current_keypad]->re_draw(last_pressed);
// }

void 
PasswordInputScreen::
check(
    Point* pos
)
{
    change_=false;
    // int8_t idx = keypads[current_keypad]->check(pos);
    
    // if (idx != -1)
    // {
    //     switch(idx)
    //     {
    //         case 0:
    //             change_keypad(LEFT_KEYBUTTON);
    //             draw(wifi_name);
    //             return;
    //         case NUMBER_OF_KEYPAD_BUTTONS+1:
    //             change_keypad(RIGHT_KEYBUTTON);
    //             draw(wifi_name);
    //             return;
    //         case 8: // DEL
    //             inputfield->del();
    //             break;
    //         case 16: // CAPSLOCK
    //             if (current_keypad == 0)
    //             {
    //                 inputfield->add_input(keypads[current_keypad]->get_button_str(idx-1));
    //                 break;
    //             }
    //             caps();
    //             return;
    //         default:
    //             inputfield->add_input(keypads[current_keypad]->get_button_str(idx-1));
    //             break;
    //     }

    //     if (idx != last_pressed)
    //     {
    //         re_draw();
    //         last_pressed = idx;
    //     }
    //     return;
    // }

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
        enter_pwd();
        return;
    }
    change_ = exit_button->check(pos->x, pos->y);
}

// void 
// PasswordInputScreen::
// change_keypad(int8_t dir)
// {
//     if (current_keypad == MAIN_QWERTY_CAPS)
//     {
//         current_keypad = 1;
//     }

//     else if (current_keypad == NUMBERS_CAPS)
//     {
//         current_keypad = 2;
//     }

//     switch (dir)
//     {
//         case LEFT_KEYBUTTON:  
//             current_keypad = current_keypad > 0? current_keypad - 1: 2;
//             break;
//         case RIGHT_KEYBUTTON:
//             current_keypad = current_keypad < 2 ? current_keypad + 1 : 0;
//             break;
//     }
//     keypads[current_keypad]->draw();
// }

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
get_str()
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

// void 
// PasswordInputScreen::
// caps()
// {
//     switch(current_keypad)
//     {
//         case MAIN_QWERTY_CAPS:
//             current_keypad = 1;
//             break;
//         case NUMBERS_CAPS:
//             current_keypad = 2;
//             break;
//         case 1:
//             current_keypad = MAIN_QWERTY_CAPS;
//             break;
//         default:
//             current_keypad = NUMBERS_CAPS;
//     }
//     keypads[current_keypad]->draw();
// }   

bool 
PasswordInputScreen::
change()
{
    return this->change_;
}

void 
PasswordInputScreen::
clear_buttons()
{
    keyboard->~Keyboard();

    delete keyboard;
    delete enter_button;
    delete exit_button;
}