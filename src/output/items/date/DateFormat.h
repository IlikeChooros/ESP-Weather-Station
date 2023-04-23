#pragma once

#include "Arduino.h"

#define UPDATE_TIME 15 // in minutes
#define NTP_SERVER "pool.ntp.org"

class DateFormat
{
    struct tm* timeinfo;
    bool getUpdate;

    public:

    void 
    init();

    /**
     * @brief Adds 1 second to struct tm, should be called every second to work properly
     * 
     * @return true if the digit object should refresh day date
     */
    bool 
    add_second();

    void 
    set_date(struct tm* timeinfo);

    void 
    set_update(bool update);

    struct tm 
    get_date();

    bool 
    get_update();

    String 
    formatDateInfo();

    String 
    formatTimeInfo();
};