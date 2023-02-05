#include "WiFiScreen.h"

WiFiScreen::WiFiScreen(TFT_eSPI* tft, int16_t bg_c)
{
    this->tft = tft;
    this->bg_c = bg_c;
}

//*****************************
// Returns true if successfully
// connects to WiFi
//*****************************
bool WiFiScreen::draw_connecting_to_wifi(String wifi_name, char* ssid, char* pass)
{    tft->fillRect(55, 70, 210, 100, TFT_DARKGREY);
    tft->drawRect(55, 70, 210, 100, TFT_WHITE);

    tft->setTextSize(1);
    tft->setTextFont(2);
    tft->setTextColor(TFT_GREEN);
    tft->setCursor(90, 75);
    tft->print("Connecting to:");

    tft->drawCentreString(ssid, 160, 95, 2);

    tft->setCursor(100, 120);
    tft->setTextSize(3);
    tft->setTextColor(TFT_DARKGREEN);
    
    uint8_t number_of_tries = 0;

    uint32_t timer = millis();

    while(WiFi.status() != WL_CONNECTED)
    {
        if (millis() - timer > 1000)
        {
            tft->print(".");
            number_of_tries++;

            if (number_of_tries == 10){
                tft->setTextSize(1);
                tft->setTextColor(TFT_RED);
                tft->drawCentreString("Failed.", 160, 115, 2);
                delay(1000);
                delete [] ssid;
                delete [] pass;

                tft->fillScreen(bg_c);
                draw(wifi_name);
                draw(true);
                return false;
            }
            timer = millis();
        }
        
    }

    delete [] ssid;
    delete [] pass;

    return true;
}