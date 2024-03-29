#ifndef SCREEN_H
#define SCREEN_H

#include <TFT_eSPI.h> 

#include "../../../weather_client/Forecast.h"
#include "../../../weather_client/Weather.h"

class MainScreen
{
    public:
    explicit 
    MainScreen(
        TFT_eSPI* tft, 
        uint16_t bg_c
    );

    virtual 
    void 
    draw(
        Weather* weather, 
        bool forceDraw
    ) = 0;

    virtual 
    void 
    draw(
        Forecast* forecast,
         bool forceDraw
    ) = 0;

    virtual 
    void 
    refresh(
        bool forceUpdate
    ) = 0;

    virtual 
    void 
    init(Weather*) = 0;

    protected:
    TFT_eSPI* _tft;
    uint16_t bg_c;
};


#endif