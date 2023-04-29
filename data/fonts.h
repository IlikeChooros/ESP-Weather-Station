#pragma once
/*
Include your custom fonts here.

If you want to create your own font then:
1. Follow instructions in: TFT_eSPI/Tools/Create_Smooth_Font/Create_font, but
you can skip whole SPIFFS part
2. Take created vlw file and convert it to bytes with: https://tomeko.net/online_tools/file_to_hex.php?lang=en
3. Create header file (.h) in /font folder with a table in it:

const uint8_t YOUR_FONT_TABLE[] PROGMEM = {

}

4. Copy bytes to this table
5. Include below your font

#ifndef YOUR_FONT
    #define YOUR_FONT
    include "font/YOUR_FONT.h"
#endif

Thats it! Now you can use your font with:
TFT_eSPI tft = TFT_eSPI();

tft.loadFont(YOUR_FONT_TABLE) // !!! important to use YOUR_FONT_TABLE

*/

#ifndef LATIN
    #define LATIN
    #define LATIN_HEIGHT 28
    #include "font/Arial28.h"
#endif

#ifndef CLOCK
    #define CLOCK
    #define CLOCK_HEIGHT 36
    #include "font/Arial36.h"
#endif

