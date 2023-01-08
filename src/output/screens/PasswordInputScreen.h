#ifndef PASSWORD_INPUT_SCREEN_H
#define PASSWORD_INPUT_SCREEN_H

#include <WiFi.h>
#include "WiFiScreen.h"

class PasswordInputScreen: public WiFiScreen
{
    public:
    PasswordInputScreen(TFT_eSPI* tft, uint16_t bg_c): WiFiScreen(tft, bg_c){}
};

#endif