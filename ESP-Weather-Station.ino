#include "src/calibrate/calibrate_data.h"

//-----------------------------------------
// Weather screens
#include "src/output/screens/weather/CurrentWeatherScreen.h"
#include "src/output/screens/weather/Forecast12Screen.h"
#include "src/output/screens/weather/FewDaysForecastScreen.h"

//-----------------------------------------
// WiFi setup screens
#include "src/output/screens/wifi/WiFiListScreen.h"
#include "src/output/screens/wifi/PasswordInputScreen.h"
#include "src/output/screens/wifi/CityNameInputScreen.h"
#include "src/output/screens/wifi/CityNameListScreen.h"

//-----------------------------------------
// Chart screens
#include "src/output/screens/chart/ChartScreenNextDays.h"
#include "src/output/screens/chart/ChartScreenNext12Hours.h"
#include "src/output/screens/chart/ChartScreenToday.h"

#include "src/output/screens/SleepScreen.h"

#include "src/output/items/ScreenPointItem.h"

#define X_1_SCREENS 6
#define X_SCREENS 3
#define MINUTES_15 900000
#define SECOND_10 10000
#define SECOND 1000

// Collector define
#define TODAY 0
#define NEXT_12_HOURS 1

void showmem(const String& msg){
    Serial.println("Memory " + msg + ": " + String(ESP.getFreeHeap()));
}

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
uint64_t lastCollectorCheck = 0;
int64_t wifiUpdateTimeCheck = -SECOND_10;

int8_t savedWiFiIdx = 0;

TouchScreen ts(&tft, calData);

WeatherDataCollector* collector = new WeatherDataCollector(X_1_SCREENS);

bool is_asleep = false;
SleepScreen* sleep_screen = new SleepScreen(&tft, TFT_BLACK);

ChartScreens** chart_screens = new ChartScreens* [X_1_SCREENS]{
    new ChartScreenToday(&tft, BACKGROUND_COLOR),
    new ChartScreenNext12Hours(&tft, BACKGROUND_COLOR),
    new ChartScreenNextDays(&tft, BACKGROUND_COLOR),
    new ChartScreenNextDays(&tft, BACKGROUND_COLOR),
    new ChartScreenNextDays(&tft, BACKGROUND_COLOR),
    new ChartScreenNextDays(&tft, BACKGROUND_COLOR)
};

MainScreen** screens = new MainScreen*[X_SCREENS]{
    new CurrentWeatherScreen(&tft, BACKGROUND_COLOR),  // [0][0]
    new Forecast12Screen(&tft, BACKGROUND_COLOR),       // [1][0]
    new FewDaysForecastScreen(&tft, BACKGROUND_COLOR)
};

CityNameInputScreen* city_input = new CityNameInputScreen(&tft, BACKGROUND_COLOR, &wclient, &ts);
CityNameListScreen*  city_list  = new CityNameListScreen(&tft, BACKGROUND_COLOR, &wclient, &ts);
ScreenPointItem sci(&tft, 160, 230, BACKGROUND_COLOR, SIZE_POINT);

void refresh();

WiFiScreen** wifi_screens = new WiFiScreen* [2]{
    new wifi::WiFiListScreen (&tft, &ts, BACKGROUND_COLOR, refresh),
    new PasswordInputScreen(&tft, BACKGROUND_COLOR)
};

Point screen_idx(0,0);
uint8_t wifi_screen_idx = 0;

uint8_t idx = 0;
uint8_t for_idx = 0;

void draw_weather_screens(){
    // It wont hurt to call both methods on the same screen object
    screens[screen_idx.x]->draw(weather, true);
    screens[screen_idx.x]->draw(forecast, true);
    sci.draw(X_SCREENS, 2, screen_idx.x+1, screen_idx.y+1);
}

void draw_chart_screens(uint8_t collector_idx){
    chart_screens[screen_idx.x]->draw(collector->get_data(collector_idx), collector->get_min_max(collector_idx), true);
    sci.draw(X_1_SCREENS, 2, screen_idx.x+1, screen_idx.y+1);
}

void get_esp_info(){
    if (millis() - lastTimeCheck < SECOND){
        return;
    }
    wclient.current_weather(weather);
    wclient.forecast_weather(forecast);

    // adding 1 second to ESP time
    screens[0]->refresh(false);

    // Try to regain wifi connection, if lost
    if (WiFi.status() != WL_CONNECTED){
        reconnect_to_wifi();
    }

    // Collector
    if (millis() - lastCollectorCheck > MIN_5){
        collect_data();
        lastCollectorCheck = millis();
    }

    lastTimeCheck = millis();
}

void wakeup(){
    tft.fillScreen(BACKGROUND_COLOR);
    screen_idx.x = 0;
    screen_idx.y = 0;
    draw_weather_screens();
    is_asleep = false;
    sleep_screen->reset();
}

void sleep(){
    tft.fillScreen(TFT_BLACK);
    is_asleep = true;

    while(is_asleep){
        sleep_screen->draw();
        ts.read();
        get_esp_info();
    }
}

void collect_data()
{
        showmem("collector");
    collector->collect(weather, TODAY);
    collector->collect(forecast, NEXT_12_HOURS);
    uint8_t day_idx = 2, day_offset = 0;
    while (day_idx < X_1_SCREENS) {
        collector->collect_all(forecast, day_idx,  day_offset);
        day_idx++; 
        day_offset++;
    }
    showmem("collector after");
}

void reset_tft(){
    tft.fillScreen(BACKGROUND_COLOR);
    tft.setCursor(0,0);
    tft.setTextColor(TFT_GREEN);
    tft.setTextSize(1);
}

void reconnect_to_wifi(){
    if (millis() - wifiUpdateTimeCheck > SECOND_10){
        WiFi.disconnect();
        WiFi.reconnect();
        wifiUpdateTimeCheck = millis();
    }
}

void refresh(){
    wifi_screens[0]->clear_buttons();
    wifi_screens[0]->scan();
    wifi_screens[0]->draw(true);
}

void left(){
    move(LEFT);
}

void right(){
    move(RIGHT);
}

void up(){
    move(UP);
}

void down(){
    move(DOWN);
}

void move(uint8_t move){
    uint8_t collector_idx = 0;

    tft.fillScreen(BACKGROUND_COLOR);
    if (screen_idx.y == 0){
        switch(move){
            case LEFT:
                screen_idx.x = screen_idx.x > 0 ? screen_idx.x - 1 : X_SCREENS-1;
                draw_weather_screens();
                break;
            case RIGHT:
                screen_idx.x = screen_idx.x < X_SCREENS-1 ? screen_idx.x + 1: 0;
                draw_weather_screens();
                break;
            case UP:
                screen_idx.y = 1;
                draw_chart_screens(screen_idx.x);
                break;
            case DOWN:
                screen_idx.y = 1;
                draw_chart_screens(screen_idx.x);
                break;
            default:
                break;
        }
    }

    else if (screen_idx.y == 1){
        switch(move){
            case UP:
                screen_idx.y = 0;
                screen_idx.x = screen_idx.x < X_SCREENS ? screen_idx.x : 0;
                draw_weather_screens();
                break;
            case DOWN:
                screen_idx.y = 0;
                screen_idx.x = screen_idx.x < X_SCREENS ? screen_idx.x : 0;
                draw_weather_screens();
                break;
            case LEFT:
                screen_idx.x = screen_idx.x > 0 ? screen_idx.x - 1 : X_1_SCREENS-1;
                draw_chart_screens(screen_idx.x);
                break;
            case RIGHT:
                screen_idx.x = screen_idx.x < X_1_SCREENS-1 ? screen_idx.x + 1: 0;
                draw_chart_screens(screen_idx.x);
                break;
        }
    }
}

void wifi_setup(){
    std::unique_ptr<Point> pos(ts.read_touch());

    wifi_screens[wifi_screen_idx]->draw(false);
    if(!pos){
        return;
    }
    
    wifi_screens[wifi_screen_idx]->check(pos.get());
    if (wifi_screens[wifi_screen_idx]->change()){
        wifi_screen_idx = wifi_screen_idx == 0 ? 1 : 0;
        tft.fillScreen(BACKGROUND_COLOR);
        wifi_screens[wifi_screen_idx]->draw(wifi_screens[0]->get_str());
        wifi_screens[wifi_screen_idx]->draw(true);
    }
    showmem("wifi setup");
}

void force_wifi_connection(){
    tft.println("Scanning WiFis...");
    wifi_screens[0]->scan();
    tft.fillScreen(BACKGROUND_COLOR);
    wifi_screens[0]->draw(true);

        showmem("wifi connection");

    while(!wifi_screens[wifi_screen_idx]->load_main()){
        wifi_setup();
    }
    String temp_ssid = wifi_screens[1]->get_str(), temp_pwd = wifi_screens[1]->get_str();
    // Already connected to WiFi without entering password
    if (!wifi_screens[1]->load_main() || (temp_ssid == "" || temp_pwd == "") ){
        return;
    }
    ReadMem read_mem;
    read_mem.writeNewWiFi(temp_ssid, temp_pwd);
}

void
pick_city()
{
    CityNameScreen** screens = new CityNameScreen* [2]{
        city_list,
        city_input
    };
    uint8_t idx = 0;

        showmem("pick city start");
    screens[idx]->draw(true);
    while(!screens[idx]->load_main())
    {
        screens[idx]->draw(false);
        if (WiFi.status() == WL_DISCONNECTED){
            reconnect_to_wifi();
        }

        std::unique_ptr<Point> pos (ts.read_touch());
        if(!pos){
            continue;
        }
            showmem("pick city in setup");

        screens[idx]->check(pos.get());
        if (screens[idx]->change()){
            idx = idx != 0 ? 0 : 1;
            tft.fillScreen(BACKGROUND_COLOR);
            screens[idx]->draw(true);
        }
    }
    delete [] screens;
}

void setup()
{
        showmem("");
    tft.init(); 
    tft.setRotation(3);

    reset_tft();
    wifi_screens[0]->init();

    ts
    .on_left(left)
    ->on_right(right)
    ->on_down(down)
    ->on_up(up)
    ->on_sleep(sleep)
    ->on_wakeup(wakeup);

    force_wifi_connection();
    delete wifi_screens[0];
    delete wifi_screens[1];
    delete [] wifi_screens;
        showmem("deleted wifis");

    tft.fillScreen(BACKGROUND_COLOR);
    city_list->init();
    city_list->set_city_info();

        showmem("set city info");
    pick_city();
    delete city_list;
    delete city_input;
    tft.fillScreen(BACKGROUND_COLOR);
        showmem("deleted cities");

    weather = new Weather;
    forecast = new Forecast;
    forecast->number_of_forecasts = NUMBER_OF_HOURS_TO_FORECAST;
    forecast->forecasted_weather = new Weather* [NUMBER_OF_HOURS_TO_FORECAST];

    for (uint8_t i=0;i<NUMBER_OF_HOURS_TO_FORECAST; i++){
        forecast->forecasted_weather[i] = new Weather;
    }
        showmem("alloc weather");

    reset_tft();
    while (!(wclient.current_weather(weather) && wclient.forecast_weather(forecast))){
        tft.println("Failed to obtain data, try restarting ESP");
        if (WiFi.status() != WL_CONNECTED){
            reconnect_to_wifi();
        }
        delay(3000);
    }
        showmem("init weather screens");
    screens[0]->init(weather);
    collector->init(weather);
        showmem("init weather screens");

    tft.fillScreen(BACKGROUND_COLOR);
    screens[0]->draw(weather, true);
    sci.draw(3,1,1,1);

    collect_data();
        showmem("collect");
}

void loop(){
    ts.read();
    get_esp_info();
    if (screen_idx.y == 0){
        screens[screen_idx.x]->draw(weather,false);
        screens[screen_idx.x]->draw(forecast,false);
    }
}