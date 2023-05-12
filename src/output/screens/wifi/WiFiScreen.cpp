#include "WiFiScreen.h"

WiFiScreen::WiFiScreen
(TFT_eSPI* tft, uint16_t bg_c):
tft(tft), bg_c(bg_c) {}

void 
animate(TFT_eSPI* tft, uint8_t idx){
    drawWifi(tft, 160, 120, 30, 3, TFT_DARKGREY);
    
}

//*****************************
// Returns true if successfully
// connects to WiFi
//*****************************
bool WiFiScreen::
draw_connecting_to_wifi(String wifi_name, char* ssid, char* pass){
    tft->fillRect(55, 70, 210, 100, 0x10A3);
    tft->drawRect(55, 70, 210, 100, TFT_WHITE);

    std::unique_ptr<char[]> ptr_ssid(ssid);
    std::unique_ptr<char[]> ptr_pass(pass);

    tft->loadFont(NOTE_FONT16);
    tft->setTextColor(TFT_GREEN, TFT_DARKGREY);
    tft->setCursor(90, 75);
    tft->print("Connecting to:");
    tft->drawCentreString(ssid, 160, 95, 2);
    tft->unloadFont();

    drawWifi(tft, 215, 110, 30, 3, 0x10A3);

    ScreenPointItem sci(tft, 70, 130, 0x10A3, 30);
    
    sci.draw(3, 1, 1, 1);

    uint8_t number_of_tries = 0;
    uint32_t timer = millis();

    while(WiFi.status() != WL_CONNECTED){
        if (millis() - timer < 1000){
            continue;
        }
        number_of_tries++;
        sci.draw(3, (number_of_tries+1)%3 + 1, 1, 1);
        if (number_of_tries == 10){
            delay(1000);

            tft->fillScreen(bg_c);
            draw(wifi_name);
            draw(true);
            
            return false;
        }
        timer = millis();
    }
    return true;
}