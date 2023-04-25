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
    for (uint8_t i=0; i<count;){
        saved_ssid = EEPROM.readString(address);
        address += MAX_SSID_LENGHT;
        saved_psw = EEPROM.readString(address);
        address += MAX_PASSWORD_LENGHT;
        // Find first 'count' non-empty networks
        if (saved_ssid.isEmpty() || saved_psw.isEmpty()){
            continue;
        }
        i++;
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
    String city;
    for (uint8_t i=0; i<number_of_saved_city_names; address += CITY_NAME_LEN){
        uint8_t idx = EEPROM.read(address);
        address += 1;
        city = EEPROM.readString(address);
        if (city.isEmpty()){
            continue;
        }
        location.push_back({city, idx});
        i++;
    }
    EEPROM.end();

    return location;
}

void
ReadMem::deleteString(uint16_t idx){
    if(!idx){
        return;
    }
    EEPROM.begin(EEPROM_SIZE);
    EEPROM.writeString(idx, String());
    EEPROM.end();
}

int16_t
ReadMem::getAddress(String& find){
    EEPROM.begin(EEPROM_SIZE);

    int16_t address = 11;
    uint8_t number_of_cities = EEPROM.read(CITY_NAME_IDX),
            number_of_wifis  = EEPROM.read(10);
    
    String psw, ssid;
    for (uint8_t i = 0; i < number_of_wifis;){
        ssid = EEPROM.readString(address);
        // Not classified network
        if (ssid.isEmpty()){
            address += MAX_SSID_LENGHT + MAX_PASSWORD_LENGHT;
            continue;
        }
        address += MAX_SSID_LENGHT;
        if (ssid == find){
            EEPROM.end();
            return address;
        }
        psw  = EEPROM.readString(address);
        address += MAX_PASSWORD_LENGHT;
        if (psw == find){
            EEPROM.end();
            return address;
        }
        i++;
    }
    String city;
    address = CITY_NAME_IDX + 1;
    for (uint8_t i = 0; i < number_of_cities; ++i, address += CITY_NAME_IDX + 1){
        city = EEPROM.readString(address);
        if (city == find){
            EEPROM.end();
            return address;
        }
    }
    EEPROM.end();
    return 0;
}

bool
ReadMem::writeNewWiFi(String ssid, String psw){
    if (ssid.length() >= MAX_SSID_LENGHT || psw.length() >= MAX_PASSWORD_LENGHT){
        return false;
    }

    EEPROM.begin(EEPROM_SIZE);
    
    uint8_t number_of_wifis = EEPROM.read(10);
    uint16_t address = 11;
    String temp;
    // Look for deleted networks and maybe update this network's pass
    for (uint8_t i = 0; i < number_of_wifis;){
        temp = EEPROM.readString(address);
        // Update already saved network
        if (temp == ssid){
            address += MAX_SSID_LENGHT;
            EEPROM.writeString(address, psw);
            EEPROM.commit();
            EEPROM.end();
            return true;
        }
        // Look for deleted networks
        if (!temp.isEmpty()){
            address += MAX_PASSWORD_LENGHT + MAX_SSID_LENGHT;
            i++;
            continue;
        }
        EEPROM.writeString(address, ssid);
        address += MAX_SSID_LENGHT;
        EEPROM.writeString(address, psw);
        EEPROM.write(10, number_of_wifis + 1);
        EEPROM.commit();
        EEPROM.end();
        return true;
    }
    // Add new network
    if (number_of_wifis >= MAX_SAVED_NETWORKS){
        EEPROM.end();
        return false;
    }
    address = 11 + number_of_wifis*(MAX_PASSWORD_LENGHT + MAX_SSID_LENGHT);
    EEPROM.writeString(address, ssid);
    address += MAX_SSID_LENGHT;
    EEPROM.writeString(address, psw);
    EEPROM.write(10, number_of_wifis + 1);
    EEPROM.commit();
    EEPROM.end();
    return true;
}

void
ReadMem::deleteWifi(String ssid){
    uint16_t address = getAddress(ssid);
    if (!address){
        return;
    }
    deleteString(address);
    EEPROM.begin(EEPROM_SIZE);
    EEPROM.write(10, EEPROM.read(10) - 1);
    EEPROM.commit();
    EEPROM.end();
}

bool
ReadMem::overwriteCity(String city, uint8_t city_idx, int8_t idx){
    if (city.length() >= CITY_NAME_LEN){
        return false;
    }
    EEPROM.begin(EEPROM_SIZE);
    uint16_t address = CITY_NAME_IDX + 1 + idx * (CITY_NAME_LEN + 1);
    EEPROM.write(address, city_idx);
    EEPROM.writeString(address + 1, city);
    EEPROM.commit();
    EEPROM.end();
    return true;
}

bool
ReadMem::writeNewCity(String city, uint8_t city_idx){
    if (city.length() >= CITY_NAME_LEN){
        return false;
    }
    EEPROM.begin(EEPROM_SIZE);
    uint16_t address = CITY_NAME_IDX + 1;
    uint8_t number_of_cities = EEPROM.read(CITY_NAME_IDX);
    if (number_of_cities >= MAX_CITIES){
        EEPROM.end();
        return false;
    }
    EEPROM.write(CITY_NAME_IDX, number_of_cities+1);
    address += number_of_cities*(CITY_NAME_LEN+1);
    EEPROM.write(address, city_idx);
    EEPROM.writeString(address+1, city);
    EEPROM.commit();
    EEPROM.end();
    return true;
}

void
ReadMem::resetWifis(){
    EEPROM.begin(EEPROM_SIZE);
    EEPROM.write(10, 0);
    EEPROM.commit();
    EEPROM.end();
}

void
ReadMem::resetCities(){
    EEPROM.begin(EEPROM_SIZE);
    EEPROM.write(CITY_NAME_IDX, 0);
    EEPROM.commit();
    EEPROM.end();
}