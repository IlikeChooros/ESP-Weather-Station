#pragma once

#include <EEPROM.h>
#include <vector>
#include <memory>
#include "../../items/ListItem.h"
#include "../../items/keypad/CustomButton.h"
#include "../../items/scroll/ScrollItem.h"
#include "../../../data_structures/picked_list.h"

namespace settings
{

// Screen showing list of data, scrollable
class SettingsScreen
{
    TFT_eSPI *tft;
    uint16_t max_list_idx;

    std::vector<print_data> _print_data;
    std::vector<std::unique_ptr<ListItem>> _list;

    bool _scroll;
    CustomButton* _scroll_down;
    CustomButton* _scroll_up;
    ScrollItem* _scroll_item;

    uint16_t _itr_y;
    uint8_t _pick_idx;
    bool _picked;

    uint16_t x;
    uint16_t y; 
    uint16_t w; 
    uint16_t h;
    uint16_t _list_y;
public:
    SettingsScreen(
        TFT_eSPI* tft,
        uint16_t x, 
        uint16_t y, 
        uint16_t w, 
        uint16_t h
    );

    ~SettingsScreen();
    
    SettingsScreen*
    prepare(const print_data&);

    SettingsScreen*
    prepare(const std::vector<print_data>&);

    /// @brief Initializes ListItems based on given data, should be called after calling prepare(...)
    void
    init();

    void
    clear();

    void
    draw(bool forceDraw);

    void
    check(Point* pos);

    bool 
    picked();

    picked_list
    picked_data();
};

}
