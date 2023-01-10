#ifndef DATE_ITEM_H
#define DATE_ITEM_H

#include "TFT_eSPI.h"
#include "SPI.h"
#include "Arduino.h"

#include "DateFormat.h"
#include "DigitSection.h"

#define HOURS 0
#define MINUTES 1
#define SECONDS 2
#define STARTING_X 60

class DateItem
{
    struct tm timeinfo;
    struct tm prev_time_info;

    DateFormat* dateFormat;

    DigitSection** digitsec;

    TFT_eSPI* tft;

    int16_t center_x;
    int16_t y_full_date;
    int16_t y_hour;
    int16_t bg_c;
public:
    DateItem(TFT_eSPI *tft, int16_t center_x, int16_t y_full_date, int16_t y_hour, int16_t bg_c);
    void init();
    void draw(bool forceDraw);
    void add_second();
};


#endif