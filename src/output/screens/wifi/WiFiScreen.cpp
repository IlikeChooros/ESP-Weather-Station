#include "WiFiScreen.h"

WiFiScreen::WiFiScreen(TFT_eSPI* tft, uint16_t bg_c)
{
    this->tft = tft;
    this->bg_c = bg_c;
}

//*****************************
// Returns true if successfully
// connects to WiFi
//*****************************
bool WiFiScreen::draw_connecting_to_wifi(String wifi_name, char* ssid, char* pass)
{
    tft->fillRect(55, 70, 210, 100, TFT_DARKGREY);
    tft->drawRect(55, 70, 210, 100, TFT_WHITE);

    std::unique_ptr<char[]> ptr_ssid(ssid);
    std::unique_ptr<char[]> ptr_pass(pass);

    tft->loadFont(NOTE_FONT16);
    tft->setTextColor(TFT_GREEN, TFT_DARKGREY);
    tft->setCursor(90, 75);
    tft->print("Connecting to:");

    tft->drawCentreString(ssid, 160, 95, 2);

    tft->setCursor(100, 120);
    
    uint8_t number_of_tries = 0;

    uint32_t timer = millis();

    while(WiFi.status() != WL_CONNECTED)
    {
        if (millis() - timer > 1000)
        {
            tft->print(".");
            number_of_tries++;

            if (number_of_tries == 10){
                tft->drawCentreString("Failed.", 160, 115, 2);
                delay(1000);

                tft->fillScreen(bg_c);
                draw(wifi_name);
                draw(true);
                tft->unloadFont();
                return false;
            }
            timer = millis();
        }
        
    }
    tft->unloadFont();
    return true;
}