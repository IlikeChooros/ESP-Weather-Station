#include "WindowItem.h"

namespace window{

WindowItem::
WindowItem(
    TFT_eSPI* tft,
    uint16_t x,
    uint16_t y,
    uint16_t w,
    uint16_t h,
    uint16_t foreground_color,
    uint16_t frame_color
): tft(tft), frame_color(frame_color),
foreground_color(foreground_color),
x(x), y(y), w(w), h(h), content(0),
quit(false) {
    exit_button = new CustomButton(tft, x + w - 35, y + 3, 30, 30, 0x8040);
    exit_button
    ->set_draw(drawExitButton)
    ->touch_color(0x30C2);
}

WindowItem::
~WindowItem(){
    delete exit_button;
    delete content;
}

WindowItem*
WindowItem::
prepare(print_data data){
    to_print.push_back(data);
    return this;
}

WindowItem*
WindowItem::
prepare(std::vector<print_data>& data){
    to_print.clear();
    to_print.assign(data.begin(), data.end());
    return this;
}

void
WindowItem::
init(){
    if (content){
        delete content;
    }
    content = new ListItem(tft, x+1, y + 35, w-2, h - 36);
    quit = false;
    for (auto i : to_print){
        content->set_data(
            i.string, i.same_line, i.font, i.color
        );
    }
    content->wrap_text(false);
}

void
WindowItem::
draw(bool forceDraw){
    draw_window(forceDraw);
    exit_button->draw(forceDraw);
    content->draw(forceDraw);
}

void
WindowItem::
draw_window(bool force){
    if (!force){
        return;
    }
    tft->fillRect(x, y, w, h, foreground_color);
    tft->drawRect(x, y, w, h, frame_color);
}

void
WindowItem::
check(Point* pos){
    quit = exit_button->check(pos->x, pos->y);
    content->check(pos->x, pos->y);
}

void
WindowItem::
clear(){
    delete content;
    content = 0;
}

bool
WindowItem::
exited(){
    return quit;
}

}
