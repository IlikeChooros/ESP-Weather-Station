#include "CurrentWeatherScreen.h"


CurrentWeatherScreen::CurrentWeatherScreen(TFT_eSPI * tft, uint16_t bg_c)
{
    this->_tft = tft;
    this->_bg_c = bg_c;

    // Temp range from 40+ to 30- (C)
    text_colors = new uint16_t [TEMP_RANGE];

    HSV* hsv = new HSV;

    hsv->hue = 0;
    hsv->satrutaion = 43;
    hsv->value = 100;

    float itr = (float)250/TEMP_RANGE;

    for (int8_t t = TEMP_RANGE-1;t>=0; t--)
    {
        text_colors[t] = HSV_RGB(*hsv);
        hsv->hue += itr;
    }

    delete hsv;

    weather_items = new WeatherItem*[NUMBER_OF_WEATHER_ITEMS] {
        new WeatherIcon(tft,185,30, 125, bg_c),
        new WindIcon(tft,0,180, 20, bg_c)
    };
}

void CurrentWeatherScreen::draw(Weather* weather)
{
    configTime(3600, 0, NTP_SERVER);

    // wind_icon->setWeather(weather);
    // wind_icon->draw();

    // weahter_icon->setWeather(weather);
    // weahter_icon->draw();
    
    for (uint8_t i = 0; i<NUMBER_OF_WEATHER_ITEMS;i++)
    {
        weather_items[i]
        ->setWeather(weather);
        weather_items[i]
        ->draw();
    }

    // Fonts: 1,2,4,6,7,8

    _tft->setCursor(0,0);
    _tft->setTextFont(4);
    _tft->setTextSize(1);

    _tft->setTextColor(text_colors[convert_to_idx((int16_t)weather->_temp)]);

    _tft->println("");

    _tft->setTextSize(2);
    _tft->println(" "+String((uint16_t)round(weather->_temp)) +" "+String(DEGREE)+"C"); // TEMP

    _tft->setTextFont(2);
    _tft->setTextSize(1);

    _tft->setTextColor(text_colors[convert_to_idx((int16_t)weather->_feels_like)]); // FEELS LIKE
    _tft->println("   Feels like: "+String((uint16_t)round(weather->_feels_like))+ " "+String(DEGREE)+"C");


    _tft->setTextColor(0x77F2);  
    _tft->println("   "+String((uint16_t)round(weather->_wind_speed*3.6f))+" km/h"); // WIND SPEED

    _tft->setTextColor(0xB41F); 
    _tft->println("   "+String(weather->_pressure)+" hPa"); // PRESSURE

    _tft->setTextFont(4);
    _tft->setTextSize(1);
    _tft->setTextColor(MIST);

    _tft->setCursor(60,180);
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        _tft->print("ERROR");
    }
    else{
        _tft->println(&timeinfo, "%H:%M %d-%m-%Y");
    }

}

int16_t CurrentWeatherScreen::convert_to_idx(int16_t t)
{
    int16_t temp = t + 30;
    temp = temp > TEMP_RANGE ? TEMP_RANGE : temp;
    temp = temp < 0 ? 0: temp;
    return temp;
}