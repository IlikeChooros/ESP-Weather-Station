#include "src/data_structures/Hsv_to_rgb.h"
#include "src/calibrate/calibrate_data.h"
#include "src/data_structures/Point.h"
#include "src/output/icons/Icons.h"
#include "src/weather_client/WeatherClient.h"
#include "src/output/CurrentWeatherScreen.h"
#include "src/output/Forecast12Screen.h"
#include "src/input/TouchScreen.h"

#include <TFT_eSPI.h> 
#include <SPI.h>

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#define BACKGROUND_COLOR 0x10C4

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

TouchScreen ts(&tft, calData);
CurrentWeatherScreen weather_screen(&tft, BACKGROUND_COLOR);
Forecast12Screen forecast_screen(&tft, BACKGROUND_COLOR);

Point screen_idx(0,0);

bool try_to_connect_to_wifi()
{
    tft.println("Connecting...");

    while(WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        tft.println("Connecting to WiFi...");
        number_of_tries++;

        if (number_of_tries == 6){
            tft.println("[-] Failed to connect to WiFi.");
            return false;
        }
    }

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
                    tft.fillScreen(BACKGROUND_COLOR);
                    weather_screen.draw(weather, true);
                    screen_idx.x = 0;
                }
                break;
            case RIGHT:
                if (screen_idx.x == 0)
                {
                    tft.fillScreen(BACKGROUND_COLOR);
                    forecast_screen.draw(forecast, true);
                    screen_idx.x = 1;
                }
                break;
            default:
                break;
        }
    }
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

    forecast = wclient.update(forecast);
    weather = wclient.update(weather);

    screen_idx.x = 1;
    forecast_screen.draw(forecast, true);
    // forecast_screen.draw(forecast);
    

    // delay(2000);
    // weather->_wind_speed=15;
    // weather->_feels_like = 28;
    // weather->_temp = 28;
    // weather_screen.draw(weather);
    // weather->_icon = "03d";
    // delay(2000);

    // weather->_feels_like = 25;
    // weather->_wind_speed=21;
    // weather->_temp = 20;
    // weather->_icon = "02d";
    // weather_screen.draw(weather);
    //delay(2000);

    // weather->_feels_like = 20;
    // weather->_temp = 18;
    // weather_screen.draw(weather);
    // weather->_icon = "50d";
    // delay(2000);

    // weather->_feels_like = 4;
    // weather->_temp = 5;
    // weather_screen.draw(weather);

    // weather_screen.draw_main_screen(weather, BACKGROUND_COLOR);
    // weather->_icon = "03d";
    // delay(2000);

    // weather->_feels_like =  5;

    // weather_screen.draw_main_screen(weather, BACKGROUND_COLOR);
    // weather->_icon = "03n";
    // delay(2000);

    // weather->_feels_like =  0;

    // weather_screen.draw_main_screen(weather, BACKGROUND_COLOR);
    // weather->_icon = "04d";
    // delay(2000);

    // weather->_feels_like =  -5;

    // weather_screen.draw_main_screen(weather, BACKGROUND_COLOR);
    // weather->_icon = "09d";
    // delay(2000);

    // weather->_feels_like =  -10;

    // weather_screen.draw_main_screen(weather, BACKGROUND_COLOR);
    // weather->_icon = "10d";
    // delay(2000);


    // weather_screen.draw_main_screen(weather, BACKGROUND_COLOR);
    // weather->_icon = "13d";
    // delay(2000);

    // weather->_feels_like =  -15;

    // weather_screen.draw_main_screen(weather, BACKGROUND_COLOR);
    // weather->_icon = "50d";
    // delay(2000);

    // weather->_feels_like =  -20;

    // weather_screen.draw_main_screen(weather, BACKGROUND_COLOR);
    // weather->_icon = "50n";
    // delay(2000);


    // weather_screen.draw_main_screen(weather, BACKGROUND_COLOR);

    // tft.println("MAIN: "+weather->_main);
    // tft.println("ICON: "+weather->_icon);
    // tft.println("TEMP: "+String(weather->_temp));
    // tft.println("FEELS_LIKE: "+String(weather->_feels_like));
    // tft.println("PRESSURE: "+String(weather->_pressure));
    // tft.println("HUMIDITY: "+String(weather->_humidity));
    // tft.println("WIND_SPEED: "+String(weather->_wind_speed));
    // tft.println("SUNRISE: "+String(weather->_sunrise));
    // tft.println("SUNSET: "+String(weather->_sunset));

    // forecast = wclient.forecast_weather();
    // weather = forecast->forecasted_weather;

    // for (uint8_t i=0;i<8;i++)
    // {
    //     tft.setCursor(0,10);
    //     tft.fillScreen(BACKGROUND_COLOR);

    //     tft.println("MAIN: "+weather->_main);
    //     tft.println("ICON: "+weather->_icon);
    //     tft.println("TEMP: "+String(weather->_temp));
    //     tft.println("FEELS_LIKE: "+String(weather->_feels_like));
    //     tft.println("PRESSURE: "+String(weather->_pressure));
    //     tft.println("HUMIDITY: "+String(weather->_humidity));
    //     tft.println("WIND_SPEED: "+String(weather->_wind_speed));

    //     weather++;
    //     delay(2000);
    // }

    // Sun sun1(&tft, 0, 0,  100, BACKGROUND_COLOR);
    // Sun sun2(&tft, 100, 0,  75, BACKGROUND_COLOR);
    // Sun sun3(&tft, 175, 0,  50, BACKGROUND_COLOR);
    // Sun sun4(&tft, 225, 0,  25, BACKGROUND_COLOR);
    // sun1.draw();
    // sun2.draw();
    // sun3.draw();
    // sun4.draw();

    // Clouds cl1 (&tft, 0,100,100, BACKGROUND_COLOR);
    // Clouds cl2 (&tft, 100,100,75, BACKGROUND_COLOR);
    // Clouds cl3 (&tft, 175,100,50, BACKGROUND_COLOR);
    // Clouds cl4 (&tft, 225,100,25, BACKGROUND_COLOR);

    // cl1.draw();
    // cl2.draw();
    // cl3.draw();
    // cl4.draw();

    // CloudsDay sun1(&tft, 0, 0,  100, BACKGROUND_COLOR);
    // CloudsNight sun2(&tft, 100, 0, 100, BACKGROUND_COLOR);
    // ManyClouds sun3 (&tft, 200, 0, 100, BACKGROUND_COLOR);
    // sun1.draw();
    // sun2.draw();
    // sun3.draw();

    // FewCloudsDay cl1 (&tft, 0,100,100, BACKGROUND_COLOR);
    // FewCloudsNight cl2 (&tft, 100,100,100, BACKGROUND_COLOR);
    // Snow cl3 (&tft, 200,100,100, BACKGROUND_COLOR);


    // cl1.draw();
    // cl2.draw();
    // cl3.draw();
}


void loop()
{
    ts.read();
}