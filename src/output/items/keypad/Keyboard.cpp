#include "Keyboard.h"

Keyboard::Keyboard(
    TFT_eSPI *tft
): last_pressed(0), current_keypad(0), tft(tft)
{

    String main_qwerty [26] = {
        "q", "w", "e", "r", "t", "y", "u", "i", "o", "p",
        "a", "s", "d", "f", "g", "h", "j", "k", "l", 
            "z", "x", "c", "v", "b", "n", "m", 
    };

    String numbers [26] = {
        "1", "2", "3", "4", "5", "6", "7", "8", "9", "0",
        "-", "@", "#", "%", "^", "$", "&", "*", "_", 
            "!", ".", ",", "?", ";", "'", "/",
    };

    String main_qwerty_C [26] = {
        "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P",     
        "A", "S", "D", "F", "G", "H", "J", "K", "L",      
            "Z", "X", "C", "V", "B", "N", "M",
    };

    keypads = new Keypad* [NUMBER_OF_KEYBOARDS]{
        new Keypad(tft, main_qwerty, "123"),
        new Keypad(tft, main_qwerty_C, "123"),
        new Keypad(tft, numbers, "ABC")
    };

    caps_button = new CustomButton(tft, 2, 207,
    2*KEYPAD_BUTTON_WIDTH + 5, 30, 0x31C6);
    caps_button
    ->set_draw_wh(drawCapsLockButton)
    ->touch_color(0x2104);

    delete_button = new CustomButton(tft, 320 - 2*KEYPAD_BUTTON_WIDTH-2,
    2*KEYPAD_BUTTON_HEIGHT + STARTING_Y + 24, 2*KEYPAD_BUTTON_WIDTH, KEYPAD_BUTTON_HEIGHT, 0x31C6);
    delete_button
    ->set_draw_wh(drawDeleteButton)
    ->touch_color(0x2104);

    space_button = new KeypadButton(tft, 70, 207, 180, 30, " ");
}

Keyboard::
~Keyboard(){
    for(uint8_t i=0; i<NUMBER_OF_KEYBOARDS; i++){
        keypads[i]->clear();
        delete keypads[i];
    }
    delete [] keypads;
    delete delete_button;
    delete caps_button;
    delete space_button;
}

KeyInfo*
Keyboard::
check(Point* pos)
{
    KeyInfo *ret = new KeyInfo {IGNORE, ""}; ;
    int8_t idx = keypads[current_keypad]->check(pos);

    if (space_button->check(pos->x, pos->y)){
        idx = NUMBER_OF_KEYPAD_BUTTONS + 1;
    }

    switch(idx)
    {
        case -1:
            break;
        case 0: // slider
            change_keypad();
            return ret; 
        default:
            ret->info = NORMAL_BUTTON;
            ret->str = idx != NUMBER_OF_KEYPAD_BUTTONS + 1 ? keypads[current_keypad]->get_button_str(idx-1) : space_button->get_str();  
            if (idx != last_pressed){
                re_draw();
                last_pressed = idx;
            }
            return ret;
    }

    if (delete_button->check(pos->x, pos->y)){
        ret->info = DELETE;
        re_draw();
    }
    else if(current_keypad != NUMBERS && caps_button->check(pos->x, pos->y)){
        caps();
    }
    return ret;    
}


void 
Keyboard::
change_keypad(){
    if (current_keypad != NUMBERS){
        current_keypad = NUMBERS;
        caps_button->set_draw_wh(drawClearWH);
        caps_button->draw(true);
    }
    else{
        current_keypad = MAIN_QWERTY;
        caps_button->set_draw_wh(drawCapsLockButton);
        caps_button->draw(true);
    }    
    keypads[current_keypad]->draw();
}

void
Keyboard::
re_draw(){
    if (last_pressed == NUMBER_OF_KEYPAD_BUTTONS + 1){
        tft->loadFont(LATIN);
        space_button->draw();
        tft->unloadFont();
        return;
    }
    caps_button->draw(true);      
    keypads[current_keypad]->re_draw(last_pressed);
    delete_button->draw(true);    
}

void 
Keyboard::
caps(){
    if (current_keypad){
        
    }
    current_keypad = current_keypad == MAIN_QWERTY ? MAIN_QWERTY_CAPS : MAIN_QWERTY; 
    keypads[current_keypad]->draw();
}  

void 
Keyboard::
draw(bool forceDraw){
    if (!forceDraw){
        return;
    }
    caps_button->draw(true);
    keypads[current_keypad]->draw();
    delete_button->draw(forceDraw);
    tft->loadFont(LATIN);
    space_button->draw();
    tft->unloadFont();
}