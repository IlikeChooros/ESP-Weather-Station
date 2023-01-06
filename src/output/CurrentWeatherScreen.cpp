#include "CurrentWeatherScreen.h"

void CurrentWeatherScreen::draw(Weather* weather, bool forceDraw)
{
    configTime(3600, 0, NTP_SERVER);
    
    Serial.println("Starting iterations...");
    for (uint8_t i = 0; i<NUMBER_OF_WEATHER_ITEMS;i++)
    {
        Serial.println(String(i));
        weather_items[i]
        ->setWeather(weather);
        weather_items[i]
        ->draw(forceDraw);
    }

    // Fonts: 1,2,4,6,7,8

    Serial.println("refresh()");
    refresh();
}

void CurrentWeatherScreen::refresh()
{
    _tft->fillRect(0,0,320,96,bg_c);
    
    this->wifi->draw();

    _tft->setTextSize(1);
    _tft->setTextColor(TFT_WHITE);

    
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        _tft->print("ERROR");
    }
    else{
        _tft->drawCentreString(formatTimeInfo(&timeinfo), 160,10,4);
        _tft->setTextFont(6);
        _tft->setCursor(100,45);
        _tft->print(&timeinfo, "%H:%M");
    }

    Serial.println("[+] Succesfully drew screen");
}

String CurrentWeatherScreen::formatTimeInfo(struct tm* timeinfo)
{
    String weekdays [7] = {"Sunday ","Monday ", "Tuesday ", "Wednesday ", "Thursday ", "Friday ", "Saturday "};
    String months [12] = {"Jan ", "Feb ", "Mar ", "Apr ", 
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

