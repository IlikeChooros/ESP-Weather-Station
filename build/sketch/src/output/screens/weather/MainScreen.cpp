#line 1 "c:\\Users\\pawel\\arduino\\ESP-Weather-Station\\src\\output\\screens\\weather\\MainScreen.cpp"
#include "MainScreen.h"

MainScreen::MainScreen(TFT_eSPI* tft, uint16_t bg_c)
{
    this->_tft = tft;
    this->bg_c = bg_c;
}