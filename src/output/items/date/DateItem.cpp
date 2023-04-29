#include "DateItem.h"

// --------------------------------
// (&tft, 160, 10, 45)
// --------------------------------
DateItem::DateItem(
    TFT_eSPI *tft, 
    int16_t center_x, 
    int16_t y_full_date, 
    int16_t y_hour, 
    int16_t bg_c
): tft(tft), y_full_date(y_full_date),
center_x(center_x), y_hour(y_hour),
bg_c(bg_c), _timezone(3600)
{
    dateFormat = new DateFormat;
    digitsec = new DigitSection *[3]{
        new DigitSection(tft, STARTING_X, y_hour, bg_c, true),
        new DigitSection(tft, STARTING_X+70, y_hour, bg_c, true),
        new DigitSection(tft, STARTING_X+140, y_hour, bg_c, false)
    };
}

void 
DateItem::
init(){
    update = false;
    configTime(_timezone, 0, NTP_SERVER);
    if (!getLocalTime(&timeinfo)){
        timeinfo.tm_hour = 12;
        timeinfo.tm_mday = 7;
        timeinfo.tm_min = 0;
        timeinfo.tm_sec = 0;
        timeinfo.tm_year = 123;
        timeinfo.tm_mon = 0;
        timeinfo.tm_wday = 0;
        update = true;
    }
    dateFormat->init();
    dateFormat->set_update(update);
    dateFormat->set_date(&timeinfo);
    prev_time_info = timeinfo;
}

DateItem*
DateItem::
timezone(uint16_t timezone){
    _timezone = timezone;
    return this;
}

void 
DateItem::
draw(bool forceDraw){

    // Refresh if needed
    dateFormat->set_date(&prev_time_info);

    tft->loadFont(CLOCK);
    digitsec[HOURS]->draw(timeinfo.tm_hour, forceDraw);
    digitsec[MINUTES]->draw(timeinfo.tm_min, forceDraw);
    digitsec[SECONDS]->draw(timeinfo.tm_sec, forceDraw);
    tft->unloadFont();

    if (!forceDraw){
        return;
    }
    // Clearing previous date 
    tft->loadFont(LATIN);
    tft->setTextDatum(TC_DATUM);
    tft->setTextColor(bg_c, bg_c);
    tft->drawString(dateFormat->formatDateInfo(), center_x, y_full_date);
    
    // Drawing new one
    dateFormat->set_date(&timeinfo);

    tft->setTextColor(TFT_WHITE, bg_c);
    tft->drawString(dateFormat->formatDateInfo(), center_x, y_full_date);
    tft->unloadFont();
}

void 
DateItem::
add_second(bool getUpdate){
    prev_time_info = timeinfo;

    if (!getUpdate){
        getUpdate = update;    
    }
    dateFormat->set_update(getUpdate);
    
    if (dateFormat->add_second()){
        timeinfo = dateFormat->get_date();
        update = dateFormat->get_update();
        draw(true);
        return;
    } 
    timeinfo = dateFormat->get_date();
}