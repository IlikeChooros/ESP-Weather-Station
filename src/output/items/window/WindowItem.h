#pragma once

#include <vector>

#include "../keypad/CustomButton.h"
#include "../ListItem.h"
#include "../../../data_structures/Point.h"

namespace window{

class WindowItem
{
private:
    TFT_eSPI *tft;
    CustomButton* exit_button;
    ListItem* content;

    std::vector<print_data> to_print;
    uint16_t x;
    uint16_t y;
    uint16_t w;
    uint16_t h;
    uint16_t foreground_color;
    uint16_t frame_color;

    void
    draw_window(bool forceDraw);
public:
    WindowItem(
        TFT_eSPI* tft,
        uint16_t x,
        uint16_t y,
        uint16_t w,
        uint16_t h,
        uint16_t fr_c,
        uint16_t frame_c
    );
    ~WindowItem();

    WindowItem*
    prepare(print_data);

    WindowItem*
    prepare(std::vector<print_data>&);

    void
    init();

    void
    draw(bool);

    void
    check(Point*);

    void
    clear();

    bool
    exited();
};


}



