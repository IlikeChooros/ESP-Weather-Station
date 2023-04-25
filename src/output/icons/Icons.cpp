#include "Icons.h"

void Sun::draw()
{
    tft->fillRect(x,y,size,size,background_color);
    drawSun(tft, x + 0.05f*size, y, size*0.9f, SUNNY, background_color);
}

void Moon::draw()
{
    tft->fillRect(x,y,size,size,background_color);
    drawMoon(tft,x+0.05f*size,y,size*0.9f, MOON, background_color, 2);
}

void FewCloudsDay::draw()
{
    tft->fillRect(x,y,size,size,background_color);

    drawSun(tft, x + 0.05f*size, y, size*0.9f, SUNNY, background_color);
    drawCloud(tft, x+0.2f*size, y + 0.63f*size, 0.6f*size, MIST, CLOUDY, background_color);
}

void FewCloudsNight::draw()
{
    tft->fillRect(x,y,size,size,background_color);

    drawMoon(tft, x + 0.1f*size, y, size*0.8f, MOON, background_color, 3);
    drawCloud(tft, x+0.15f*size, y + 0.63f*size, 0.6f*size, MIST, CLOUDY, background_color);
}

void CloudsDay::draw()
{
    tft->fillRect(x,y,size,size,background_color);

    drawSun(tft, x + 0.38f*size, y, size*0.6f, SUNNY, background_color);
    drawCloud(tft,x,y+0.1f*size, 0.4f*size, CLOUDY, LIGHT_DARK_CLOUDS, background_color);
    drawCloud(tft, x, y + 0.28f*size, 0.9f*size, MIST, CLOUDY, background_color);
}

void CloudsNight::draw()
{
    tft->fillRect(x,y,size,size,background_color);

    drawMoon(tft, x + 0.5f*size, y, size*0.4f, MOON, background_color, 2);
    drawCloud(tft,x,y+0.1f*size, 0.4f*size, CLOUDY, LIGHT_DARK_CLOUDS, background_color);
    drawCloud(tft, x, y + 0.28f*size, 0.9f*size, MIST, CLOUDY, background_color);
}

void ManyClouds::draw()
{
    tft->fillRect(x,y,size,size,background_color);

    //on right
    drawCloud(tft,x+0.3f*size,y+0.1f*size, 0.7f*size, LIGHT_DARK_CLOUDS, MIDDLE_DARK_CLOUDS,background_color);

    //on left
    drawCloud(tft, x,y+0.2f*size, 0.6f*size, CLOUDY, LIGHT_DARK_CLOUDS,background_color);

    //bottom
    drawCloud(tft, x, y+0.25f*size, 0.9f*size, MIST, CLOUDY,background_color);
}

void Storm::draw()
{
    tft->fillRect(x,y,size,size,background_color);
    //Cloud drawing
    drawCloud(tft, x, y, size, ALMOST_DARK_CLOUDS, DARK_CLOUDS,background_color);

    // lightning drawing

    uint16_t ax = x+0.5f*size,
            ay = y + 0.2f*size,
            bx = ax - 0.05f*size,
            by = ay + 0.2f*size;
    tft->drawWideLine(ax, ay, bx, by, 0.05f*size, SUNNY, background_color);

    ax = bx;
    ay = by;

    ax += 0.1f*size;
    by +=0.2f*size;
    bx += 0.05f*size;

    tft->drawWideLine(ax, ay, bx, by, 0.03f*size, SUNNY, background_color);

    ax -= 0.02f*size;
    bx = ax;
    by = ay;
    ax -= 0.08f*size;
    
    tft->drawWideLine(ax, ay, bx, by, 0.045f*size, SUNNY, SUNNY);
}


void Rain::draw()
{
    tft->fillRect(x,y,size,size,background_color);
    //Cloud drawing

    drawCloud(tft, x, y, size, CLOUDY,LIGHT_DARK_CLOUDS ,background_color);

    uint16_t ax = x + 0.3f*size,
            ay = y+0.45f*size,
            bx = ax - 0.07f*size,
            by = ay + 0.08f*size;

    for (uint8_t a = 0;a<3;a++)
    {
        draw_droplet(ax,ay,bx,by, 0.03f*size);
        ax += 0.2f*size;
        bx += 0.2f*size;
    }


    ay += 0.11f*size;
    ax = x+ 0.3f*size;
    bx = ax - 0.07f*size,
    by = ay + 0.08f*size;
    for (uint8_t a = 0;a<3;a++)
    {
        draw_droplet(ax,ay,bx,by, 0.03f*size);
        ax += 0.2f*size;
        bx += 0.2f*size;
    }
}

void Rain::draw_droplet(uint16_t ax, uint16_t ay,uint16_t bx, uint16_t by ,uint16_t size)
{
    tft->drawWideLine(ax,ay,bx,by,size, WATER, background_color);
}

void BigRain::draw()
{
    tft->fillRect(x,y,size,size,background_color);
    //Cloud drawing

    drawCloud(tft, x, y, size, LIGHT_DARK_CLOUDS,MIDDLE_DARK_CLOUDS ,background_color);

    uint16_t ax = x + 0.3f*size,
            ay = y+0.45f*size,
            bx = ax - 0.15f*size,
            by = ay + 0.25f*size;

    for (uint8_t a = 0;a<3;a++)
    {
        tft->drawWideLine(ax,ay,bx,by,0.03f*size, WATER, background_color);
        ax += 0.2f*size;
        bx += 0.2f*size;
    }
}

void Snow::draw()
{
    tft->fillRect(x,y,size,size,background_color);

    drawCloud(tft, x,y, size, CLOUDY, LIGHT_DARK_CLOUDS, background_color);

    drawSnowflake(tft, x + 0.3f*size, y+0.4f*size, size*0.4f, background_color, SNOW_FLAKE, WATER);
    //drawSnowflake(tft, x+0.1f*size, y, size*0.8f, CLOUDY, SNOW_FLAKE, WATER);
}

void MistNight::draw()
{
    tft->fillRect(x,y,size,size,background_color);

    drawMoon(tft, x + 0.3f*size, y, size*0.65f, MOON, background_color, 2);
    drawMist(tft, x+0.1f*size, y+ 0.1f*size, size*0.9f,MIST, background_color);
}

void MistDay::draw()
{
    tft->fillRect(x,y,size,size,background_color);

    drawSun(tft, x + 0.2f*size, y, size*0.65f, SUNNY, background_color);
    drawMist(tft, x+0.1f*size, y+ 0.1f*size, size*0.9f,MIST, background_color);
}

void Wind::draw()
{
    tft->fillRect(x,y,size*1.3f,size*1.3f,background_color);

    drawSingleWindString(tft,x,y,size, 0.6f*size, 0.05f*size, TFT_WHITE, background_color, false);  
    drawSingleWindString(tft,x+0.1f*size, y+ 0.25f*size, 0.9f*size, 0.7f*size, 0.08f*size, TFT_WHITE, background_color, true);  
}

void WeakWind::draw()
{
    tft->fillRect(x,y,size*1.3f,size*1.3f,background_color);

    drawSingleWindString(tft,x,y,size, 0.5f*size, 0.08f*size, TFT_WHITE, background_color, false);  
    drawSingleWindString(tft,x+0.1f*size, y+ 0.35f*size, 0.6f*size, 0.36f*size, 0.08f*size, TFT_WHITE, background_color, true); 
}

void StrongWind::draw()
{
    tft->fillRect(x,y,size*1.3f,size*1.3f,background_color);

    drawSingleWindString(tft,x,y,size, 0.5f*size, 0.08f*size, TFT_WHITE, background_color, false);  
    drawSingleWindString(tft,x+0.2f*size, y+ 0.25f*size, 0.9f*size, 0.7*size, 0.08f*size, TFT_WHITE, background_color, true); 
    drawSingleWindString(tft,x+0.1f*size, y+ 0.60f*size, 0.6f*size, 0.36f*size, 0.08f*size, TFT_WHITE, background_color, true); 
}

void Droplet_0::draw()
{
    drawDroplet(tft,x,y,size,SNOW_FLAKE);
    drawDroplet(tft,x+0.18f*size, y + 0.25f*size, 0.7f*size, background_color);
}

void Droplet_30::draw()
{
    drawDroplet(tft,x,y,size,SNOW_FLAKE);
    drawDroplet(tft,x+0.18f*size, y + 0.25f*size, 0.7f*size, background_color);
    tft->fillRect(x+0.3f*size, y+0.85f*size, 0.4f*size, 0.05f*size, SNOW_FLAKE);
    tft->fillRect(x+0.35f*size, y + 0.9f*size, 0.3f*size, 0.05f*size, SNOW_FLAKE);

}

void Droplet_50::draw()
{
    drawDroplet(tft,x,y,size,SNOW_FLAKE);
    drawDroplet(tft,x+0.18f*size, y + 0.22f*size, 0.7f*size, background_color);
    tft->fillRect(x+0.25f*size, y+0.65f*size, 0.5f*size, 0.2f*size, SNOW_FLAKE);
    tft->fillRect(x+0.3f*size, y+0.85f*size, 0.4f*size, 0.05f*size, SNOW_FLAKE);
    tft->fillRect(x+0.35f*size, y + 0.9f*size, 0.3f*size, 0.05f*size, SNOW_FLAKE);
}

void Droplet_70::draw()
{
    drawDroplet(tft,x,y,size,SNOW_FLAKE);
    drawDroplet(tft,x+0.18f*size, y + 0.2f*size, 0.7f*size, background_color);
    tft->fillCircle(x+size/2, y + size*0.7f, size*0.3f, SNOW_FLAKE);
}

void Droplet_100::draw()
{
    drawDroplet(tft,x,y,size,SNOW_FLAKE);
}

void WiFiIconStrong::draw()
{
    tft->fillRect(x,y,1.05f*size,size, background_color);
    tft->drawLine(x+size, y, x+size, y+0.55f*size, background_color);
    tft->fillCircle(x+size, y+size*0.7f, 0.1f*size, background_color);

    drawWifi(tft,x,y,size, 2, background_color);
}

void WiFiIconMedium::draw()
{
    tft->fillRect(x,y,1.05f*size,size, background_color);
    tft->drawLine(x+size, y, x+size, y+0.55f*size, background_color);
    tft->fillCircle(x+size, y+size*0.7f, 0.1f*size, background_color);

    drawWifi(tft,x,y,size, 1, background_color);
}

void WiFiIconWeak::draw()
{
    tft->fillRect(x,y,1.05f*size,size, background_color);
    tft->drawLine(x+size, y, x+size, y+0.55f*size, background_color);
    tft->fillCircle(x+size, y+size*0.7f, 0.1f*size, background_color);

    drawWifi(tft,x,y,size, 0, background_color);
}

void WiFiIconLost::draw()
{
    tft->fillRect(x,y,1.05f*size,size, background_color);
    tft->drawLine(x+size, y, x+size, y+0.55f*size, background_color);
    tft->fillCircle(x+size, y+size*0.7f, 0.1f*size, background_color);

    drawWifi(tft,x,y,size, 3, background_color);
    tft->drawLine(x+size, y, x+size, y+0.55f*size, TFT_RED);
    tft->fillCircle(x+size, y+size*0.7f, 0.1f*size, TFT_RED);
}

void LockerOpened::draw()
{
    drawLockOpened(tft,x,y,size, TFT_GREEN,background_color);
}

void LockerLocked::draw()
{
    drawLockLocked(tft,x,y,size, TFT_RED,background_color);
}

void WiFiStrenghtStrong::draw()
{
    tft->fillRect(x,y,size*0.8f,size,background_color);

    tft->fillRect(x,y, size*0.2f, size, TFT_GREEN);
    tft->fillRect(x+0.3f*size,y, size*0.2f, size, TFT_GREEN);
    tft->fillRect(x+0.6f*size,y, size*0.2f, size, TFT_GREEN);
}

void WiFiStrenghtMedium::draw()
{
    tft->fillRect(x,y,size*0.5f,size,background_color);

    tft->fillRect(x,y, size*0.2f, size, TFT_ORANGE);
    tft->fillRect(x+0.3f*size,y, size*0.2f, size, TFT_ORANGE);
}

void WiFiStrenghtWeak::draw()
{
    tft->fillRect(x,y,size*0.2f,size,background_color);

    tft->fillRect(x,y, size*0.2f, size, TFT_RED);
}