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
#include "src/output/icons/ScreenPointItem.h"
#include "src/input/TouchScreen.h"


#include <TFT_eSPI.h> 
#include <SPI.h>

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#define BACKGROUND_COLOR 0x10C4
#define X_SCREENS 3
#define Y_SCREENS 1
#define SCREEN_LIST 2
#define MINUTES_15 900000
#define MINUTE 60000
#define SECOND 1000

TFT_eSPI tft = TFT_eSPI();

const char* ssid =  "bc772c"; //"bc772c"; //"Black Shark";   // "NETIASPOT-2,4GHz-69C140"; // bc772c
const char* password =  "269929817"; //"269929817"; //"12345abc";   //"6epTdSSVW22X"; // 269929817
const String current_weather = "https://api.openweathermap.org/data/2.5/weather?lat=50.95709295&lon=17.290269769664455&units=metric&lang=pl&appid=";
const String key = "6a0b31b6c9c1f95d47860092dadc1f6c";

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

uint32_t lastTimeCheck = 0;
uint32_t last_15_minCheck = 0;

TouchScreen ts(&tft, calData);

MainScreen*** screens = new MainScreen**[X_SCREENS]{
    new MainScreen* [Y_SCREENS] {new CurrentWeatherScreen(&tft, BACKGROUND_COLOR)},  // [0][0]
    new MainScreen* [Y_SCREENS] {new Forecast12Screen(&tft, BACKGROUND_COLOR)},       // [1][0]
    new MainScreen* [Y_SCREENS] {new FewDaysForecastScreen(&tft, BACKGROUND_COLOR)}
};
ScreenPointItem sci(&tft, 150, 230, BACKGROUND_COLOR);
WiFiListScreen wifi_screen(&tft, BACKGROUND_COLOR);

Point screen_idx(0,0);

bool try_to_connect_to_wifi()
{
    Serial.println("Connecting...");
    tft.println("Connecting...");

    while(WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi...");
        tft.println("Connecting to WiFi...");
        number_of_tries++;

        if (number_of_tries == 6){
            Serial.println("[-] Failed to connect to WiFi.");
            tft.println("[-] Failed to connect to WiFi.");
            return false;
        }
    }
    Serial.println("[+] Connected to the Wifi");
    tft.println("[+] Connected to the Wifi");
    return true;
}

void print_touch()
{
    Serial.println("TOUCHING!!!");
}


void up()
{

}

void down()
{

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
                screen_idx.x = screen_idx.x > 0 ? screen_idx.x - 1 : 2;
                break;
            case RIGHT:
                screen_idx.x = screen_idx.x < 2 ? screen_idx.x + 1: 0;
                break;
            default:
                break;
        }
        if (screen_idx.x == 0)
        {
            tft.fillScreen(BACKGROUND_COLOR);
            screens[screen_idx.x][screen_idx.y]->draw(weather, true);
        }
        else
        {
            tft.fillScreen(BACKGROUND_COLOR);
            screens[screen_idx.x][screen_idx.y]->draw(forecast, true);
        }
    }

    sci.draw(3,1,screen_idx.x+1,1);
}

void setup()
{
    Serial.begin(921600);
    WiFi.begin(ssid, password);
    tft.init();
    tft.setRotation(3);

    tft.fillScreen(BACKGROUND_COLOR);
    tft.setTextColor(TFT_GREEN);
    tft.setTextSize(1);

    ts.on_down(down);
    ts.on_left(left);
    ts.on_right(right);
    ts.on_up(up);

    if(!try_to_connect_to_wifi())
    {
        return;
    }

    get_http = wclient._init_("Oława");
    tft.println("GET_HTTP: "+String(get_http));

    while(!get_http)
    {
        tft.println("Retrying.");
        get_http = wclient._init_("Oława");
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

    wclient.current_weather(weather);
    wclient.forecast_weather(forecast);

    screens[0][0]->init();

    Serial.println("SCANNING");
    wifi_screen.scan(print_touch);
    Serial.println("DRAWING");
    wifi_screen.draw();

    //screens[screen_idx.x][screen_idx.y]->draw(weather, true);
    //sci.draw(3,1,1,1);
}


void loop()
{
    int16_t* pos = ts.read_buttons();

    if(pos)
    {
        Serial.println("if (pos)");
        wifi_screen.check(pos);
        delete [] pos;
    }


    if (millis() - lastTimeCheck > MINUTE)
    {
        wifi_screen.clear_buttons();
        wifi_screen.scan(print_touch);
        tft.fillScreen(BACKGROUND_COLOR);
        wifi_screen.draw();
        lastTimeCheck = millis();
    }
    
    // ts.read();

    // if (millis() - lastTimeCheck> SECOND)
    // {
    //     wclient.current_weather(weather);
    //     wclient.forecast_weather(forecast);
    //     // drawing main screen time data
    //     screens[0][0]->refresh();
    //     if (screen_idx.x == 0)
    //     {
    //         screens[0][0]->draw(weather, false);
    //     }
    //     lastTimeCheck = millis();
    // }
}