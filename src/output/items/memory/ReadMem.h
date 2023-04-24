#pragma once

#include "EEPROM.h"
#include <list>
#include <Arduino.h>

#ifndef EEPROM_SIZE
#define EEPROM_SIZE 512
#endif

#define MAX_PASSWORD_LENGHT 31
#define MAX_SSID_LENGHT 26 

#define MAX_CITIES 2
#define CITY_NAME_LEN 22
#define CITY_NAME_IDX EEPROM_SIZE-CITY_NAME_LEN*MAX_CITIES-MAX_CITIES

#define MAX_SAVED_NETWORKS uint8_t((CITY_NAME_IDX - 10)/(MAX_PASSWORD_LENGHT + MAX_SSID_LENGHT))

/// @brief Class to read EEPROM memory, saves as much as possible write transactions, allows memory fragmentation.
class ReadMem
{
private:
    std::list<std::pair<String, String>> wifi;
    std::list<std::pair<String, uint8_t>> location;
public:
    ReadMem() = default;

    std::list<std::pair<String, String>>&
    wifis(bool forceRead);

    std::list<std::pair<String, uint8_t>>&
    cities(bool forceRead);

    void
    deleteString(uint16_t idx);

    int16_t 
    getAddress(String&);

    bool
    writeNewWiFi(String ssid, String psw);

    void
    deleteWifi(String ssid);

    bool
    overwriteCity(String city, uint8_t city_idx, int8_t idx);

    bool
    writeNewCity(String city, uint8_t city_idx);

    void
    resetWifis();

    void
    resetCities();
};
