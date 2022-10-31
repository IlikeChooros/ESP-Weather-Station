#include "src/calibrate/calibrate_data.h"
#include "src/data_structures/Point.h"
#include "src/output/Coordinate_system.h"

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// Pobrac biblioteke : ArduinoJson
// Pobrac konwerter: https://www.instructables.com/Converting-Images-to-Flash-Memory-Iconsimages-for-/



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

Point touch_point;

bool touch_pressed = false;

const char* ssid = "NETIASPOT-2,4GHz-69C140"; // bc772c
const char* password = "6epTdSSVW22X"; // 269929817
const String current_weather = "https://api.openweathermap.org/data/2.5/weather?lat=50.95709295&lon=17.290269769664455&units=metric&lang=pl&appid=";
const String key = "6a0b31b6c9c1f95d47860092dadc1f6c";

uint8_t number_of_tries = 0;

HTTPClient http;
int16_t http_code;

void try_to_connect_to_wifi()
{
    tft.println("Connecting...");

    while(WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        tft.println("Connecting to WiFi...");
        number_of_tries++;

        if (number_of_tries == 10){
            tft.println("[-] Failed to connect to WiFi.");
            return;
        }
    }

    tft.println("[+] Connected to the Wifi");
}

void get_weather()
{
    tft.setCursor(0,0);
    if(http_code == 200){
        String payload = http.getString();

        StaticJsonDocument<200> filter;
        filter["name"] = true;
        filter["main"]["temp"] = true;

        // Deserialize the document
        StaticJsonDocument<400> doc;
        deserializeJson(doc, payload, DeserializationOption::Filter(filter));

        tft.print("[+] Succesful request GET: ");
        tft.println(http_code);
        tft.println(doc["name"].as<const char*>());
        tft.println(String(doc["main"]["temp"].as<double>()));
        tft.println(payload);

    }
    else{
        tft.println("[-] Error on HTTP request: " + String(http_code));
    }

    http.end();
}

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

    try_to_connect_to_wifi();
    tft.fillScreen(TFT_BLACK);

    http.begin(current_weather + key);
    http_code = http.GET();

    get_weather();
}


void loop()
{

}