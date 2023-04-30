#pragma once
/*
Include your custom fonts here.


If you want to create your own font then:
Follow strictly instructions in: TFT_eSPI/Tools/Create_Smooth_Font/Create_font
*/

#ifndef LATIN
    #define LATIN "BasicLatin28"
    #define LATIN_HEIGHT 26
#endif

#ifndef EXTENDED_LATIN
    #define EXTENDED_LATIN "ExtendedLatin28"
    #define EXTENDED_HEIGHT 26
#endif

#ifndef EXTENDED_LATIN_SMALL
    #define EXTENDED_LATIN_SMALL "ExtendedLatin12"
#endif

#ifndef NOTE_FONT
    #define NOTE_FONT
    #define NOTE_FONT12 "Arial12"
    #define NOTE_FONT16 "Arial16"
    #define NOTE_HEIGHT 10
#endif

#ifndef WEATHER_FONT
    #define WEATHER_FONT "Weather16"
    #define WEATHER_HEIGHT 14
#endif    

#ifndef TEMP_FONT
    #define TEMP_FONT "Temp42"
#endif

#ifndef CLOCK_FONT
    #define CLOCK_FONT "Clock48"
#endif

#ifndef DATE_FONT
    #define DATE_FONT "Date28"
#endif
