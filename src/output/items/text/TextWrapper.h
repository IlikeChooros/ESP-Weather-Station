#pragma once

#include "TFT_eSPI.h"

class TextWrapper
{
private:
    TFT_eSPI* tft;
    uint16_t max_width;
    uint16_t margin;

    uint16_t end_cursor;
    uint16_t start_cursor;
public:
    TextWrapper(TFT_eSPI* tft);
    ~TextWrapper() = default;

    TextWrapper*
    prepare(uint16_t max_width, uint16_t margin);

    /// @brief Wraps text to given width ex.: Hello World, -> Hello Wo...
    /// @param text Text to wrap
    /// @return Wrapped text
    String
    wrapBegin(String&& text);

    String
    wrapEnd(String&& text);
};

