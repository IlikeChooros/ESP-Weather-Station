#ifndef DATE_FORMAT_H
#define DATE_FORMAT_H

#include "Arduino.h"
#include "TFT_eSPI.h" // for struct tm
#include "SPI.h"

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
    struct tm get_date();
    String formatDateInfo();
    String formatTimeInfo();
};

#endif