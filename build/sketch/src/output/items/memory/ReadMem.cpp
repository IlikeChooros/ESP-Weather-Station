#line 1 "c:\\Users\\pawel\\arduino\\ESP-Weather-Station\\src\\output\\items\\memory\\ReadMem.cpp"
#include "ReadMem.h"

std::list<std::pair<String, String>>&
ReadMem::wifis(bool forceRead){
    if (!(wifi.empty() || forceRead)){
        return wifi;
    }
    EEPROM.begin(EEPROM_SIZE);
    uint8_t count = EEPROM.read(10);
    uint16_t address = 11;
    String saved_ssid, saved_psw;

    wifi.clear();
    for (uint8_t i=0; i<count; i++){
        saved_ssid = EEPROM.readString(address);
        address += MAX_SSID_LENGHT;
        saved_psw = EEPROM.readString(address);
        address += MAX_PASSWORD_LENGHT;
        wifi.push_back({saved_ssid, saved_psw});
    }
    EEPROM.end();
    return wifi;
}

std::list<std::pair<String, uint8_t>>&
ReadMem::cities(bool forceRead){
    if (!(location.empty() || forceRead)){
        return location;
    }

    EEPROM.begin(EEPROM_SIZE);

    uint8_t number_of_saved_city_names = EEPROM.read(CITY_NAME_IDX);
    number_of_saved_city_names = number_of_saved_city_names < MAX_CITIES ? number_of_saved_city_names : MAX_CITIES;

    location.clear();
    uint16_t address = CITY_NAME_IDX+1;
    for (uint8_t i=0; i<number_of_saved_city_names; i++, address += CITY_NAME_LEN){
        uint8_t idx = EEPROM.read(address);
        address += 1;
        location.push_back({EEPROM.readString(address), idx});
    }
    EEPROM.end();

    return location;
}