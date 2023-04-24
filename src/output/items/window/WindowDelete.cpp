#include "WindowDelete.h"

namespace window{

WindowDelete::
WindowDelete(
    TFT_eSPI* tft,
    uint16_t x,
    uint16_t y,
    uint16_t w,
    uint16_t h,
    uint16_t fr_c,
    uint16_t frame_c
): WindowItem(tft, x, y, w, h, fr_c, frame_c), del(false){
    erase_button  = new CustomButton(tft, x + 5, y + 3, 30, 30, 0x4228);
    erase_button
    ->set_draw(drawEraseButton)
    ->touch_color(0x30C2);
}

WindowDelete::
~WindowDelete(){
    delete erase_button;
}

void
WindowDelete::
draw(bool forceDraw){
    draw_window(forceDraw);
    exit_button->draw(forceDraw);
    erase_button->draw(forceDraw);
    content->draw(forceDraw);
}

void
WindowDelete::
check(Point* pos){
    del = erase_button->check(pos->x, pos->y);
    quit = exit_button->check(pos->x, pos->y) || del;
    content->check(pos->x, pos->y);
}

bool
WindowDelete::
deleted(){
    return del;
}

bool
WindowDelete::
exited(){
    return quit;
}

}