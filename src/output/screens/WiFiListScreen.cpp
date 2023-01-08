#include "WiFiListScreen.h"

WiFiListScreen::WiFiListScreen(TFT_eSPI* tft, uint16_t bg_c)
{
    this->tft = tft;
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    this->bg_c = bg_c;
}

//----------------------------
// The argument is a function, which will be
// called when a wifi button will be pressed
// returns button list for touch screen
//----------------------------
TouchButton** WiFiListScreen::scan(void(*on_press)(void))
{
    number_of_networks = WiFi.scanNetworks();
    wifis = 0;
    buttons = 0;

    Serial.println("NETWORKS: "+String(number_of_networks));
    if (!number_of_networks)
    {
        return 0;
    }

    uint16_t x = 20, y = 20;
    wifis = new WiFiListItem* [number_of_networks];
    
    
    if (number_of_networks > 6)
    {
        scroll = true;
        buttons = new TouchButton* [6];
    }
    else{
        buttons = new TouchButton* [number_of_networks];
    }

    for (uint8_t i=0;i<number_of_networks;i++)
    {
        Serial.println(String(i)+" SSID "+String(WiFi.SSID(i))+" STRENGHT "+String(WiFi.RSSI(i)));
        wifis[i] = new WiFiListItem(tft, x, y + (i%6) *HEIGHT + OFFSET, WIDTH, HEIGHT, WiFi.SSID(i), bg_c);
        wifis[i]->set_strenght(WiFi.RSSI(i));
        if (i<6)
        {
            buttons[i] = wifis[i]->get_button();
            buttons[i]->set_on_press(on_press);
        }
    }

    Serial.println("SCAN END");

    return buttons;
}

uint8_t WiFiListScreen::get_number_of_networks()
{
    return number_of_networks < 6 ? number_of_networks : 6;
}

//------------------------
// Before using it, make sure
// envoke scan() method
//------------------------
void WiFiListScreen::draw()
{
    if (!number_of_networks)
    {
        return;
    }

    for (uint8_t i=0; i<number_of_networks; i++)
    {
        if (i<6)
        {
            wifis[i]->draw();
        }
        delete wifis[i];
    }
    delete [] wifis;
}

void WiFiListScreen::clear_buttons()
{
    if (!number_of_networks)
    {
        return;
    }

    uint8_t d = number_of_networks < 6 ? number_of_networks : 6;
    for (uint8_t i=0; i<d; i++)
    {
        buttons[i]->clear();
        delete buttons[i];
    }
    delete [] buttons;
}