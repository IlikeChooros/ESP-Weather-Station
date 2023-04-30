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
bg_c(bg_c), _timezone(3600), text_width(0),
full_date(tft){
    dateFormat = new DateFormat;
    digitsec = new DigitSection *[3]{
        new DigitSection(tft, STARTING_X, y_hour, bg_c, true),
        new DigitSection(tft, STARTING_X+70, y_hour, bg_c, true),
        new DigitSection(tft, STARTING_X+140, y_hour, bg_c, false)
    };
    full_date.createSprite(320, 28);
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

    full_date.loadFont(DATE_FONT);
    full_date.setTextColor(TFT_WHITE, bg_c);
    full_date.fillSprite(bg_c);
    full_date.drawCentreString(dateFormat->formatDateInfo(), 160, 0, 2);
    text_width = tft->textWidth(dateFormat->formatDateInfo());
    full_date.unloadFont();
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

    tft->loadFont(CLOCK_FONT);
    digitsec[HOURS]->draw(timeinfo.tm_hour, forceDraw);
    digitsec[MINUTES]->draw(timeinfo.tm_min, forceDraw);
    digitsec[SECONDS]->draw(timeinfo.tm_sec, forceDraw);
    tft->unloadFont();

    if (!forceDraw){
        return;
    }

    tft->fillRect(center_x - text_width/2 - 2, y_full_date, text_width + 4, tft->fontHeight(), bg_c);
    full_date.pushSprite(0, y_full_date);
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

        full_date.loadFont(DATE_FONT);
        full_date.setTextColor(TFT_WHITE, bg_c);
        full_date.fillSprite(bg_c);
        full_date.drawCentreString(dateFormat->formatDateInfo(), 160, 0, 2);
        text_width = tft->textWidth(dateFormat->formatDateInfo());
        full_date.unloadFont();

        draw(true);
        return;
    } 
    timeinfo = dateFormat->get_date();
}