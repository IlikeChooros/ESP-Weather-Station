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

    /// @brief Reads from EEPROM saved networks 
    /// @param forceRead should it read forcefully
    /// @return first - ssid, second - pass
    std::list<std::pair<String, String>>&
    wifis(bool forceRead);

    /// @brief Read from EEPROM saved cities
    /// @param forceRead should it read forcefully
    /// @return first - city, second - city index
    std::list<std::pair<String, uint8_t>>&
    cities(bool forceRead);

    void
    deleteString(uint16_t idx);

    /// @brief Finds given string in EEPROM via linear search.
    /// @param  String - to find
    /// @return A integer number, if it is 0 - then no such string matched
    int16_t 
    getAddress(String&);

    /// @brief Adds to EEPROM given network's data
    /// @param ssid  network's SSID
    /// @param psw  valid password
    /// @return true - added new network, false - couldn't add new network
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
