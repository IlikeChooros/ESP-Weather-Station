#include "ScrollItem.h"

ScrollItem::
ScrollItem(
    TFT_eSPI* tft,
    uint16_t x,
    uint16_t y,
    uint16_t w,
    uint16_t h,
    uint8_t max_range
): tft(tft), x(x), y(y), w(w), h(h),
max_range(max_range), prev_idx(255),
segmenent_height(h / max_range) {}

void
ScrollItem::
draw(uint8_t idx){
    if (prev_idx == idx && idx >= max_range){
        return;
    }

    tft->fillRect(x, y, w, h, 0x2965);
    tft->drawRect(x, y, w, h, 0x39C7);
    tft->fillRect(x + 1, y + idx * segmenent_height + 1, w - 2, segmenent_height-2, 0x52AA);
}