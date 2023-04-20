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
};
