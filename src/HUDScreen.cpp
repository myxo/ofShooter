#include "HUDScreen.h"
#include "world.h"
#include "ofMain.h"

#include "stdio.h"

HUDScreen::HUDScreen(const World& world_) : world(world_) {}

void HUDScreen::display(){
    // ofPushMatrix();
    // ofTranslate(world.window_start_x, world.window_start_y);

    display_life(world.player.get());

    for (auto mob : world.mob_array){
        if (!mob->is_dead()){
            display_life(mob.get());
        }
    }

    // ofPopMatrix();
}

void HUDScreen::display_life(movingEntity *object){
    int life = object->life;
    int max_life = object->MAX_LIFE;

    int BAR_SIZE_X = 30; // in px
    int BAR_SIZE_Y = 6;
    int life_size_in_bar = BAR_SIZE_X * ((double)life / max_life);

    ofVec2f obj_center = object->get_center_screen();
    int radius = object->radius;

    int bar_left_up_x = obj_center.x - radius - 10; 
    int bar_left_up_y = obj_center.y - radius - 10;

    ofSetColor(0, 0, 125);
    ofDrawRectangle(bar_left_up_x, bar_left_up_y, BAR_SIZE_X, BAR_SIZE_Y); 

    ofSetColor(255, 0, 0);
    ofDrawRectangle(bar_left_up_x, bar_left_up_y, life_size_in_bar, BAR_SIZE_Y);
}