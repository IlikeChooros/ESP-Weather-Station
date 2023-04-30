#pragma once

#include <TFT_eSPI.h> 
#include "../../custom_font/fonts.h"

/**
 * @brief Fuction drawing refresh button
 * 
 * @param tft 
 * @param x 
 * @param y 
 * @param size
 * @param color 
 */
void
drawRefreshButton(
    TFT_eSPI* tft,
    uint16_t x,
    uint16_t y,
    uint16_t size,
    uint16_t color 
);

void
drawTickButton(
    TFT_eSPI* tft,
    uint16_t x, 
    uint16_t y, 
    uint16_t size, 
    uint16_t color
);

void
drawSetLocationButton(
    TFT_eSPI* tft,
    uint16_t x,
    uint16_t y,
    uint16_t size,
    uint16_t color 
);

void
drawRightArrow(
    TFT_eSPI* tft,
    uint16_t x,
    uint16_t y,
    uint16_t w,
    uint16_t h,
    uint16_t color 
);

void
drawLeftArrow(
    TFT_eSPI* tft,
    uint16_t x,
    uint16_t y,
    uint16_t w,
    uint16_t h,
    uint16_t color 
);

void
drawExitButton(
    TFT_eSPI* tft,
    uint16_t x,
    uint16_t y,
    uint16_t size,
    uint16_t color
);

void
drawSettingsButton(
    TFT_eSPI* tft,
    uint16_t x,
    uint16_t y,
    uint16_t size,
    uint16_t color 
);

void
drawScrollUpButton(
    TFT_eSPI* tft,
    uint16_t x,
    uint16_t y,
    uint16_t w,
    uint16_t h,
    uint16_t color 
);

void
drawScrollDownButton(
    TFT_eSPI* tft,
    uint16_t x,
    uint16_t y,
    uint16_t w,
    uint16_t h,
    uint16_t color 
);


void
drawDetailsButton(
    TFT_eSPI* tft,
    uint16_t x,
    uint16_t y,
    uint16_t size,
    uint16_t color 
);

void
drawEraseButton(
    TFT_eSPI* tft,
    uint16_t x,
    uint16_t y,
    uint16_t size,
    uint16_t color 
);
