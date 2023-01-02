#include "TimeItem.h"


void TimeItem::draw(bool forceDraw)
{
    if (!redraw && !forceDraw)
    {
        return;
    }

    String date = unixTimeToHumanReadable(hourly);
    this->_tft->setCursor(this->x, this->y);
    this->_tft->setTextColor(this->bg_c);
    this->_tft->setTextFont(this->font);
    this->_tft->setTextSize(this->text_size);
    this->_tft->print(prev_date);

    this->_tft->setTextColor(color);
    this->_tft->setCursor(x,y);
    this->_tft->print(date);
    prev_date = date;
}

void TimeItem::setWeather(Weather* weather)
{
    redraw = unix != weather->_dt;
    this->unix = weather->_dt;
}

String TimeItem::unixTimeToHumanReadable(bool hourFormat)
{
    // Save the time in Human
    // readable format
    String ans = "";
 
    // Number of days in month
    // in normal year
    int daysOfMonth[] = { 31, 28, 31, 30, 31, 30,
                          31, 31, 30, 31, 30, 31 };
 
    long int currYear, daysTillNow, extraTime, extraDays,
        index, date, month, hours, minutes,
        flag = 0;
 
    // Calculate total days unix time T
    daysTillNow = unix / (24 * 60 * 60);
    extraTime = unix % (24 * 60 * 60);
    currYear = 1970;
 
    // Calculating current year
    while (true) {
        if (currYear % 400 == 0
            || (currYear % 4 == 0 && currYear % 100 != 0)) {
            if (daysTillNow < 366) {
                break;
            }
            daysTillNow -= 366;
        }
        else {
            if (daysTillNow < 365) {
                break;
            }
            daysTillNow -= 365;
        }
        currYear += 1;
    }
    // Updating extradays because it
    // will give days till previous day
    // and we have include current day
    extraDays = daysTillNow + 1;
 
    if (currYear % 400 == 0
        || (currYear % 4 == 0 && currYear % 100 != 0))
        flag = 1;
 
    // Calculating MONTH and DATE
    month = 0, index = 0;
    if (flag == 1) {
        while (true) {
 
            if (index == 1) {
                if (extraDays - 29 < 0)
                    break;
                month += 1;
                extraDays -= 29;
            }
            else {
                if (extraDays - daysOfMonth[index] < 0) {
                    break;
                }
                month += 1;
                extraDays -= daysOfMonth[index];
            }
            index += 1;
        }
    }
    else {
        while (true) {
 
            if (extraDays - daysOfMonth[index] < 0) {
                break;
            }
            month += 1;
            extraDays -= daysOfMonth[index];
            index += 1;
        }
    }
 
    // Current Month
    if (extraDays > 0) {
        month += 1;
        date = extraDays;
    }
    else {
        if (month == 2 && flag == 1)
            date = 29;
        else {
            date = daysOfMonth[month - 1];
        }
    }
 
    // Calculating HH:MM:YYYY
    hours = extraTime / 3600;
    minutes = (extraTime % 3600) / 60;    
    
    if (hourFormat)
    {
        ans += String(hours);
        ans += ":";
        if (minutes<10)
        {
            ans+= "0";
        }
        ans += String(minutes);
    }
    else
    {
        ans += String(date);
        ans += "-";
        ans += String(month);
    }
    
 
    // Return the time
    return ans;
}