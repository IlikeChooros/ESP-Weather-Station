#include "TextItem.h"


void TextItem::draw()
{
    if(!redraw)
    {
        return;
    }
    
    char buffer[40];
    sprintf(buffer, format, prev_data);

    _tft->setTextColor(this->bg_c);
    _tft->setTextFont(this->font);
    _tft->setTextSize(this->text_size);
    _tft->setCursor(this->x, this->y);
    _tft->print(buffer);

    sprintf(buffer, format, this->_data);
    _tft->setTextColor(this->color);
    _tft->setCursor(this->x, this->y);
    _tft->print(buffer);

    this->prev_data = this->_data;
}

void TextTemp::setWeather(Weather* weather)
{
    this->redraw = (int16_t)weather->_temp != this->_data;
    _data = (int16_t)weather->_temp;
    this->color = temp_text_colors[convert_to_idx((int16_t)weather->_temp)];
}

void TextPressure::setWeather(Weather* weather)
{
    this->redraw = (int16_t)weather->_pressure != this->_data;
    _data = (int16_t)weather->_pressure;
}

void TextWind::setWeather(Weather* weather)
{
    this->redraw = (int16_t)weather->_wind_speed*3.6f != this->_data;
    _data = (int16_t)weather->_wind_speed*3.6f;
}

void TextFeelsLike::setWeather(Weather* weather)
{
    this->redraw = (int16_t)weather->_feels_like != this->_data;
    _data = (int16_t)weather->_feels_like;
    this->color = temp_text_colors[convert_to_idx((int16_t)weather->_feels_like)];
}

