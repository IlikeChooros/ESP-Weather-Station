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
    dateFormat = new DateFormat;

    digitsec = new DigitSection *[3]
    {
        new DigitSection(tft, STARTING_X, y_hour, 1, 6, bg_c, true),
        new DigitSection(tft, STARTING_X+70, y_hour, 1, 6, bg_c, true),
        new DigitSection(tft, STARTING_X+140, y_hour, 1, 6, bg_c, false)
    };
}

void DateItem::init()
{
    Serial.println("date item init");
    bool update = false;
    configTime(3600, 0, NTP_SERVER);
    if (!getLocalTime(&timeinfo))
    {
        Serial.println("! get local time");
        timeinfo.tm_hour = 12;
        timeinfo.tm_mday = 7;
        timeinfo.tm_min = 0;
        timeinfo.tm_sec = 0;
        timeinfo.tm_year = 123;
        timeinfo.tm_mon = 0;
        timeinfo.tm_wday = 0;
        update = true;
    }
    Serial.println("after if");
    dateFormat->init();
    Serial.println("after date format init");
    dateFormat->set_update(update);
    Serial.println("st_update");
    dateFormat->set_date(&timeinfo);
    Serial.println("set_date");
    prev_time_info = timeinfo;

}

//---------------------------------------------
// Function expects to be called every 1 second
//---------------------------------------------
void DateItem::draw(bool forceDraw)
{
    // Clearing previous date 
    dateFormat->set_date(&prev_time_info);

    digitsec[HOURS]->draw(timeinfo.tm_hour, forceDraw);
    digitsec[MINUTES]->draw(timeinfo.tm_min, forceDraw);
    digitsec[SECONDS]->draw(timeinfo.tm_sec, forceDraw);

    tft->setTextSize(1);
    tft->setTextColor(bg_c);
    if (forceDraw)
    {
        tft->drawCentreString(dateFormat->formatDateInfo(), center_x, y_full_date, 4);
    }
    
    
    // Drawing new one
    dateFormat->set_date(&timeinfo);

    if (forceDraw)
    {
        tft->setTextColor(TFT_WHITE);
        tft->drawCentreString(dateFormat->formatDateInfo(), center_x, y_full_date, 4);
    }
}

//********************************
// Adds 1 second to its time info,
// To work correctly should be called
// every second
//********************************
void DateItem::add_second(bool getUpdate)
{
    prev_time_info = timeinfo;

    if (getUpdate)
    {
        dateFormat->set_update(true);
    }

    if (dateFormat->add_second())
    {
        timeinfo = dateFormat->get_date();
        draw(true);
        return;
    } 
    timeinfo = dateFormat->get_date();
}