#pragma once

#include "WindowItem.h"
namespace window{

class WindowDelete : public WindowItem
{
private:
    CustomButton* erase_button;
    bool del;
public:
    WindowDelete(
        TFT_eSPI* tft,
        uint16_t x,
        uint16_t y,
        uint16_t w,
        uint16_t h,
        uint16_t fr_c,
        uint16_t frame_c
    );
    ~WindowDelete();

    virtual void
    draw(bool);

    virtual void
    check(Point* pos);

    bool
    deleted();

    virtual bool
    exited();
};

}

