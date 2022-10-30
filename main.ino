#include "src/calibrate/calibrate_data.h"
#include "src/data_structures/Point.h"
#include "src/output/Coordinate_system.h"

#include <WiFi.h>
#include <HTTPClient.h>

// 1. Wpisz nazwę miasta
// 2. Wyślij prośbę do: http://api.openweathermap.org/geo/1.0/direct?q=Oława&limit=1&appid=6a0b31b6c9c1f95d47860092dadc1f6c
//                                                                     (miasto)
// 3. [{"name":"Oława","local_names":{"pl":"Oława"},"lat":50.95709295,"lon":17.290269769664455,"country":"PL","state":"Lower Silesian Voivodeship"}]
// Wybież lat i lon.
// 4. Wyszukaj to:
// https://api.openweathermap.org/data/2.5/weather?lat=50.95709295&lon=17.290269769664455&lang=pl&appid=6a0b31b6c9c1f95d47860092dadc1f6c
//                                                    (lat z Oławy)    (lon z Oławy)
// 5. Otrzymujesz to:
// {"coord":{"lon":17.2903,"lat":50.9571},"weather":[{"id":804,"main":"Clouds","description":"overcast clouds","icon":"04d"}],
// "base":"stations","main":{"temp":296.71,"feels_like":296.35,"temp_min":294.83,"temp_max":297.54,"pressure":1019,"humidity":47,"sea_level":1019,"grnd_level":1004},
// "visibility":10000,"wind":{"speed":1.79,"deg":196,"gust":3.33},"clouds":{"all":93},"dt":1667135121,"sys":
// {"type":2,"id":2073402,"country":"PL","sunrise":1667108337,"sunset":1667143793},"timezone":3600,"id":7532481,"name":"Oława","cod":200}

TFT_eSPI tft = TFT_eSPI();

Point touch_point;

bool touch_pressed = false;

const char* ssid = "bc772c";
const char* password = "269929817";
const String endpoint = "";
const String key = "6a0b31b6c9c1f95d47860092dadc1f6c";

void setup()
{
    Serial.begin(921600);
    WiFi.begin(ssid, password);
    tft.init();
    tft.setRotation(1);
    tft.setTouch(calData);

    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_GREEN);
    tft.setTextSize(1);
    tft.println("Connecting...");

    while(WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        tft.println("Connecting to WiFi...");
    }

    tft.println("[+] Connected to the Wifi");
}


void loop()
{
    // touch_pressed = tft.getTouch(&touch_point.x, &touch_point.y);

    // if (touch_pressed)
    // {
    //     tft.fillCircle(touch_point.x, touch_point.y,3, TFT_GOLD);
    // }
}