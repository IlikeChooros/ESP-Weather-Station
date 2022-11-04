#ifndef HSV_TO_RGB_H
#define HSV_TO_RGB_H

class HSV
{
    public:
    float hue;
    float satrutaion;
    float value;
};

inline uint32_t to_rgb(uint8_t r, uint8_t g, uint8_t b)
{
    uint32_t RGB;
    r = (r>>3);
    g = (g>>2);
    b = (b>>3);

    RGB = RGB | (r<<11);
    RGB = RGB | (g<<5);
    RGB = RGB | (b);

    return RGB;
}

inline uint32_t HSV_RGB(HSV color)
{
    float s = color.satrutaion/100;
    float v = color.value/100;

    float C = s*v;
    float X = C * ( 1 - abs(fmod(color.hue/60,2) - 1));
    float m = v - C; 

    float r,g,b;

    if (color.hue < 60)
    {
        r = C, g=X, b=0;
    }
    else if (color.hue<120)
    {
        r=X, g=C, b=0;
    }    
    else if (color.hue<180)
    {
        r=0, g=C, b=X;
    }    
    else if (color.hue<240)
    {
        r=0, g=X, b=C;
    }    
    else if (color.hue<300)
    {
        r=X, g=0, b=C;
    }    
    else
    {
        r=C, g=0, b=X;
    }

    return to_rgb(
        (r+m)*255,
        (g+m)*255,
        (b+m)*255
    );
}


#endif