#pragma once

#include "CityNameScreen.h"
#include "../../items/keypad/Keyboard.h"
#include "../../items/InputField.h"


class CityNameInputScreen: public CityNameScreen
{
    Keyboard* keyboard;
    InputField* inputfield;

    KeypadButton* enter_button;
    KeypadButton* return_button;

    void
    enter();

    void
    override_location();

public:
    CityNameInputScreen(
        TFT_eSPI* tft,
        uint16_t bg_c,
        WeatherClient* wc,
        TouchScreen* ts
    ): CityNameScreen(tft, bg_c, wc, ts)
    {
        keyboard = new Keyboard(tft);
        inputfield = new InputField(tft, 40, 20, 230, 40);
        enter_button = new KeypadButton(tft, 275, 20, 35, 40, "+");
        return_button = new KeypadButton(tft, 0,0, 25, 25, "X");
        enter_button->set_color(0x3CE6);
        enter_button->set_on_touch_color(0x19E2);

        return_button->set_color(TFT_RED);
    }

    void
    draw();

    void 
    check(Point* pos);
};
