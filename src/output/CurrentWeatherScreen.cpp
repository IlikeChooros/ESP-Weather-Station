#include "CurrentWeatherScreen.h"


CurrentWeatherScreen::CurrentWeatherScreen(TFT_eSPI * tft, uint16_t bg_c)
{
    this->_tft = tft;
    this->_bg_c = bg_c;

    set_text_colors();

    weather_items = new WeatherItem*[NUMBER_OF_WEATHER_ITEMS] {
        new WeatherIcon(tft,185,30, 125, bg_c),
        new WindIcon(tft, 5, 105, 20, bg_c),
        new TextTemp(tft, 30, 30, 4, 2, TFT_WHITE, "%d `C" , bg_c),
        new TextFeelsLike(tft, 35, 80, 2, 1, TFT_WHITE,"Feels like: %d `C", bg_c),
        new TextWind(tft, 30, 105, 4, 1, 0x77F2, "%d km/h", bg_c),
        new TextPressure(tft, 30, 130, 4, 1, 0xB41F, "%d hPa", bg_c)
    };
}

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

