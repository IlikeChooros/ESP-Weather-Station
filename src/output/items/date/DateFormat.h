#pragma once

#include "Arduino.h"

#define UPDATE_TIME 15 // in minutes
#define NTP_SERVER "pool.ntp.org"

class DateFormat
{
    struct tm* timeinfo;
    bool getUpdate;
    public:
    void init();
    bool add_second();
    void set_date(struct tm* timeinfo);
    void set_update(bool update);
    struct tm get_date();
    bool get_update();
    String formatDateInfo();
    String formatTimeInfo();
};