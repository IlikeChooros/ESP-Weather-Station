#include "WiFiScreen.h"

WiFiScreen::WiFiScreen
(TFT_eSPI* tft, uint16_t bg_c):
tft(tft), bg_c(bg_c) {}

//*****************************
// Returns true if successfully
// connects to WiFi
//*****************************
bool WiFiScreen::
draw_connecting_to_wifi(const String& wifi_name, char* ssid, char* pass){
    uint8_t i = 0;
    while(wifi_name != WiFi.SSID(i)){
        ++i;
    }
    // Mmmm i like spaghetti
    tft->fillRect(55, 70, 210, 100, 0x10A3);
    tft->drawRect(55, 70, 210, 100, TFT_WHITE);

    std::unique_ptr<char[]> ptr_ssid(ssid);
    std::unique_ptr<char[]> ptr_pass(pass);
    std::unique_ptr<TextWrapper> tw(new TextWrapper(tft));

    String wrap;
    tft->loadFont(NOTE_FONT16);
    tft->setTextColor(TFT_LIGHTGREY, 0x10A3);
    tft->drawString("Connecting to:", 90, 75);
    wrap = tw->prepare(210, 20)->wrapBegin(String(ssid));
    tft->drawCentreString(wrap, 160, 95, 2);
    tft->unloadFont();

    std::unique_ptr<WiFiStrenghtItem> wifi(new WiFiStrenghtItem(tft, 200, 115, 35, 0x10A3));
    wifi->draw(WiFi.RSSI(i));
    
    std::unique_ptr<ScreenPointItem> sci(new ScreenPointItem(tft, 140, 135, 0x10A3, 16));
    sci->draw(5, 1, 1, 1);

    uint8_t number_of_tries = 0;
    uint32_t timer = millis();

    while(WiFi.status() != WL_CONNECTED){
        if (millis() - timer < 500){       
            continue;
        }
        number_of_tries++;
        sci->draw(5, 1, (number_of_tries)%5 + 1, 1);
        if (number_of_tries == 14){
            tft->drawRect(55, 70, 210, 100, TFT_RED);
            delay(1000);            
            return false;
        }
        timer = millis();
    }
    tft->drawRect(55, 70, 210, 100, TFT_DARKGREEN);
    delay(1000);
    return true;
}