#line 1 "c:\\Users\\pawel\\arduino\\ESP-Weather-Station\\src\\output\\items\\keypad\\Keyboard.cpp"
#include "Keyboard.h"

Keyboard::Keyboard(
    TFT_eSPI *tft
): last_pressed(0), current_keypad(0)
{

    String main_qwerty [28] = {
        "q", "w", "e", "r", "t", "y", "u", "i", "o", "p",
        "a", "s", "d", "f", "g", "h", "j", "k", "l", "<<",
        "z", "x", "c", "v", "b", "n", "m", "^"
    };

    String numbers [28] = {
        "1", "2", "3", "4", "5", "6", "7", "8", "9", "0",
        "!", "@", "#", "$", "%", "^", "&", "*", "(", "<<",
        ")", "[", "]", ";", ":", "+", "-", "."
    };

    String main_qwerty_C [28] = {
        "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P",     
        "A", "S", "D", "F", "G", "H", "J", "K", "L", "<<",     
        "Z", "X", "C", "V", "B", "N", "M", "^"
    };

    keypads = new Keypad* [NUMBER_OF_KEYBOARDS]{
        new Keypad(tft, main_qwerty, "1#"),
        new Keypad(tft, numbers, "Aa"),
        new Keypad(tft, main_qwerty_C, "1#")
    };

    for (uint8_t i = 0; i < NUMBER_OF_KEYBOARDS; i++)
    {
        keypads[i]->set_color(0x9800, DELETE_IDX - 1);
        keypads[i]->set_on_touch_color(0x4000, DELETE_IDX - 1);
        keypads[i]->set_text_color(TFT_WHITE, DELETE_IDX - 1);
        if (i != 1){
            keypads[i]->set_color(0x03CF, CAPS_LOCK - 1);
            keypads[i]->set_on_touch_color(0x0208, CAPS_LOCK - 1);
        }
    }
}

KeyInfo*
Keyboard::
check(Point* pos)
{
    KeyInfo *ret;
    int8_t idx = keypads[current_keypad]->check(pos);
    
    if (idx == -1){
        return 0;
    }

    ret = new KeyInfo {0,""}; // *res = 0, *(res+1) = 0 == IGNORE

    switch(idx)
    {
        case 0: // slider
            change_keypad();
            return ret; 
        case DELETE_IDX:
            ret->info = DELETE;
            break;
        case CAPS_LOCK: 
            if (current_keypad != NUMBERS){
                caps();
                return ret;
            }
        default:
            ret->info = NORMAL_BUTTON;
            ret->str = keypads[current_keypad]->get_button_str(idx-1);  
    }

    if (idx != last_pressed){
        re_draw();
        last_pressed = idx;
    }
    return ret;
}


void 
Keyboard::
change_keypad()
{
    if (current_keypad != NUMBERS){
        current_keypad = NUMBERS;
    }
    else{
        current_keypad = MAIN_QWERTY;
    }
    keypads[current_keypad]->draw(true);
}

void
Keyboard::
re_draw(){
    keypads[current_keypad]->re_draw(last_pressed);
}

void 
Keyboard::
caps(){
    current_keypad = current_keypad == MAIN_QWERTY ? MAIN_QWERTY_CAPS : MAIN_QWERTY; 
    keypads[current_keypad]->draw(true);
}  

void 
Keyboard::
draw(bool forceDraw){
    keypads[current_keypad]->draw(forceDraw);
}