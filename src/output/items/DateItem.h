#ifndef DATE_ITEM_H
#define DATE_ITEM_H

#include "TFT_eSPI.h"
#include "SPI.h"
#include "Arduino.h"

#include "DateFormat.h"


class DateItem
{
    struct tm timeinfo;
    struct tm prev_time_info;

    DateFormat* dateFormat;

    TFT_eSPI* tft;

    int16_t center_x;
    int16_t y_full_date;
    int16_t y_hour;
    int16_t bg_c;
public:
    DateItem(TFT_eSPI *tft, int16_t center_x, int16_t y_full_date, int16_t y_hour, int16_t bg_c);
    void init();
    void draw();
    void add_second();
};


#endif