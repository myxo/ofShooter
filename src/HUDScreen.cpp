#include "HUDScreen.h"
#include "world.h"
#include "ofMain.h"
#include "bulletFactory.h"

#include "stdio.h"

HUDScreen::HUDScreen(const World& world_) : world(world_) {
    gun_message_font.load("verdana.ttf", 25, true, true);
    gun_message_font.setLineHeight(34.0f);
    gun_message_font.setLetterSpacing(1.035);

}

void HUDScreen::display(){
    // ofPushMatrix();
    // ofTranslate(world.window_start_x, world.window_start_y);

    display_life(world.player.get());

    for (auto mob : world.mob_array){
        if (!mob->is_dead()){
            display_life(mob.get());
        }
    }
    display_gun_refactoring_time();

    ofSetColor(0,0,0);
    if (world.bullet_factory->active_gun == GunState::PISTOLE){
        gun_message_font.drawString("PISTOLE", 200, 50);
    } else if (world.bullet_factory->active_gun == GunState::SHOTGUN){
        gun_message_font.drawString("SHOTGUN", 200, 50);
    } 

    // ofPopMatrix();
}

void HUDScreen::display_gun_refactoring_time(){
    double ratio = world.bullet_factory->get_gun_refactoring_ratio();
    if (ratio == 1.0){
        return;
    }

    int BAR_SIZE_X = 30; // in px
    int BAR_SIZE_Y = 6;

    ofVec2f obj_center = world.player->get_center_screen();
    int radius = world.player->radius;

    int bar_left_up_x = obj_center.x - radius - 10; 
    int bar_left_up_y = obj_center.y - radius - 20;

    ofSetColor(50, 50, 50);
    ofDrawRectangle(bar_left_up_x, bar_left_up_y, BAR_SIZE_X, BAR_SIZE_Y); 

    ofSetColor(180, 180, 180);
    ofDrawRectangle(bar_left_up_x, bar_left_up_y, (int)(BAR_SIZE_X * ratio), BAR_SIZE_Y);
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
    int bar_left_up_y = obj_center.y - radius - 30;

    ofSetColor(0, 0, 125);
    ofDrawRectangle(bar_left_up_x, bar_left_up_y, BAR_SIZE_X, BAR_SIZE_Y); 

    ofSetColor(255, 0, 0);
    ofDrawRectangle(bar_left_up_x, bar_left_up_y, life_size_in_bar, BAR_SIZE_Y);
}