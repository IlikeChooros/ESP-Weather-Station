#include "src/data_structures/Hsv_to_rgb.h"
#include "src/calibrate/calibrate_data.h"
#include "src/data_structures/Point.h"
#include "src/output/icons/Icons.h"
#include "src/weather_client/WeatherClient.h"
#include "src/output/screens/CurrentWeatherScreen.h"
#include "src/output/screens/MainScreen.h"
#include "src/output/screens/Forecast12Screen.h"
#include "src/output/screens/FewDaysForecastScreen.h"
#include "src/output/screens/WiFiListScreen.h"
#include "src/output/screens/PasswordInputScreen.h"
#include "src/output/items/ScreenPointItem.h"
#include "src/input/TouchScreen.h"

#include <EEPROM.h>
#include <TFT_eSPI.h> 
#include <SPI.h>

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#define EEPROM_SIZE 13*sizeof(String)+sizeof(uint8_t)

#define CITY_NAME "Oława"
#define BACKGROUND_COLOR 0x10C4
#define X_SCREENS 3
#define Y_SCREENS 1
#define SCREEN_LIST 2
#define MINUTES_15 900000
#define MINUTE 60000
#define SECOND 1000

TFT_eSPI tft = TFT_eSPI();

uint8_t number_of_tries = 0;

HTTPClient http;
bool get_http;

WeatherClient wclient(&http, MINUTES_15);
Weather* weather;
Forecast* forecast;

enum Move_idx
{
    UP,
    DOWN,
    RIGHT,
    LEFT
};

uint64_t lastTimeCheck = 0;

TouchScreen ts(&tft, calData);

MainScreen*** screens = new MainScreen**[X_SCREENS]{
    new MainScreen* [Y_SCREENS] {new CurrentWeatherScreen(&tft, BACKGROUND_COLOR)},  // [0][0]
    new MainScreen* [Y_SCREENS] {new Forecast12Screen(&tft, BACKGROUND_COLOR)},       // [1][0]
    new MainScreen* [Y_SCREENS] {new FewDaysForecastScreen(&tft, BACKGROUND_COLOR)}
};
ScreenPointItem sci(&tft, 150, 230, BACKGROUND_COLOR);

void refresh();

WiFiScreen** wifi_screens = new WiFiScreen* [2]{
    new WiFiListScreen (&tft, BACKGROUND_COLOR, refresh),
    new PasswordInputScreen(&tft, BACKGROUND_COLOR)
};


Point screen_idx(0,0);
uint8_t wifi_screen_idx = 0;

bool try_to_connect_to_wifi(String wifi_ssid)
{
    tft.println("Connecting to WiFi: "+wifi_ssid+" ");

    number_of_tries = 0;
    while(WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        tft.print(".");
        number_of_tries++;

        if (number_of_tries == 8){
            tft.println("");
            tft.println("[-] Failed to connect to WiFi.");
            return false;
        }
    }
    tft.println("");
    tft.println("[+] Connected to the Wifi");
    return true;
}

bool connect_to_wifi_silently()
{
    number_of_tries = 0;
    while(WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        number_of_tries++;

        if (number_of_tries == 8){
            return false;
        }
    }
    return true;
}

void refresh()
{
    wifi_screens[0]->clear_buttons();
    wifi_screens[0]->scan();
    wifi_screens[0]->draw();
}

void left()
{
    move(LEFT);
}

void right()
{
    move(RIGHT);
}

void move(uint8_t move)
{
    if (screen_idx.y == 0)
    {
        switch(move)
        {
            case LEFT:
                screen_idx.x = screen_idx.x > 0 ? screen_idx.x - 1 : X_SCREENS-1;
                break;
            case RIGHT:
                screen_idx.x = screen_idx.x < X_SCREENS-1 ? screen_idx.x + 1: 0;
                break;
            default:
                break;
        }
        tft.fillScreen(BACKGROUND_COLOR);

        // It wont hurt to call both methods on the same screen object
        screens[screen_idx.x][0]->draw(weather, true);
        screens[screen_idx.x][0]->draw(forecast, true);
    }

    sci.draw(3,1,screen_idx.x+1,1);
}

void wifi_setup()
{
    int16_t* pos = ts.read_touch();

    if(pos)
    {
        wifi_screens[wifi_screen_idx]->check(pos);
        if (wifi_screens[wifi_screen_idx]->change())
        {
            wifi_screen_idx = wifi_screen_idx == 0 ? 1 : 0;

            tft.fillScreen(BACKGROUND_COLOR);

            wifi_screens[wifi_screen_idx]->draw(wifi_screens[0]->get_str());
            wifi_screens[wifi_screen_idx]->draw();
            
        }
        delete [] pos;
    }
}

void initial_network_connection(int8_t number_of_networks, bool verbose)
{
    //******************************
    // Read from EEPROM saved wifis
    //

    uint32_t address = 10;
    uint8_t count = EEPROM.read(address);
    Serial.println(String(count));
    address += sizeof(uint8_t);

    String saved_ssid, saved_psw;

    for (uint8_t i=0; i<count; i++)
    {
        saved_ssid = EEPROM.readString(address);
        address += sizeof(saved_ssid);
        saved_psw = EEPROM.readString(address);
        address += sizeof(saved_psw);
        Serial.println(String(i) + ". SSID "+saved_ssid + " PASS "+saved_psw);
        // Compare all found network ssid's to saved one
        // If wifi names are the same, connect to this WiFi
        for (int8_t j=0; j<number_of_networks; j++)
        {
            if (WiFi.SSID(j) == saved_ssid)
            {
                char* temp_ssid = new char[saved_ssid.length()+1];
                char* temp_psw = new char[saved_psw.length()+1];
                
                saved_ssid.toCharArray(temp_ssid, saved_ssid.length()+1);
                saved_psw.toCharArray(temp_psw, saved_psw.length()+1);

                
                WiFi.begin(temp_ssid, temp_psw);

                
                if(verbose)
                {
                    // If successfully connected to wifi
                    if(try_to_connect_to_wifi(temp_ssid))
                    {
                        delete [] temp_ssid;
                        delete [] temp_psw;
                        return;
                    }
                }

                else{
                    if(connect_to_wifi_silently())
                    {
                        delete [] temp_ssid;
                        delete [] temp_psw;
                        return;
                    }
                }
            
            }
        }

        if (i == 5)
        {
            tft.fillScreen(BACKGROUND_COLOR);
            tft.setCursor(0,0);
        }
    }
}

void setup()
{
    EEPROM.begin(EEPROM_SIZE);
    Serial.begin(921600);
    tft.init();
    tft.setRotation(3);

    tft.fillScreen(BACKGROUND_COLOR);
    tft.setTextColor(TFT_GREEN);
    tft.setTextSize(1);

    //******************************
    // Scanning for newtorks
    //
    tft.setCursor(0,0);
    tft.println("Looking for saved WiFi...");

    WiFi.mode(WIFI_STA);
    int8_t number_of_networks = WiFi.scanNetworks();

    if (number_of_networks > 0)
    {
        initial_network_connection(number_of_networks, true);
    }

    ts.on_left(left);
    ts.on_right(right);

    //******************************
    //  Force a connection to WiFi
    //
    if(WiFi.status() != WL_CONNECTED)
    {
        tft.println("Couldnt connect to WiFi.");
        tft.println("Scanning WiFis...");
        wifi_screens[0]->scan();

        tft.fillScreen(BACKGROUND_COLOR);
        wifi_screens[0]->draw();

        while(!wifi_screens[1]->load_main()){wifi_setup();}

        String temp_ssid = wifi_screens[1]->get_str(), temp_pwd = wifi_screens[1]->get_str();

        //*********************************
        // Saving entered network to EEPROM
        //
        uint8_t count = EEPROM.read(10);
        uint32_t address = 10;
        address+=sizeof(uint8_t);

        address += count *2*(sizeof(String));
        if (address <= 512-2*sizeof(String))
        {
            // Serial.println("Address fine: "+String(address));
            EEPROM.writeString(address, temp_ssid);
            EEPROM.commit();

            address += sizeof(temp_ssid);
            EEPROM.writeString(address, temp_pwd);
            EEPROM.commit();

            address += sizeof(temp_pwd);
            count++;
            EEPROM.write(10, count);
            EEPROM.commit();
        }
    }

    get_http = wclient._init_(CITY_NAME);
    tft.println("GET_HTTP: "+String(get_http));

    while(!get_http)
    {
        tft.println("Retrying wclient init...");
        get_http = wclient._init_(CITY_NAME);
        delay(3500);
    }

    tft.fillScreen(BACKGROUND_COLOR);

    weather = new Weather;
    forecast = new Forecast;
    forecast->number_of_forecasts = NUMBER_OF_HOURS_TO_FORECAST;
    forecast->forecasted_weather = new Weather* [NUMBER_OF_HOURS_TO_FORECAST];
    for (uint8_t i=0;i<NUMBER_OF_HOURS_TO_FORECAST; i++)
    {
        forecast->forecasted_weather[i] = new Weather;
    }

    tft.setCursor(0,0);
    tft.setTextColor(TFT_GREEN);
    tft.setTextSize(1);

    // If any of them failed to get weather data, 
    // will try to get it again
    while (!(wclient.current_weather(weather) && wclient.forecast_weather(forecast)))
    {
        tft.println("Failed to obtain data, try restarting ESP");
        delay(1000);

        // ESP should already have got WiFi ssid and password,
        // so it will try to regain connection and try again
        if (WiFi.status() != WL_CONNECTED)
        {
            WiFi.mode(WIFI_STA);
            initial_network_connection(number_of_networks, true);
        }
    }

    screens[0][0]->init();

    EEPROM.end();

    tft.fillScreen(BACKGROUND_COLOR);
    screens[0][0]->draw(weather, true);
    sci.draw(3,1,1,1);
}


void loop()
{
    ts.read();

    if (millis() - lastTimeCheck>= SECOND)
    {
        wclient.current_weather(weather);
        wclient.forecast_weather(forecast);

        // adding 1 second to ESP time
        screens[0][0]->refresh();
        
        screens[screen_idx.x][0]->draw(weather,false);
        screens[screen_idx.x][0]->draw(forecast,false);
        
        lastTimeCheck = millis();


        // Try to regain wifi connection, if lost
        if (WiFi.status() != WL_CONNECTED)
        {
            WiFi.mode(WIFI_STA);
            int8_t number_of_networks = WiFi.scanNetworks();
            if (number_of_networks < 1)
            {
                return;
            }
            initial_network_connection(number_of_networks, false);
        }
    }
}