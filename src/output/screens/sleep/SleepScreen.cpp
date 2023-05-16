#include "SleepScreen.h"

SleepScreen::
SleepScreen(
    TFT_eSPI* tft,
    uint16_t bg_c
): tft(tft), bg_c(bg_c),
floating_ram(new floating::FloatingRam(tft, bg_c)){
    reset();
    floating_ram->x(0)->y(0);
}

void SleepScreen::
draw(){
    // for(uint8_t i=0; i<rects.size(); i++){
    //     rects.at(i).draw();
    // }
    floating_ram->draw();
}

void SleepScreen::
reset(){
    //rects.clear();
}