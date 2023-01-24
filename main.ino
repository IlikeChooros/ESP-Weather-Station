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
#include "src/output/screens/ChartScreen.h"
#include "src/output/items/ScreenPointItem.h"
#include "src/input/TouchScreen.h"

#define CITY_NAME "Oława"
#define BACKGROUND_COLOR 0x10C4
#define X_SCREENS 3
#define Y_SCREENS 1
#define SCREEN_LIST 2
#define MINUTES_15 900000
#define SECOND_10 10000
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
int64_t wifiUpdateTimeCheck = -SECOND_10;
int8_t savedWiFiIdx = 0;
int8_t numberOfSavedWifis = 0;
String** saved_wifi_info = 0;

TouchScreen ts(&tft, calData);

WeatherDataCollector* collector = new WeatherDataCollector(3);

Vector<uint16_t> colors;

ChartScreen* chart_screen = new ChartScreen(&tft, BACKGROUND_COLOR, colors);

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

uint8_t idx = 0;
uint8_t for_idx = 0;

void eeprom_earse(uint16_t starting_address, uint16_t ending_address)
{
    for (;starting_address<ending_address; starting_address++)
    {
        EEPROM.write(starting_address, 0);
    }
    EEPROM.commit();
}

void reset_tft()
{
    tft.fillScreen(BACKGROUND_COLOR);
    tft.setCursor(0,0);
    tft.setTextColor(TFT_GREEN);
    tft.setTextSize(1);
}

void char_to_wifi_info(char* ssid, char* pass, uint8_t idx)
{
    ssid = new char [saved_wifi_info[idx][0].length()+1];
    pass = new char [saved_wifi_info[idx][1].length()+1];

    saved_wifi_info[idx][0].toCharArray(ssid, saved_wifi_info[idx][0].length()+1);
    saved_wifi_info[idx][1].toCharArray(pass, saved_wifi_info[idx][1].length()+1);
}

void reconnect_to_wifi()
{

    if (millis() - wifiUpdateTimeCheck > SECOND_10)
    {
        WiFi.disconnect();
        WiFi.reconnect();
        wifiUpdateTimeCheck = millis();
    }
}

void load_saved_wifis()
{
    //******************************
    // Read from EEPROM saved wifis
    // address = 10 -> number of networks
    // address <11, 11+MAX_SSID_LEN (37)) -> 1. ssid 
    // address <37, 38 + MAX_PASSWORD_LEN (58)) -> 1. password
    // ...
    // address < (prev_address)+1 = x, x + MAX_SSID_LEN> -> k. ssid

    EEPROM.begin(EEPROM_SIZE);
    numberOfSavedWifis = EEPROM.read(10);
    uint16_t address = 11;

    if (numberOfSavedWifis)
    {
        saved_wifi_info = new String* [numberOfSavedWifis];
    }

    String saved_ssid, saved_psw;

    for (uint8_t i=0; i<numberOfSavedWifis; i++)
    {
        saved_ssid = EEPROM.readString(address);
        address += MAX_SSID_LENGHT;
        saved_psw = EEPROM.readString(address);
        address += MAX_PASSWORD_LENGHT;
        saved_wifi_info[i] = new String[2]{
            saved_ssid,
            saved_psw
        };
    }
    EEPROM.end();
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

void up()
{
    move(UP);
}

void down()
{
    move(DOWN);
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
            case UP:
                screen_idx.y = 1;
                break;
            case DOWN:
                screen_idx.y = 1;
                break;
            default:
                break;
        }
        tft.fillScreen(BACKGROUND_COLOR);

        if (screen_idx.y == 0)
        {
            // It wont hurt to call both methods on the same screen object
            screens[screen_idx.x][0]->draw(weather, true);
            screens[screen_idx.x][0]->draw(forecast, true);
            sci.draw(3,1,screen_idx.x+1,1);
        }
        else
        {
            chart_screen->draw(collector->get_data(0), collector->get_min_max(0), true);
        }
    }

    else if (screen_idx.y == 1)
    {
        switch(move)
        {
            case UP:
                screen_idx.y = 0;
                break;
            case DOWN:
                screen_idx.y = 0;
                break;
            case LEFT:
            case RIGHT:
                break;
        }

        tft.fillScreen(BACKGROUND_COLOR);
        screens[screen_idx.x][0]->draw(weather, true);
        screens[screen_idx.x][0]->draw(forecast, true);
        sci.draw(3,1,screen_idx.x+1,1);
    }
    
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

void force_wifi_connection()
{
    tft.println("Scanning WiFis...");

    wifi_screens[0]->scan();

    tft.fillScreen(BACKGROUND_COLOR);
    wifi_screens[0]->draw();

    while(!wifi_screens[wifi_screen_idx]->load_main()){wifi_setup();}

    String temp_ssid = wifi_screens[1]->get_str(), temp_pwd = wifi_screens[1]->get_str();
    //****************************
    // Already connected to WiFi 
    // without entering password
    if (!wifi_screens[1]->load_main() || (temp_ssid == "" || temp_pwd == "") )
    {
        return;
    }
    //******************************************
    // Checking if entered wifi ssid
    // is already saved, if so updating password
    EEPROM.begin(EEPROM_SIZE);
    uint16_t address = 11;
    for (uint8_t i=0; i<numberOfSavedWifis; i++)
    {
        if (saved_wifi_info[i][0] == temp_ssid && temp_pwd.length() < MAX_PASSWORD_LENGHT)
        {
            address += i*(MAX_PASSWORD_LENGHT + MAX_SSID_LENGHT)+MAX_SSID_LENGHT;

            if (EEPROM.readString(address).length() > temp_pwd.length())
            {
                eeprom_earse(address + temp_pwd.length(), address + EEPROM.readString(address).length());
            }
            
            EEPROM.writeString(address, temp_pwd);
            EEPROM.commit();

            EEPROM.end();

            saved_wifi_info[i][1] = temp_pwd;
            return;
        }
    }


    //*********************************
    // Saving entered network to EEPROM
    //
    address += numberOfSavedWifis*(MAX_PASSWORD_LENGHT + MAX_SSID_LENGHT);
    if (address <= 512-MAX_PASSWORD_LENGHT-MAX_SSID_LENGHT && temp_ssid.length() < MAX_SSID_LENGHT && temp_pwd.length() < MAX_SSID_LENGHT)
    {
        EEPROM.writeString(address, temp_ssid);

        address += MAX_SSID_LENGHT;
        EEPROM.writeString(address, temp_pwd);

        address += MAX_PASSWORD_LENGHT;
        numberOfSavedWifis++;
        EEPROM.write(10, numberOfSavedWifis);
        EEPROM.commit();
    }

    //**************************
    // Updating saved_wifi_info
    //
    if (numberOfSavedWifis-1 == 0)
    {
        EEPROM.end();
        return;
    }

    for (int8_t i=0; i<numberOfSavedWifis-1;i++)
    {
        delete [] saved_wifi_info[i];
    }
    delete [] saved_wifi_info;

    EEPROM.end();
    load_saved_wifis();
}

void setup()
{
    Serial.begin(921600);
    tft.init();
    tft.setRotation(3);

    //******************************
    // Scanning for newtorks
    //
    // EEPROM.begin(EEPROM_SIZE);
    // eeprom_earse(10, 150);
    // EEPROM.end();
    reset_tft();
    load_saved_wifis();
    int8_t number_of_networks; 
    wifi_screens[0]->init();

    ts.on_left(left);
    ts.on_right(right);
    ts.on_down(down);
    ts.on_up(up);

    //******************************
    //  Force a connection to WiFi
    //
    force_wifi_connection();

    //****************************
    // initialize weather client
    reset_tft();
    get_http = wclient._init_(CITY_NAME);
    tft.println("GET_HTTP: "+String(get_http));

    while(!get_http)
    {
        tft.println("Retrying wclient init...");
        get_http = wclient._init_(CITY_NAME);
        delay(3500);
    }

    weather = new Weather;
    forecast = new Forecast;
    forecast->number_of_forecasts = NUMBER_OF_HOURS_TO_FORECAST;
    forecast->forecasted_weather = new Weather* [NUMBER_OF_HOURS_TO_FORECAST];
    for (uint8_t i=0;i<NUMBER_OF_HOURS_TO_FORECAST; i++)
    {
        forecast->forecasted_weather[i] = new Weather;
    }

    reset_tft();
    // If any of them failed to get weather data, 
    // will try to get it again
    while (!(wclient.current_weather(weather) && wclient.forecast_weather(forecast)))
    {
        tft.println("Failed to obtain data, try restarting ESP");

        // ESP should already have got WiFi ssid and password,
        // so it will try to regain connection and try again
        // to get weather data
        if (WiFi.status() != WL_CONNECTED)
        {
            reconnect_to_wifi();
        }
        delay(3000);
    }

    screens[0][0]->init();

    tft.fillScreen(BACKGROUND_COLOR);
    screens[0][0]->draw(weather, true);
    sci.draw(3,1,1,1);

    collector->collect_all(forecast, 0, 0);
}


void loop()
{
    ts.read();

    if (millis() - lastTimeCheck < SECOND)
    {
        return;
    }
    wclient.current_weather(weather);
    wclient.forecast_weather(forecast);

    // adding 1 second to ESP time
    screens[0][0]->refresh(false);
    
    if (screen_idx.y == 0)
    {
        screens[screen_idx.x][0]->draw(weather,false);
        screens[screen_idx.x][0]->draw(forecast,false);
    }
    
    
    lastTimeCheck = millis();

    collector->collect(weather, 1);

    // Try to regain wifi connection, if lost
    if (WiFi.status() != WL_CONNECTED)
    {
        reconnect_to_wifi();
    }
}