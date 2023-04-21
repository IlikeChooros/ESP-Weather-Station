# 1 "c:\\Users\\pawel\\arduino\\ESP-Weather-Station\\ESP-Weather-Station.ino"

# 3 "c:\\Users\\pawel\\arduino\\ESP-Weather-Station\\ESP-Weather-Station.ino" 2
# 4 "c:\\Users\\pawel\\arduino\\ESP-Weather-Station\\ESP-Weather-Station.ino" 2
# 5 "c:\\Users\\pawel\\arduino\\ESP-Weather-Station\\ESP-Weather-Station.ino" 2
# 6 "c:\\Users\\pawel\\arduino\\ESP-Weather-Station\\ESP-Weather-Station.ino" 2
# 7 "c:\\Users\\pawel\\arduino\\ESP-Weather-Station\\ESP-Weather-Station.ino" 2

//-----------------------------------------
// Weather screens
# 11 "c:\\Users\\pawel\\arduino\\ESP-Weather-Station\\ESP-Weather-Station.ino" 2
# 12 "c:\\Users\\pawel\\arduino\\ESP-Weather-Station\\ESP-Weather-Station.ino" 2
# 13 "c:\\Users\\pawel\\arduino\\ESP-Weather-Station\\ESP-Weather-Station.ino" 2

//-----------------------------------------
// WiFi setup screens
# 17 "c:\\Users\\pawel\\arduino\\ESP-Weather-Station\\ESP-Weather-Station.ino" 2
# 18 "c:\\Users\\pawel\\arduino\\ESP-Weather-Station\\ESP-Weather-Station.ino" 2
# 19 "c:\\Users\\pawel\\arduino\\ESP-Weather-Station\\ESP-Weather-Station.ino" 2
# 20 "c:\\Users\\pawel\\arduino\\ESP-Weather-Station\\ESP-Weather-Station.ino" 2

//-----------------------------------------
// Chart screens
# 24 "c:\\Users\\pawel\\arduino\\ESP-Weather-Station\\ESP-Weather-Station.ino" 2
# 25 "c:\\Users\\pawel\\arduino\\ESP-Weather-Station\\ESP-Weather-Station.ino" 2
# 26 "c:\\Users\\pawel\\arduino\\ESP-Weather-Station\\ESP-Weather-Station.ino" 2

# 28 "c:\\Users\\pawel\\arduino\\ESP-Weather-Station\\ESP-Weather-Station.ino" 2

# 30 "c:\\Users\\pawel\\arduino\\ESP-Weather-Station\\ESP-Weather-Station.ino" 2
# 41 "c:\\Users\\pawel\\arduino\\ESP-Weather-Station\\ESP-Weather-Station.ino"
// Collector define



TFT_eSPI tft = TFT_eSPI();

uint8_t number_of_tries = 0;

HTTPClient http;
bool get_http;

WeatherClient wclient(&http, 900000);
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
int64_t wifiUpdateTimeCheck = -10000;

int8_t savedWiFiIdx = 0;
int8_t numberOfSavedWifis = 0;
String** saved_wifi_info = 0;

TouchScreen ts(&tft, calData);

WeatherDataCollector* collector = new WeatherDataCollector(6);

bool is_asleep = false;
SleepScreen* sleep_screen = new SleepScreen(&tft, 0x0000 /*   0,   0,   0 */);

ChartScreens** chart_screens = new ChartScreens* [6]{
    new ChartScreenToday(&tft, 0x10C4),
    new ChartScreenNext12Hours(&tft, 0x10C4),
    new ChartScreenNextDays(&tft, 0x10C4),
    new ChartScreenNextDays(&tft, 0x10C4),
    new ChartScreenNextDays(&tft, 0x10C4),
    new ChartScreenNextDays(&tft, 0x10C4)
};


MainScreen** screens = new MainScreen*[3]{
    new CurrentWeatherScreen(&tft, 0x10C4), // [0][0]
    new Forecast12Screen(&tft, 0x10C4), // [1][0]
    new FewDaysForecastScreen(&tft, 0x10C4)
};


CityNameInputScreen* city_input = new CityNameInputScreen(&tft, 0x10C4, &wclient, &ts);

CityNameListScreen* city_list = new CityNameListScreen(&tft, 0x10C4, &wclient, &ts);
ScreenPointItem sci(&tft, 160, 230, 0x10C4);

void refresh();

WiFiScreen** wifi_screens = new WiFiScreen* [2]{
    new WiFiListScreen (&tft, 0x10C4, refresh),
    new PasswordInputScreen(&tft, 0x10C4)
};


Point screen_idx(0,0);
uint8_t wifi_screen_idx = 0;

uint8_t idx = 0;
uint8_t for_idx = 0;

void draw_weather_screens(){
    // It wont hurt to call both methods on the same screen object
    screens[screen_idx.x]->draw(weather, true);
    screens[screen_idx.x]->draw(forecast, true);
    sci.draw(3, 2, screen_idx.x+1, screen_idx.y+1);
}

void draw_chart_screens(uint8_t collector_idx){
    chart_screens[screen_idx.x]->draw(collector->get_data(collector_idx), collector->get_min_max(collector_idx), true);
    sci.draw(6, 2, screen_idx.x+1, screen_idx.y+1);
}

void get_esp_info(){
    if (millis() - lastTimeCheck < 1000){
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
    if (millis() - lastCollectorCheck > 300000){
        collect_data();
        lastCollectorCheck = millis();
    }

    lastTimeCheck = millis();
}

void wakeup(){
    tft.fillScreen(0x10C4);
    screen_idx.x = 0;
    screen_idx.y = 0;
    draw_weather_screens();
    is_asleep = false;
    sleep_screen->reset();
}

void sleep(){
    tft.fillScreen(0x0000 /*   0,   0,   0 */);
    is_asleep = true;

    while(is_asleep){
        sleep_screen->draw();
        ts.read();
        get_esp_info();
    }
}

void collect_data()
{
    collector->collect(weather, 0);
    collector->collect(forecast, 1);
    uint8_t day_idx = 2, day_offset = 0;
    while (day_idx < 6) {
        collector->collect_all(forecast, day_idx, day_offset);
        day_idx++;
        day_offset++;
    }
}

void eeprom_earse(uint16_t starting_address, uint16_t ending_address){

    for (;starting_address<ending_address; starting_address++){
        EEPROM.write(starting_address, 0);
    }
    EEPROM.commit();
}

void reset_tft(){
    tft.fillScreen(0x10C4);
    tft.setCursor(0,0);
    tft.setTextColor(0x07E0 /*   0, 255,   0 */);
    tft.setTextSize(1);
}

void char_to_wifi_info(char* ssid, char* pass, uint8_t idx){
    ssid = new char [saved_wifi_info[idx][0].length()+1];
    pass = new char [saved_wifi_info[idx][1].length()+1];

    saved_wifi_info[idx][0].toCharArray(ssid, saved_wifi_info[idx][0].length()+1);
    saved_wifi_info[idx][1].toCharArray(pass, saved_wifi_info[idx][1].length()+1);
}

void reconnect_to_wifi(){
    if (millis() - wifiUpdateTimeCheck > 10000){
        WiFi.disconnect();
        WiFi.reconnect();
        wifiUpdateTimeCheck = millis();
    }
}

void load_saved_wifis(){
    ReadMem read;
    auto wifis = read.wifis(true);
    numberOfSavedWifis = wifis.size();

    if (numberOfSavedWifis){
        saved_wifi_info = new String* [numberOfSavedWifis];
    }
    uint8_t count = 0;
    for (auto i : wifis){
        saved_wifi_info[count] = new String[2]{
            i.first,
            i.second
        };
        count++;
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

    tft.fillScreen(0x10C4);
    if (screen_idx.y == 0){
        switch(move){
            case LEFT:
                screen_idx.x = screen_idx.x > 0 ? screen_idx.x - 1 : 3 -1;
                draw_weather_screens();
                break;
            case RIGHT:
                screen_idx.x = screen_idx.x < 3 -1 ? screen_idx.x + 1: 0;
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
                screen_idx.x = screen_idx.x < 3 ? screen_idx.x : 0;
                draw_weather_screens();
                break;
            case DOWN:
                screen_idx.y = 0;
                screen_idx.x = screen_idx.x < 3 ? screen_idx.x : 0;
                draw_weather_screens();
                break;
            case LEFT:
                screen_idx.x = screen_idx.x > 0 ? screen_idx.x - 1 : 6 -1;
                draw_chart_screens(screen_idx.x);
                break;
            case RIGHT:
                screen_idx.x = screen_idx.x < 6 -1 ? screen_idx.x + 1: 0;
                draw_chart_screens(screen_idx.x);
                break;
        }
    }
}

void wifi_setup(){
    Point* pos = ts.read_touch();

    wifi_screens[wifi_screen_idx]->draw(false);

    if(pos){
        wifi_screens[wifi_screen_idx]->check(pos);
        if (wifi_screens[wifi_screen_idx]->change()){
            wifi_screen_idx = wifi_screen_idx == 0 ? 1 : 0;
            tft.fillScreen(0x10C4);
            wifi_screens[wifi_screen_idx]->draw(wifi_screens[0]->get_str());
            wifi_screens[wifi_screen_idx]->draw(true);
        }
        delete pos;
    }
}

void force_wifi_connection(){
    tft.println("Scanning WiFis...");

    wifi_screens[0]->scan();

    tft.fillScreen(0x10C4);
    wifi_screens[0]->draw(true);

    while(!wifi_screens[wifi_screen_idx]->load_main()){wifi_setup();}

    String temp_ssid = wifi_screens[1]->get_str(), temp_pwd = wifi_screens[1]->get_str();
    //****************************
    // Already connected to WiFi 
    // without entering password
    if (!wifi_screens[1]->load_main() || (temp_ssid == "" || temp_pwd == "") ){
        return;
    }
    //******************************************
    // Checking if entered wifi ssid
    // is already saved, if so updating password
    EEPROM.begin(512);
    uint16_t address = 11;
    for (uint8_t i=0; i<numberOfSavedWifis; i++)
    {
        if (saved_wifi_info[i][0] == temp_ssid && temp_pwd.length() < 31)
        {
            address += i*(31 + 26)+26;

            if (EEPROM.readString(address).length() > temp_pwd.length()){
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
    address += numberOfSavedWifis*(31 + 26);
    if (address <= 512-31 -26 && temp_ssid.length() < 26 && temp_pwd.length() < 26){
        EEPROM.writeString(address, temp_ssid);

        address += 26;
        EEPROM.writeString(address, temp_pwd);

        address += 31;
        numberOfSavedWifis++;
        EEPROM.write(10, numberOfSavedWifis);
        EEPROM.commit();
    }

    //**************************
    // Updating saved_wifi_info
    //
    if (numberOfSavedWifis-1 == 0){
        EEPROM.end();
        return;
    }

    for (int8_t i = 0; i < numberOfSavedWifis-1; i++){
        delete [] saved_wifi_info[i];
    }
    delete [] saved_wifi_info;

    EEPROM.end();
    load_saved_wifis();
}

void
pick_city()
{
    bool city_idx = 0;

    city_list->draw(true);
    while(!(city_input->load_main() || city_list->load_main()))
    {
        if(city_idx){
            city_input->draw(false);
        }
        else{
            city_list->draw(false);
        }

        if (WiFi.status() == WL_DISCONNECTED){
            reconnect_to_wifi();
        }

        Point* pos = ts.read_touch();
        if(!city_idx){
            city_list->draw(false);
        }
        if(!pos){
            continue;
        }
        // 1
        if(city_idx){
            city_input->check(pos);
            city_idx = !city_input->change(); // if true -> idx = 0, else  idx = 1

            if (city_input->change()){
                tft.fillScreen(0x10C4);
                city_list->draw(true);
            }
        }
        else{ // 0
            city_list->check(pos);
            city_idx = city_list->change(); // if true idx = 1, else idx = 0

            if (city_list->change()){
                tft.fillScreen(0x10C4);
                city_input->draw(true);
            }
        }
        delete pos;
    }
}

void setup()
{
    tft.init();
    tft.setRotation(3);

    reset_tft();
    load_saved_wifis();
    wifi_screens[0]->init();

    ts
    .on_left(left)
    ->on_right(right)
    ->on_down(down)
    ->on_up(up)
    ->on_sleep(sleep)
    ->on_wakeup(wakeup);

    force_wifi_connection();

    tft.fillScreen(0x10C4);
    city_list->init();
    city_list->set_city_info();
    pick_city();
    tft.fillScreen(0x10C4);

    weather = new Weather;
    forecast = new Forecast;
    forecast->number_of_forecasts = 40;
    forecast->forecasted_weather = new Weather* [40];

    for (uint8_t i=0;i<40; i++){
        forecast->forecasted_weather[i] = new Weather;
    }

    reset_tft();
    while (!(wclient.current_weather(weather) && wclient.forecast_weather(forecast))){
        tft.println("Failed to obtain data, try restarting ESP");
        if (WiFi.status() != WL_CONNECTED){
            reconnect_to_wifi();
        }
        delay(3000);
    }

    screens[0]->init(weather);
    collector->init(weather);

    tft.fillScreen(0x10C4);
    screens[0]->draw(weather, true);
    sci.draw(3,1,1,1);

    collect_data();
}


void loop(){
    ts.read();
    get_esp_info();
    if (screen_idx.y == 0){
        screens[screen_idx.x]->draw(weather,false);
        screens[screen_idx.x]->draw(forecast,false);
    }
}
