#include "GeoLocScreen.h"

extern bool waitForGeoLoc = true;
extern uint8_t total_geo_size;
extern uint8_t geo_pos;

static uint8_t current_pos = 255;
static bool picked = false;

void
exit_geo_pick(void){
    waitForGeoLoc = false;
    picked = false;
}

void
finish_geo_setup(void){
    waitForGeoLoc = false;
    picked = true;
}

GeoLocScreen::
~GeoLocScreen(){
    delete exit_button;
    delete enter_button;
    delete geoitem;
    delete sci;
}

GeoLocScreen::
GeoLocScreen(
    TFT_eSPI *tft,
    WeatherClient* wclient,
    TouchScreen* ts
): tft(tft), ts(ts), img(tft){
    enter_button = new CustomButton(tft, 5, 5, 30, 30, 0x3CE6);
    enter_button
    ->set_draw(drawTickButton)
    ->set_on_press(finish_geo_setup);

    exit_button = new CustomButton(tft, 285, 5, 30, 30, TFT_RED);
    exit_button
    ->set_draw(drawExitButton)
    ->set_on_press(exit_geo_pick);

    img.loadFont(NOTE_FONT16);
    uint16_t len = img.textWidth("Choose desired location");
    img.createSprite(len, img.fontHeight());
    img.fillSprite(BACKGROUND_COLOR);
    img.drawString("Choose desired location", 0, 0);
    img.unloadFont();
    img_x = 160 - len/2;

    geoitem = new GeoLocItem(
        tft, wclient, 160, 80, BACKGROUND_COLOR
    );

    sci = new ScreenPointItem(tft, 160, 200, BACKGROUND_COLOR, 15);
}

void GeoLocScreen::
check(void)
{
    std::unique_ptr<Point> pos(ts->read_touch());

    if (!pos){
        return;
    }
    if(exit_button->check(pos->x, pos->y)){
        return;
    }
    if(enter_button->check(pos->x, pos->y)){
        return;
    }

    // GeoItem screen check
    uint16_t x = pos->x, y = pos->y;
    if (y < 80){
        return;
    }
    Move move;
    if (x < 160){
        move = Move::LEFT;
    }
    else{
        move = Move::RIGHT;
    }
    geoitem->change(move);
    sci->draw(total_geo_size, 1, geo_pos+1, 1);
    geoitem->draw(true);
}

void GeoLocScreen::
draw(bool forceDraw){
    if (!forceDraw){
        return;
    }
    exit_button->draw(true);
    enter_button->draw(true);
    drawLeftArrow(tft, 32, 170, 80, 60, BACKGROUND_COLOR);
    drawRightArrow(tft, 212, 170, 80, 60, BACKGROUND_COLOR);
    img.pushSprite(img_x, 10);
    geoitem->draw(true);
    sci->draw(total_geo_size, 1, geo_pos+1, 1);
}

void GeoLocScreen::
set_location(const String& location){
    waitForGeoLoc = true;
    picked = false;
    geo_pos = 0;
    current_pos = 255;

    geoitem->set_loctation(location);
}

bool GeoLocScreen::
is_picked(void){
    return picked;
}