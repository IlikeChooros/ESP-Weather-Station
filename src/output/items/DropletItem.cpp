#include "DropletItem.h"

void 
DropletItem::
draw(bool forceDraw)
{
    if (!forceDraw && !redraw)
    {
        return;
    }

    Icon* icon = matchIcon();
    icon->draw();
    delete icon;
}

void 
DropletItem::
setWeather(Weather* weather)
{
    redraw = pop != weather->_pop;
    pop = weather->_pop;

    if (pop <= 0.1f)
    {
        idx_icon = NO_RAIN;
    }
    else if (pop <= 0.3f)
    {
        idx_icon = UNLIKELY_RAIN;
    }
    else if (pop <= 0.5f)
    {
        idx_icon = PROBABLY_RAIN;
    }
    else if (pop <= 0.7f)
    {
        idx_icon = LIKELY_RAIN;
    }
    else{
        idx_icon = RAIN;
    }
}

Icon* 
DropletItem::matchIcon()
{
    switch (idx_icon)
    {
        case NO_RAIN:
            return new Droplet_0(_tft, x,y, size, bg_c);
        case UNLIKELY_RAIN:
            return new Droplet_30(_tft,x,y,size,bg_c);
        case PROBABLY_RAIN:
            return new Droplet_50(_tft,x,y,size,bg_c);
        case LIKELY_RAIN:
            return new Droplet_70(_tft,x,y,size,bg_c);
        default:
            return new Droplet_100(_tft,x,y,size,bg_c);
    }
}