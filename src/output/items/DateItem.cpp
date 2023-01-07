#include "DateItem.h"

// --------------------------------
// (&tft, 160, 10, 45)
// --------------------------------
DateItem::DateItem(TFT_eSPI *tft, int16_t center_x, int16_t y_full_date, int16_t y_hour, int16_t bg_c)
{
    this->center_x = center_x;
    this->y_full_date = y_full_date;
    this->y_hour = y_hour;
    this->tft = tft;
    this->bg_c = bg_c;
    configTime(3600, 0, NTP_SERVER);
    dateFormat = new DateFormat;
}

void DateItem::init()
{
    //getLocalTime(&prev_time_info);
    if (!getLocalTime(&timeinfo))
    {
        timeinfo.tm_hour = 12;
        timeinfo.tm_mday = 7;
        timeinfo.tm_min = 0;
        timeinfo.tm_sec = 0;
        timeinfo.tm_year = 123;
        timeinfo.tm_mon = 0;
        timeinfo.tm_wday = 0;
        Serial.println("Failed to obtain time");
    }
    dateFormat->init();
    dateFormat->set_date(&timeinfo);
    prev_time_info = timeinfo;
}

//---------------------------------------------
// Function expects to be called every 1 second
//---------------------------------------------
void DateItem::draw()
{
    // Clearing previous date 
    tft->setTextSize(1);
    tft->setTextColor(bg_c);

    dateFormat->set_date(&prev_time_info);

    tft->drawCentreString(dateFormat->formatDateInfo(), center_x, y_full_date, 4);
    tft->drawCentreString(dateFormat->formatTimeInfo(), center_x, y_hour, 6);

    tft->setTextColor(TFT_WHITE);

    dateFormat->set_date(&timeinfo);
    tft->drawCentreString(dateFormat->formatDateInfo(), center_x, y_full_date, 4);
    tft->drawCentreString(dateFormat->formatTimeInfo(), center_x, y_hour, 6);
}

void DateItem::add_second()
{
    prev_time_info = timeinfo;
    dateFormat->add_second();
    timeinfo = dateFormat->get_date();
}