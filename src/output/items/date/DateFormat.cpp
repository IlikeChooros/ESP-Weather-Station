#include "DateFormat.h"

void 
DateFormat::
init()
{
    this->getUpdate = false;
}

void 
DateFormat::
set_date(struct tm* timeinfo)
{
    this->timeinfo = timeinfo;
}

struct tm 
DateFormat::
get_date()
{
    return *this->timeinfo;
}

void 
DateFormat::
set_update(bool update)
{
    getUpdate = update;
}

bool 
DateFormat::
get_update()
{
    return this->getUpdate;
}

bool 
DateFormat::
add_second()
{
    timeinfo->tm_sec++;
    if (this->getUpdate)
    {
        getUpdate = !getLocalTime(timeinfo);
        return !getUpdate;
    }
    if (timeinfo->tm_sec != 60)
    {
        return false;
    }
    // seconds == 60, so incrementing minute by 1, doing the same for everything else

    timeinfo->tm_sec = 0;
    timeinfo->tm_min++;

    if (timeinfo->tm_min % UPDATE_TIME == 0 && getLocalTime(timeinfo))
    {
        return false;
    }
    // If there was a connection error to the ntp server, continue updating date on its own

    if (timeinfo->tm_min != 60)
    {
        return false;
    }
    timeinfo->tm_min = 0;
    timeinfo->tm_hour++;

    if (timeinfo->tm_hour != 24)
    {
        return false;
    }

    timeinfo->tm_hour = 0;
    timeinfo->tm_mday++;

    timeinfo->tm_wday = (timeinfo->tm_wday+1)%7;

    uint8_t days_in_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (timeinfo->tm_year%400 == 0 || (timeinfo->tm_year%4 == 0 && timeinfo->tm_year%100 != 0))
    {
        days_in_month[1]=29;
    }
    if (timeinfo->tm_mday <= days_in_month[timeinfo->tm_mon])
    {
        return true;
    }

    timeinfo->tm_mon++;
    timeinfo->tm_mday = 1;

    if (timeinfo->tm_mon <= 12)
    {
        return true;
    }

    timeinfo->tm_mon = 0;
    timeinfo->tm_year++;

    return true;
}

String 
DateFormat::
formatDateInfo()
{
    String weekdays[7] = {"Sunday ", "Monday ", "Tuesday ", "Wednesday ", "Thursday ", "Friday ", "Saturday "};
    String months[12] = {"Jan ", "Feb ", "Mar ", "Apr ",
                         "May ", "Jun ", "Jul ", "Aug ",
                         "Sep ", "Oct ", "Nov ", "Dec "};
    String date = "";

    date += weekdays[timeinfo->tm_wday];
    date += "- ";
    date += String(timeinfo->tm_mday);
    date += " ";
    date += String(months[timeinfo->tm_mon]);
    date += String(1900 + timeinfo->tm_year);
    return date;
}

String 
DateFormat::
formatTimeInfo()
{
    String time = "";
    time += String(timeinfo->tm_hour);
    time += ":";
    if (timeinfo->tm_min < 10)
    {
        time += "0";
    }
    time += String(timeinfo->tm_min);
    time += ":";
    if (timeinfo->tm_sec < 10)
    {
        time += "0";
    }
    time += String(timeinfo->tm_sec);
    return time;
}