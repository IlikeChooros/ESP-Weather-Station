#pragma once

#include "CityNameScreen.h"
#include "../../items/keypad/Keyboard.h"
#include "../../items/keypad/CustomButton.h"
#include "../../items/InputField.h"



class CityNameInputScreen: public CityNameScreen
{
    Keyboard* keyboard;
    InputField* inputfield;

    CustomButton* enter_button;
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

        enter_button = new CustomButton(tft, 275, 20, 35, 40,0x3CE6);
        enter_button
        ->set_draw(drawTickButton)
        ->touch_color(0x19E2);

        return_button = new KeypadButton(tft, 5, 5, 30, 30, "x");
        return_button->set_color(TFT_RED);
    }

    void
    draw();

    void 
    check(Point* pos);
};
