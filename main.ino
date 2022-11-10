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

#define BACKGROUND_COLOR 0x10C4 //0x2945    //0x2124

// Pobrac biblioteke : ArduinoJson
// Pobrac konwerter: https://www.instructables.com/Converting-Images-to-Flash-Memory-Iconsimages-for-/
// YT: How to program TTGO T-Display - PART3 (Images and Custom Fonts)
// http://www.rinkydinkelectronics.com/t_imageconverter565.php
// 1. Wpisz nazwę miasta
// 2. Wyślij prośbę do: http://api.openweathermap.org/geo/1.0/direct?q=Oława&limit=1&appid=6a0b31b6c9c1f95d47860092dadc1f6c
//                                                                     (miasto)
// 3. [{"name":"Oława","local_names":{"pl":"Oława"},"lat":50.95709295,"lon":17.290269769664455,"country":"PL","state":"Lower Silesian Voivodeship"}]
// Wybież lat i lon.
// 4. Wyszukaj to:
// https://api.openweathermap.org/data/2.5/weather?lat=50.95709295&lon=17.290269769664455&units=metric&lang=pl&appid=

//https://api.openweathermap.org/data/2.5/forecast?lat=50.95709295&lon=17.290269769664455&units=metric&lang=pl&appid=6a0b31b6c9c1f95d47860092dadc1f6c
//                                                    (lat z Oławy)    (lon z Oławy)
// 5. Otrzymujesz to:
// {"coord":{"lon":17.2903,"lat":50.9571},"weather":[{"id":804,"main":"Clouds","description":"overcast clouds","icon":"04d"}],
// "base":"stations","main":{"temp":296.71,"feels_like":296.35,"temp_min":294.83,"temp_max":297.54,"pressure":1019,"humidity":47,"sea_level":1019,"grnd_level":1004},
// "visibility":10000,"wind":{"speed":1.79,"deg":196,"gust":3.33},"clouds":{"all":93},"dt":1667135121,"sys":
// {"type":2,"id":2073402,"country":"PL","sunrise":1667108337,"sunset":1667143793},"timezone":3600,"id":7532481,"name":"Oława","cod":200}

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

TouchScreen ts(&tft, calData);
CurrentWeatherScreen weather_screen(&tft, BACKGROUND_COLOR);
Forecast12Screen forecast_screen(&tft, BACKGROUND_COLOR);

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
    Serial.println("UP");
}

void down()
{
    Serial.println("DOWN");
}

void left()
{
    Serial.println("LEFT");
}

void right()
{
    Serial.println("RIGHT");
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
    // weather_screen.draw(weather);

    forecast = wclient.forecast_weather();
    forecast_screen.draw(forecast);
    

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