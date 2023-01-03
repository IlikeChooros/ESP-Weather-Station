#include "src/data_structures/Hsv_to_rgb.h"
#include "src/calibrate/calibrate_data.h"
#include "src/data_structures/Point.h"
#include "src/output/icons/Icons.h"
#include "src/weather_client/WeatherClient.h"
#include "src/output/CurrentWeatherScreen.h"
#include "src/output/MainScreen.h"
#include "src/output/Forecast12Screen.h"
#include "src/output/FewDaysForecastScreen.h"
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
#define MINUTES_5 60000*5
#define MINUTE 60000

TFT_eSPI tft = TFT_eSPI();

const char* ssid =  "bc772c"; //"Black Shark";   // "NETIASPOT-2,4GHz-69C140"; // bc772c
const char* password =  "269929817"; //"12345abc";   //"6epTdSSVW22X"; // 269929817
const String current_weather = "https://api.openweathermap.org/data/2.5/weather?lat=50.95709295&lon=17.290269769664455&units=metric&lang=pl&appid=";
const String key = "6a0b31b6c9c1f95d47860092dadc1f6c";

uint8_t number_of_tries = 0;

HTTPClient http;
bool get_http;

WeatherClient wclient(&http);
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

TouchScreen ts(&tft, calData);

MainScreen*** screens = new MainScreen**[X_SCREENS]{
    new MainScreen* [Y_SCREENS] {new CurrentWeatherScreen(&tft, BACKGROUND_COLOR)},  // [0][0]
    new MainScreen* [Y_SCREENS] {new Forecast12Screen(&tft, BACKGROUND_COLOR)},       // [1][0]
    new MainScreen* [Y_SCREENS] {new FewDaysForecastScreen(&tft, BACKGROUND_COLOR)}
};
ScreenPointItem sci(&tft, 150, 230, BACKGROUND_COLOR);

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
                if (screen_idx.x == 1)
                {
                    screen_idx.x = 0;
                    tft.fillScreen(BACKGROUND_COLOR);
                    //weather = wclient.update(weather);
                    screens[screen_idx.x][screen_idx.y]->draw(weather, true);
                }
                else if (screen_idx.x == 2)
                {
                    tft.fillScreen(BACKGROUND_COLOR);
                    screen_idx = 1;
                    screens[screen_idx.x][screen_idx.y]->draw(forecast, true);

                }
                break;
            case RIGHT:
                if (screen_idx.x == 0 || screen_idx.x == 1)
                {
                    tft.fillScreen(BACKGROUND_COLOR);
                    screen_idx.x++;
                    //draw_update_forecast();
                    screens[screen_idx.x][screen_idx.y]->draw(forecast, true);
                }
                break;
            default:
                break;
        }
    }

    sci.draw(3,1,screen_idx.x+1,1);
}

void setup()
{
    Serial.begin(921600);
    WiFi.begin(ssid, password);
    tft.init();
    tft.setRotation(1);

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
    weather = wclient.current_weather();
    forecast = wclient.forecast_weather();

    screens[screen_idx.x][screen_idx.y]->draw(weather, true);
    sci.draw(3,1,1,1);
}


void loop()
{
    ts.read();

    if (screen_idx.x == 0 && millis() - lastTimeCheck> MINUTE)
    {
        lastTimeCheck = millis();
        // drawing main screen time data
        screens[0][0]->refresh();
    }
}