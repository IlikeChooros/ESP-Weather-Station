#pragma once

#include <Arduino.h>
#include <TFT_eSPI.h> 
#include <SPI.h>

void 
drawCloud(
    TFT_eSPI *tft,
    uint16_t x, 
    uint16_t y, 
    uint16_t size, 
    uint16_t color,
    uint16_t fade_color,
    uint16_t background_color,
    uint16_t left_shade,
    uint16_t right_shade,
    uint16_t far_right_shade
);

void 
drawSun(
    TFT_eSPI *tft,
    uint16_t x, 
    uint16_t y, 
    uint16_t size, 
    uint16_t color, 
    uint16_t background_color
);

void  
drawMoon(
    TFT_eSPI *tft,
    uint16_t x, 
    uint16_t y, 
    uint16_t size, 
    uint16_t color, 
    uint16_t background_color,
    uint8_t offset
);


void  
drawSnowflake(
    TFT_eSPI *tft,
    uint16_t x, 
    uint16_t y, 
    uint16_t size, 
    uint16_t filler_circle_color, 
    uint16_t color, 
    uint16_t background_color
);

void  
drawMist (
    TFT_eSPI *tft,
    uint16_t x, 
    uint16_t y, 
    uint16_t size, 
    uint16_t color, 
    uint16_t background_color
);

void  
drawSingleWindString(
    TFT_eSPI *tft,
    uint16_t x, 
    uint16_t y, 
    uint16_t size,
    uint16_t lenght, 
    uint8_t thickness,
    uint16_t color, 
    uint16_t background_color, 
    bool reversed
);

void  
drawDroplet(
    TFT_eSPI *tft,
    uint16_t x, 
    uint16_t y, 
    uint16_t size, 
    uint16_t color
);

void 
drawWifi(
    TFT_eSPI *tft,
    uint16_t x, 
    uint16_t y, 
    uint8_t size, 
    uint8_t strenght, 
    uint16_t background_color
);

void  
drawLockOpened(
    TFT_eSPI *tft, 
    uint16_t x, 
    uint16_t y, 
    uint8_t size, 
    uint16_t color, 
    uint16_t background_color
);

void 
drawLockLocked(
    TFT_eSPI *tft, 
    uint16_t x, 
    uint16_t y, 
    uint8_t size, 
    uint16_t color, 
    uint16_t background_color
); 


void
drawPickIcon(
    TFT_eSPI* tft,
    uint16_t x, 
    uint16_t y, 
    uint8_t size, 
    uint16_t color
);

void
drawSunset(
    TFT_eSPI* tft,
    uint16_t x, 
    uint16_t y, 
    uint8_t size, 
    uint16_t bg_c
);

void
drawSunrise(
    TFT_eSPI* tft,
    uint16_t x, 
    uint16_t y, 
    uint8_t size, 
    uint16_t bg_c
);

