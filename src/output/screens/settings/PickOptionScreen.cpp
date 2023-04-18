#include "PickOptionScreen.h"

namespace settings{

bool selected = false;
bool exit_screen = false;

void
exit(){
    exit_screen = true;
    selected = false;
}

void
confirm(){
    exit_screen = true;
}

PickOptionScreen::
PickOptionScreen(
    TFT_eSPI* tft,
    TouchScreen* ts
): tft(tft), ts(ts), _title(""){
    _confirm = new CustomButton(tft, 285, 5, 30, 30, 0x33E6);
    _exit = new CustomButton(tft, 285, 50, 30, 30, 0x8040);
    _sc = new SettingsScreen(tft, 20, 30, 240, 200);

    _confirm
    ->set_draw(drawTickButton)
    ->touch_color(0x2204)
    ->set_on_press(settings::confirm);

    _exit
    ->set_draw(drawExitButton)
    ->touch_color(0x30C2)
    ->set_on_press(settings::exit);
}

PickOptionScreen::
~PickOptionScreen(){
    delete _exit;
    delete _confirm;
    delete _sc;
}

PickOptionScreen*
PickOptionScreen::
prepare(const print_data& data){
    _sc->prepare(data);
    return this;
}

PickOptionScreen*
PickOptionScreen::
prepare(const std::vector<print_data>& data){
    _sc->prepare(data);
    return this;
}

void
PickOptionScreen::
init(){
    selected = false;
    exit_screen = false;
    _sc->init();
}

void
PickOptionScreen::
draw_title(bool forceDraw){
    if (!forceDraw){
        return;
    }
    tft->setTextColor(TFT_LIGHTGREY);
    tft->setTextSize(1);
    tft->drawCentreString(_title, 140, 5, 2);
}

void
PickOptionScreen::
draw(bool forceDraw){
    _exit->draw(forceDraw);
    _confirm->draw(forceDraw);
    _sc->draw(forceDraw);
    draw_title(forceDraw);
}

void
PickOptionScreen::
check(){
    Point* pos = ts->read_touch();

    if (!pos){
        return;
    }

    _sc->check(pos);
    selected = _sc->picked();
    if (selected){
        _confirm->check(pos->x, pos->y);
    }
    _exit->check(pos->x, pos->y);

    delete pos;
}

PickOptionScreen*
PickOptionScreen::
set_title(const String& t){
    _title = t;
    return this;
}

bool
PickOptionScreen::
load_main(){
    return exit_screen;
}

bool
PickOptionScreen::
picked(){
    return selected;
}

picked_list
PickOptionScreen::
get_picked(){
    return _sc->picked_data();
}

}



