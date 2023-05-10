#pragma once
/*
Include your custom fonts here.
All of the fonts used by me are in Arial font.

If you want to create your own font then
follow strictly instructions in: TFT_eSPI/Tools/Create_Smooth_Font/Create_font

Here are unicode block I used:
    0x002C, 0x002F, // Basic Latin letterns only
    0x0041, 0x005A,
    0x0061, 0x007A,

    0x00C0, 0x00D6, // Latin-1 Supplement only letters
    0x00D8, 0x00F6,
    0x00F8, 0x00FF,
    0x0100, 0x017F,

Here are individual unicodes:
    0x002D, 0x0030, 0x0031, 0x0032, 0x0033, 0x0034, // - 0 1 2 3 4
    0x0035, 0x0036, 0x0037, 0x0038, 0x0039,  // 5 6 7 8 9  
    0x00B0,  0x0043, 0x0025, 0x003A, 0x002F, // ° C % : /
    0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0067, 0x0068, 0x0069, 0x006B, 0x006C, // a b c d e g h i k l 
    0x006E, 0x006F, 0x0070, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0079,  // n o p r s t u v y
    0x0041, 0x0045, 0x0046, 0x004A, 0x004D, 0x004E, 0x0050, 0x0053, 0x0054, 0x0057, //A, D, F, J, M, N, P, S, T, W

*/

/*
Displaying keyboard and network SSID's:
It's full Basic Latin
*/
#ifndef LATIN
    #define LATIN "BasicLatin28"
    #define LATIN_HEIGHT 26
#endif

/*
Displaying cities' info:
It's letters only: Basic Latin and Latin-1 Supplement 
*/
#ifndef EXTENDED_LATIN
    #define EXTENDED_LATIN "ExtendedLatin28"
#endif

/*
Displaying cities' info but smaller:
It's letters only: Basic Latin and Latin-1 Supplement 
*/
#ifndef EXTENDED_LATIN_SMALL
    #define EXTENDED_LATIN_SMALL "ExtendedLatin12"
#endif


/*
Displaying small text, used as titles of screens:
It's letters only Basic Latin
*/
#ifndef NOTE_FONT
    #define NOTE_FONT
    #define NOTE_FONT12 "Arial12"
    #define NOTE_FONT16 "Arial16"
#endif

/*
Displaying clock, temperature, pressure and wind speed in CurrentWeatherScreen and FewDays-,12- forecast screens, contains:
a e h i k m l s F P 0 1 2 3 4 5 6 7 8 9 : - ° C / % 
Can display for example:
    Feels like: 12 ° C
    69 %
    113 km/h
    1025 hPa
    17:00
*/
#ifndef WEATHER_FONT
    #define WEATHER_FONT "Weather16"
    #define WEATHER_HEIGHT 16
#endif    

/*
Displaying current temperature in CurrentWeatherScreen, contains:
0 1 2 3 4 5 6 7 8 9 - ° C
*/
#ifndef TEMP_FONT
    #define TEMP_FONT "Temp42"
#endif

/*
Displaying clock in CurrentWeatherScreen, contains:
0 1 2 3 4 5 6 7 8 9 :
*/
#ifndef CLOCK_FONT
    #define CLOCK_FONT "Clock48"
#endif

/* Displaying Date in CurrentWeatherScreen, contains:
0 1 2 3 4 5 6 7 8 9
a b c d e g h i l n o p r s t u v y A D F J M N P S T W 
With those letters you can formulate words: 
    Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Nov, Dec
    Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday
*/ 
#ifndef DATE_FONT
    #define DATE_FONT "Date26"
#endif
