#ifndef DATE_ITEM_H
#define DATE_ITEM_H

#include "TFT_eSPI.h"
#include "SPI.h"
#include "Arduino.h"

#include "DateFormat.h"
#include "../digits/DigitSection.h"

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
    uint16_t _timezone;
public:
    DateItem(
        TFT_eSPI *tft, 
        int16_t center_x, 
        int16_t y_full_date, 
        int16_t y_hour, 
        int16_t bg_c
    );

    void 
    init();

    /**
     * @brief Draws date format: Weekday - Month Year  Hours:Minutes:Seconds  ("%A - %b %Y", "%H:%M:%S")
     * 
     * @param forceDraw 
     */
    void 
    draw(bool forceDraw);

    /**
     * @brief Adds 1 second to struct tm, to work properly should be called every second
     * 
     * @param getUpdate 
     */
    void 
    add_second(bool getUpdate);

    /// @brief Set custom timezone, by default 3600 (1 hour)
    /// @param timezone 
    /// @return this pointer
    DateItem*
    timezone(uint16_t timezone);
};


#endif