#include "SettingsScreen.h"

namespace settings
{
constexpr uint8_t scroll_height = 20;
constexpr uint8_t min_height = 30;
uint8_t max_items = 5;
int8_t scroll_idx = 0;
int8_t max_idx = 0;

void
scroll_down(){
    scroll_idx = scroll_idx < (max_idx - max_items) ? scroll_idx + 1 : max_idx - max_items;
}

void
scroll_up(){
    scroll_idx = scroll_idx > 0 ? scroll_idx - 1 : 0;
}

SettingsScreen::
SettingsScreen(
    TFT_eSPI* tft,
    uint16_t x, 
    uint16_t y, 
    uint16_t w, 
    uint16_t h
): tft(tft),
_scroll_down(0),
_scroll_up(0),
_scroll(false),
_load_main(false),
x(x), y(y), w(w), h(h),
_pick_idx(0) {}

SettingsScreen::
~SettingsScreen(){
    delete _scroll_down;
    delete _scroll_up;
}


SettingsScreen*
SettingsScreen::
prepare(const print_data& data){
    _print_data.push_back(data);
    return this;
}

SettingsScreen*
SettingsScreen::
prepare(const std::vector<print_data>& d){
    _print_data.clear();
    _print_data.assign(d.begin(), d.end());
    return this;
}

void
SettingsScreen::
init(){
    using uptrl = std::unique_ptr<ListItem>;

    max_idx = _print_data.size();
    scroll_idx = 0;
    uint8_t max_items = (h - 2*scroll_height) / min_height> 1 ? h / min_height : 1; // maximum number of display items (list options) on the screen
    uint8_t offset =  5; // (h - 2*scroll_height - min_height * max_items) / (1 + max_items); // distance between options

    // Make sure its well scaled
    if (max_idx > max_items){
        _itr_y = min_height;
        max_list_idx = max_items;

        _scroll_down = new CustomButton(tft, x, y, w, scroll_height, 0x10A3);
        _scroll_down
        ->touch_color(0x0861)
        ->set_draw_wh(drawScrollDownButton)
        ->set_on_press(scroll_down);

        _scroll_up = new CustomButton(tft, x, y + h - scroll_height, w, scroll_height, 0x10A3);
        _scroll_up
        ->touch_color(0x0861)
        ->set_draw_wh(drawScrollUpButton)
        ->set_on_press(scroll_up);
        _scroll = true;
    }
    // Else scale to make it bigger
    else{
        _itr_y = h/max_idx;
        _scroll = false;
        max_list_idx = max_idx;
    }

    for (auto data : _print_data){
        _list.push_back(uptrl(new ListItem(tft, x, y, w, _itr_y - offset)));
        _list.at(_list.size()-1)->set_data(
            data.string, data.same_line,
            data.font, data.size, data.color);
        y += _itr_y;
    }
}

bool
SettingsScreen::
picked(){
    return _load_main;
}

picked_list
SettingsScreen::
picked_data(){
    return picked_list(_list.at(_pick_idx)->stored().at(0), _pick_idx);
}


void
SettingsScreen::
clear(){
    _print_data.clear();
}

void
SettingsScreen::
check(Point* pos){
    _load_main = false;
    if (_scroll){
        max_list_idx = scroll_idx + max_items;
        if (_scroll_up->check(pos->x, pos->y) || _scroll_down->check(pos->x, pos->y)){
            max_list_idx = scroll_idx + max_items;

            Point pos(30,30);
            for (uint8_t i = scroll_idx; i < max_list_idx; ++i){
                _list.at(i)->set_position(pos);
                pos.y += _itr_y;
            }
            return;
        }
    }

    for (uint8_t i = scroll_idx; i < max_list_idx; ++i){
        if(!_list.at(i)->check(pos->x, pos->y)){
            continue;
        }
        if (_pick_idx != i){
            _list.at(_pick_idx)->draw(true);
        }
        _pick_idx = i;
        _load_main = true;
        break;
    }
}

void
SettingsScreen::
draw(bool forceDraw){
    if (!(forceDraw && _print_data.size() > 0)){
        return;
    }

    if (_scroll){
        _scroll_up->draw(forceDraw);
        _scroll_down->draw(forceDraw);
    }
    
    for (uint8_t i = scroll_idx; i < max_list_idx; ++i){
        _list.at(i)
        ->draw(forceDraw);
    }
}


}