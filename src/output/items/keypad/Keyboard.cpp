#include "Keyboard.h"

Keyboard::Keyboard(
    TFT_eSPI *tft
): last_pressed(0), current_keypad(0), tft(tft){

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

    buttons = new TouchButton* [3]{
        caps_button, delete_button, space_button
    };
}

Keyboard::
~Keyboard(){
    for(uint8_t i=0; i<NUMBER_OF_KEYBOARDS; i++){
        keypads[i]->clear();
        delete keypads[i];
    }
    delete [] keypads;
    delete [] buttons;
    delete delete_button;
    delete caps_button;
    delete space_button;
}

KeyInfo*
Keyboard::
check(Point* pos)
{
    KeyInfo *ret = new KeyInfo {IGNORE, ""};
    int8_t idx = keypads[current_keypad]->check(pos);

    if (space_button->check(pos->x, pos->y)){
        idx = SPACE;
    }

    switch(idx)
    {
        case -1:
            break;
        case 0: // slider
            change_keypad();
            if (last_pressed > NUMBER_OF_KEYPAD_BUTTONS){
                buttons[last_pressed - NUMBER_OF_KEYPAD_BUTTONS - 1]->draw(true);
            }
            return ret; 
        default:
            ret->info = NORMAL_BUTTON;
            ret->str = idx != SPACE ? keypads[current_keypad]->get_button_str(idx-1) : space_button->get_str();  
            if (idx != last_pressed){
                re_draw();
                last_pressed = idx;
            }
            return ret;
    }

    if (delete_button->check(pos->x, pos->y)){
        ret->info = DELETE;
        if (last_pressed != DELETE_IDX){
            re_draw();
        }        
        last_pressed = DELETE_IDX;
    }
    else if(current_keypad != NUMBERS && caps_button->check(pos->x, pos->y)){
        caps();
        if (last_pressed == DELETE_IDX || last_pressed == 0){
            re_draw();
        }
        last_pressed = CAPS_LOCK;
    }
    return ret;    
}


void 
Keyboard::
change_keypad(){
    auto draw = drawCapsLockButton;
    switch(current_keypad){
        case NUMBERS:
            current_keypad = MAIN_QWERTY;
            break;
        default:
            draw = drawClearWH;
            current_keypad = NUMBERS;
    }
    caps_button->set_draw_wh(draw);
    caps_button->draw(true); 
    keypads[current_keypad]->draw();
}

void
Keyboard::
re_draw(){
    switch(last_pressed){
        case SPACE:
            tft->loadFont(LATIN);
            space_button->draw(true);
            tft->unloadFont();
            return;
        case DELETE_IDX:
            delete_button->draw(true);
            return;
        case CAPS_LOCK:
            caps_button->draw(true);
            return;
        default:
            keypads[current_keypad]->re_draw(last_pressed);
            return;
    }
}

void 
Keyboard::
caps(){
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
    delete_button->draw(true);
    tft->loadFont(LATIN);
    space_button->draw(true);
    tft->unloadFont();
}