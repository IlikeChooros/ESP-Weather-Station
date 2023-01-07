#include "MainScreen.h"

MainScreen::MainScreen(TFT_eSPI* tft, uint16_t bg_c)
{
    this->_tft = tft;
    this->bg_c = bg_c;
}