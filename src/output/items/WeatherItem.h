#ifndef WEATHER_ITEM_H
#define WEATHER_ITEM_H

#include <Arduino.h>
#include <TFT_eSPI.h> 
#include <SPI.h>
#include "../../weather_client/Weather.h"


class WeatherItem
{
    public:

    explicit
    WeatherItem(TFT_eSPI *_tft, uint16_t x, uint16_t y, uint16_t background_color);

    /**
     * @brief Draws object on the TFT Screen
     * 
     * @param forceDraw Boolean value to forcefully 
     *                  draw this object
     */
    virtual void
    draw(bool forceDraw) = 0;

    
    /**
     * @brief Set the Weather data to this object
     * 
     * @param weather Weather pointer object, already initialized
     */
    virtual void
    setWeather(Weather* weather) = 0;

    protected:
    TFT_eSPI *_tft;
    uint16_t x;
    uint16_t y;
    uint8_t size;
    uint16_t bg_c;
};




#endif