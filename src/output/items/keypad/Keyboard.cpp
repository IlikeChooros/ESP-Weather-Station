#include "Keyboard.h"

Keyboard::Keyboard(
    TFT_eSPI *tft
)
{
    this->last_pressed = 0;
    this->current_keypad = 1;

    String main_qwerty [24] = {
        "q", "w", "e", "r", "t", "y", "u", "<<",
        "a", "s", "d", "f", "g", "h", "j", "^",
        "z", "x", "c", "v", "b", "n", "m", "o"
    };

    String numbers [24] = {
        "i", "p", "k", "l", "0", "1", "2", "<<",
        "3", "4", "5", "6", "7", "8", "9", "^",
        "!", "?", "$", "%", "^", "&", "*", "@"
    };
    String main_qwerty_C [24] = {
        "Q", "W", "E", "R", "T", "Y", "U", "<<",     
        "A", "S", "D", "F", "G", "H", "J", "^",     
        "Z", "X", "C", "V", "B", "N", "M", "O"
    };
    String numbers_C [24] = {
        "I", "P", "K", "L", "0", "1", "2", "<<",   
        "3", "4", "5", "6", "7", "8", "9", "^",    
        "!", "?", "$", "%", "^", "&", "*", "@"
    };
    String special [24] = {
        "(", ")", "[",  "]", "{", "}", ";", "<<",   
        ":", "'", "\"", ",", ".", "<", ">", "\\",    
        "|", "+", "-",  "#", "",  "",  "",  ""
    };

    keypads = new Keypad* [NUMBER_OF_KEYBOARDS]{
        new Keypad(tft, special, "1234", "Aabc"), 
        new Keypad(tft, main_qwerty, "$#@!", "1234"),
        new Keypad(tft, numbers, "AaBc", "$#@!"),
        new Keypad(tft, numbers_C, "AaBc", "$#@!"),
        new Keypad(tft, main_qwerty_C, "$#@!", "1234")
    };

    for (uint8_t i=0; i<NUMBER_OF_KEYBOARDS; i++)
    {
        keypads[i]->set_color(0x9800, 7);
        keypads[i]->set_on_touch_color(0x4000, 7);
        keypads[i]->set_text_color(TFT_WHITE, 7);
        if (i>0)
        {
            keypads[i]->set_color(0x03CF ,15);
            keypads[i]->set_on_touch_color(0x0208 ,15);
        }
    }
}

KeyInfo*
Keyboard::
check(Point* pos)
{
    KeyInfo *res;
    int8_t idx = keypads[current_keypad]->check(pos);
    
    if (idx == -1)
    {
        return 0;
    }

    res = new KeyInfo {0,""}; // *res = 0, *(res+1) = 0 == IGNORE

    switch(idx)
    {
        case 0:
            change_keypad(LEFT_KEYBUTTON);
            return res; 
        case NUMBER_OF_KEYPAD_BUTTONS+1:
            change_keypad(RIGHT_KEYBUTTON);
            return res;
        case DELETE_IDX:
            res->info = DELETE;
            break;
        case CAPS_LOCK: 
            if (current_keypad != 0)
            {
                caps();
                return res;
            }
        default:
            res->info = NORMAL_BUTTON;
            res->str = keypads[current_keypad]->get_button_str(idx-1);  
    }

    if (idx != last_pressed)
    {
        re_draw();
        last_pressed = idx;
    }
    return res;
}


void 
Keyboard::
change_keypad(uint8_t dir)
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

void
Keyboard::
re_draw()
{
    keypads[current_keypad]->re_draw(last_pressed);
}

void 
Keyboard::
caps()
{
    switch(current_keypad)
    {
        case MAIN_QWERTY_CAPS:
            current_keypad = 1;
            break;
        case NUMBERS_CAPS:
            current_keypad = 2;
            break;
        case 1:
            current_keypad = MAIN_QWERTY_CAPS;
            break;
        default:
            current_keypad = NUMBERS_CAPS;
    }
    keypads[current_keypad]->draw();
}  

void 
Keyboard::
draw()
{
    keypads[current_keypad]->draw();
}