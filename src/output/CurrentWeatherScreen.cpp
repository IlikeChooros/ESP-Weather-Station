#include "CurrentWeatherScreen.h"


CurrentWeatherScreen::CurrentWeatherScreen(TFT_eSPI * tft)
{
    this->_tft = tft;

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
}

void CurrentWeatherScreen::draw_main_screen(Weather* weather, uint16_t bg_c)
{
    _tft->fillScreen(bg_c);
    configTime(0, 3600, NTP_SERVER);
    Icon* icon = iconMatcher(weather->_icon, _tft, 185,30, 125, bg_c);
    icon->draw();

    // Fonts: 1,2,4,6,7,8

    _tft->setCursor(0,0);
    _tft->setTextFont(4);
    _tft->setTextSize(1);

    _tft->setTextColor(text_colors[convert_to_idx((int16_t)weather->_temp)]);

    _tft->println("");

    _tft->setTextSize(2);
    _tft->println(String(weather->_temp) + " C"); // TEMP
    _tft->setTextFont(2);
    _tft->setTextSize(1);

    _tft->setTextColor(text_colors[convert_to_idx((int16_t)weather->_feels_like)]); // FEELS LIKE
    _tft->println("  Feels like: "+String(weather->_feels_like)+ " C");

    _tft->setTextColor(0x77F2);  
    _tft->println("  "+String(weather->_wind_speed*3.6f)+" km/h"); // WIND SPEED

    _tft->setTextColor(0xB41F); 
    _tft->println("  "+String(weather->_pressure)+" hPa"); // PRESSURE

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


void CurrentWeatherScreen::draw_desc(Weather* weather, uint16_t bg_c)
{
    _tft->fillScreen(bg_c);
    _tft->setCursor(0,40);
    _tft->setTextFont(2);
    _tft->setTextSize(2);
    

    _tft->setTextColor(text_colors[convert_to_idx((int16_t) weather->_temp)]);
    _tft->println("   TEMP: "+String(weather->_temp) + " C");

    _tft->setTextColor(text_colors[convert_to_idx((int16_t)weather->_feels_like)]);
    _tft->println("   FEELS LIKE: "+String(weather->_feels_like)+ " C");

    _tft->setTextColor(MIST);
    _tft->println("   PRESSURE: "+String(weather->_pressure)+" hPa");

    _tft->setTextColor(0x85FF);
    _tft->println("   HUMIDITY: "+String(weather->_humidity)+" %");

    _tft->setTextColor(0x77F2);
    _tft->println("   WIND: "+String(weather->_wind_speed * 3.6f)+" km/h");
}

int16_t CurrentWeatherScreen::convert_to_idx(int16_t t)
{
    int16_t temp = t + 30;
    temp = temp > TEMP_RANGE ? TEMP_RANGE : temp;
    temp = temp < 0 ? 0: temp;
    return temp;
}