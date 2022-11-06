#include "TextItem.h"

TextItem::TextItem(TFT_eSPI *tft, uint16_t x, uint16_t y, uint8_t font, uint8_t text_size, String text, uint16_t background_color)
{
    this->x = x;
    this->y = y;
    this->_tft = tft;
    this->bg_c = background_color;
    this->font = font;
    this->text = text;
    this->text_size = text_size;
}
