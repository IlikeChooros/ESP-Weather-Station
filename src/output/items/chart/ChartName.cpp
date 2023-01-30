#include "ChartName.h"

void
ChartName::
draw()
{
    tft->fillRect(x,y+1, CHART_NAME_WIDTH, CHART_NAME_HEIGHT, color);
    tft->setCursor(x+CHART_NAME_WIDTH + 3, y);
    tft->setTextColor(color);
    tft->setTextSize(1);
    tft->setTextFont(1);
    tft->print(str);
}