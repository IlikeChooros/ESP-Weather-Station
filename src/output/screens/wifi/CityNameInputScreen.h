#pragma once

#include "CityNameScreen.h"
#include "../../items/keypad/Keyboard.h"
#include "../../items/keypad/CustomButton.h"
#include "../../items/InputField.h"

#include "../geoloc/GeoLocScreen.h"
#include "../settings/PickOptionScreen.h"

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

    void
    save_data();

public:
    CityNameInputScreen(
        TFT_eSPI* tft,
        uint16_t bg_c,
        WeatherClient* wc,
        TouchScreen* ts
    );

    void
    draw(bool forceDraw);

    void 
    check(Point* pos);
};
