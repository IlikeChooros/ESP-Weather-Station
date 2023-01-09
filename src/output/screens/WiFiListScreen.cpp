#include "WiFiListScreen.h"

//----------------------------
// The argument is a function, which will be
// called when a wifi button will be pressed
// returns button list for touch screen
//----------------------------
void WiFiListScreen::scan()
{
    change_ = false;
    onRelease = false;
    number_of_networks = WiFi.scanNetworks();
    wifis = 0;

    Serial.println("NETWORKS: "+String(number_of_networks));
    if (!number_of_networks)
    {
        return;
    }

    uint16_t x = 10, y = 20;
    number_of_networks = number_of_networks < 6 ? number_of_networks : 6;

    wifis = new TouchButton* [number_of_networks];
    
    for (uint8_t i=0;i<number_of_networks;i++)
    {
        Serial.println(String(i)+" SSID "+String(WiFi.SSID(i))+" STRENGHT "+String(WiFi.RSSI(i)));
        wifis[i] = new WiFiListItem(tft, x, y + (i%6) *(HEIGHT+OFFSET), WIDTH, HEIGHT, WiFi.SSID(i), WiFi.RSSI(i), bg_c);
    }

    Serial.println("SCAN END");
}

void WiFiListScreen::check(int16_t* pos)
{
    for (uint8_t i=0; i<number_of_networks; i++)
    {
        if (onRelease)
        {
            wifis[onReleaseIdx]->draw();
            onRelease = false;
        }

        if (wifis[i]->check(pos[0], pos[1]))
        {
            picked_wifi = wifis[i]->get_str();
            change_ = true;
            onRelease = true;
            onReleaseIdx = i;
            return;
        }
    }

    refresh_button->check(pos[0], pos[1]);
}

//---------------------------------
// returns true if this screen has to be
// changed to another one
//---------------------------------
bool WiFiListScreen::change()
{
    return this->change_;
}


//------------------------
// Before using it, make sure
// envoke scan() method
//------------------------
void WiFiListScreen::draw()
{
    for (uint8_t i=0; i<number_of_networks; i++)
    {
        wifis[i]->draw();
    }

    refresh_button->draw();
}

void WiFiListScreen::clear_buttons()
{
    if (!number_of_networks)
    {
        return;
    }
    for (uint8_t i=0; i<number_of_networks; i++)
    {
        delete wifis[i];
    }
    delete [] wifis;
}