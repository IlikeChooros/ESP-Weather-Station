#include "WiFiScreen.h"

WiFiScreen::WiFiScreen(TFT_eSPI* tft, int16_t bg_c)
{
    this->tft = tft;
    this->bg_c = bg_c;
}