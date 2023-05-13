#ifndef INPUT_FIELD_H
#define INPUT_FIELD_H

#include "Arduino.h"
#include "TFT_eSPI.h"
#include "SPI.h"

#include "../../custom_font/fonts.h"

#define INPUT_FIELD_BG 0x1904

class InputField
{
    TFT_eSPI* tft;
    String input;
    String to_print;

    int16_t x;
    int16_t y;
    int16_t width;
    int16_t height;

    int16_t _start_cursor;
    int16_t _end_cursor;


    bool _prev_state;
    int16_t _cursor_x;    
    uint64_t _cache_time;
    uint64_t _last_check;
    
    void
    blink(bool);

    public:
    InputField(
        TFT_eSPI* tft,
        int16_t x, 
        int16_t y, 
        int16_t width, 
        int16_t height
    );

    void
    draw(bool forceDraw);

    /**
     * @brief Will concatanate given input
     * 
     * @param input 
     */
    void 
    add_input(
        String input
    );

    /// @brief Deletes 1 character from input
    void 
    del();

    /**
     * @brief Get the input
     * 
     * @return String 
     */
    const String& 
    get_input();

    

    /// @brief Does the blinking effect on cursor
    void
    blink();
};

#endif