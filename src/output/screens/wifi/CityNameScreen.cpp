#include "CityNameScreen.h"

bool CityNameScreen::
load_main(){
    return this->load_main_;
}

bool CityNameScreen::
change(){
    return this->change_;
}

bool CityNameScreen::
draw_get(String city_name){

    tft->loadFont(NOTE_FONT16);
    tft->setTextColor(TFT_LIGHTGREY, 0x10A3);
    tft->fillRect(55, 70, 210, 100, 0x10A3);
    tft->drawRect(55, 70, 210, 100, TFT_LIGHTGREY);
    std::unique_ptr<TextWrapper> tw(new TextWrapper(tft));
    String wrap(tw->prepare(130, 10)->wrapBegin(std::forward<String>(city_name)));

    tft->drawString("Searching: " + wrap, 60, 75);

    std::unique_ptr<ScreenPointItem> sci(new ScreenPointItem(tft, 160, 135, 0x10A3, 20));
    sci->draw(3, 1, 1, 1);

    uint64_t timer = millis(), delta;
    bool successful = true;
    uint16_t color = TFT_GREEN;
    auto payload = wclient->get_all_cities_info(city_name);
    String msg("Found: "+String(payload.size()));
    
    if(payload.empty()){
        successful = false;
        color = TFT_RED;
        msg = "Not found.";
    }
    delta = millis() - timer;
    delta = delta > 300 ? delta : 400;
    delay(100);
    sci->draw(3, 1, 2, 1);
    delay(delta*2);
    sci->draw(3, 1, 3, 1);
    tft->drawRect(55, 70, 210, 100, color);
    tft->drawString(msg, 60, 92);
    tft->unloadFont();
    delay(500);
    return successful;
}