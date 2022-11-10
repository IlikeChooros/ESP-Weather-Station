#include "CurrentWeatherScreen.h"

void CurrentWeatherScreen::draw(Weather* weather, bool forceDraw)
{
    configTime(3600, 0, NTP_SERVER);
    
    for (uint8_t i = 0; i<NUMBER_OF_WEATHER_ITEMS;i++)
    {
        weather_items[i]
        ->setWeather(weather);
        weather_items[i]
        ->draw(forceDraw);
    }

    // Fonts: 1,2,4,6,7,8

    // _tft->setCursor(0,0);
    // _tft->setTextFont(4);
    // _tft->setTextSize(1);

    // _tft->setTextColor(text_colors[convert_to_idx((int16_t)weather->_temp)]);

    // _tft->println("");

    // _tft->setTextSize(2);
    // _tft->println(" "+String((int16_t)round(weather->_temp)) +" "+String(DEGREE)+"C"); // TEMP

    // _tft->setTextFont(2);
    // _tft->setTextSize(1);

    // _tft->setTextColor(text_colors[convert_to_idx((int16_t)weather->_feels_like)]); // FEELS LIKE
    // _tft->println("   Feels like: "+String((int16_t)round(weather->_feels_like))+ " "+String(DEGREE)+"C");


    // _tft->setTextColor(0x77F2);  
    // _tft->println("   "+String((int16_t)round(weather->_wind_speed*3.6f))+" km/h"); // WIND SPEED

    // _tft->setTextColor(0xB41F); 
    // _tft->println("   "+String(weather->_pressure)+" hPa"); // PRESSURE

    _tft->setTextFont(2);
    _tft->setTextSize(2);
    _tft->setTextColor(MIST);

    _tft->setCursor(50,180);
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        _tft->print("ERROR");
    }
    else{
        _tft->println(&timeinfo, "%H:%M %d-%m-%Y");
    }

}

