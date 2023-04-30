#include "TextItem.h"

uint16_t* temp_colors = set_text_colors();

TextItem::
TextItem(
    TFT_eSPI *_tft, 
    uint16_t x, 
    uint16_t y, 
    String font,
    uint16_t color,
    const char* format, 
    uint16_t background_color
): WeatherItem(_tft,x,y,background_color),
font(font), format(format), color(color), text_width(0) {}

void TextItem::draw(bool forceDraw){
    if (!(forceDraw || redraw)){
        return;
    }
    
    char buffer[40];
    _tft->setTextColor(bg_c, bg_c);
    _tft->loadFont(font);
    _tft->fillRect(x, y, text_width, _tft->fontHeight(), bg_c);

    sprintf(buffer, format, this->_data);
    _tft->setTextColor(color, bg_c);
    text_width = _tft->drawString(buffer, x, y);
    _tft->unloadFont();
}

void TextTemp::draw(bool force){
    if (!(force || redraw)){
        return;
    }
    
    char buffer[40];
    _tft->setTextColor(bg_c, bg_c);
    _tft->loadFont(font);
    _tft->fillRect(x - text_width/2 - 2, y, text_width + 4, _tft->fontHeight(), bg_c);

    sprintf(buffer, format, _data);
    _tft->setTextColor(color, bg_c);
    text_width = _tft->drawCentreString(buffer, x, y, 2);
    _tft->unloadFont();
}

void TextFeelsLike::draw(bool force){
    if (!(force || redraw)){
        return;
    }
    
    char buffer[40];
    _tft->setTextColor(bg_c, bg_c);
    _tft->loadFont(font);
    _tft->fillRect(x - text_width/2 - 2, y, text_width + 4, _tft->fontHeight(), bg_c);

    sprintf(buffer, format, _data);
    _tft->setTextColor(color, bg_c);
    text_width = _tft->drawCentreString(buffer, x, y, 2);
    _tft->unloadFont();
}

void TextTemp::setWeather(Weather* weather){
    this->redraw = (int16_t)weather->_temp != this->_data;
    _data = (int16_t)weather->_temp;
    this->color = get_text_color((int16_t) weather->_temp, temp_colors);
}

void TextPressure::setWeather(Weather* weather){
    this->redraw = (int16_t)weather->_pressure != this->_data;
    _data = (int16_t)weather->_pressure;
}

void TextWind::setWeather(Weather* weather){
    this->redraw = (int16_t) (weather->_wind_speed*3.6f) != this->_data;
    _data = (int16_t) ((float) (weather->_wind_speed*3.6f));
}

void TextFeelsLike::setWeather(Weather* weather){
    this->redraw = (int16_t)weather->_feels_like != this->_data;
    _data = (int16_t)weather->_feels_like;
    this->color = get_text_color((int16_t) weather->_feels_like, temp_colors);
}

void TextPop::setWeather(Weather* weather){
    this->redraw = (int16_t)(100 * weather->_pop) != this->_data;
    _data = (int16_t)(100 * weather->_pop);
}