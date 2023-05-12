#pragma once

#include "TFT_eSPI.h"
#include <vector>

#include "../../input/TouchButton.h"
#include "../icons/drawings.h"
#include "../../data_structures/Point.h"
#include "../../data_structures/print_data.h"
#include "text/TextWrapper.h"

class
ListItem: public TouchButton{

private:
    TFT_eSPI* tft;
    TFT_eSprite* img;
    bool wrap;
    std::vector<print_data> data;
    std::vector<print_data> to_print;
    uint16_t prev_cursor;    

    void 
    draw_(uint16_t color);
    
public:
    ListItem(
        TFT_eSPI* tft,
        int16_t x,
        int16_t y,
        int16_t width,
        int16_t height
    );

    ~ListItem();

    void 
    draw(bool forceDraw);

    void
    on_touch();

    /// @brief Set text wrapping
    /// @param  bool true - text will be wrapped (by default)
    /// @return this pointer
    ListItem*
    wrap_text(bool);

    /// @brief Creates a sprite, rendering will be faster at the cost of memory (total memory used: 2 x width x height B)
    /// @warning Use this function after setting data
    /// @return this pointer
    ListItem*
    createSprite();

    /// @brief Puts data in ListItem
    /// @param str String to display
    /// @param same_line wheter it should be in the same line (false - creates break line before this string)
    /// @param font text font
    /// @param text_color 
    /// @return this pointer
    ListItem*
    set_data(
        String str,
        bool same_line,
        String font,
        uint16_t text_color
    );

    /// @brief Set new position of the listItem
    /// @param pos position
    /// @return this pointer
    ListItem*
    set_position(Point& pos);

    /// @brief Get stored data
    std::vector<print_data>&
    stored();
};