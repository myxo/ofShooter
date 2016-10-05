#include "HUDDebug.h"
#include "mob.h"

#include <algorithm>

HUDDebug::HUDDebug(const World& world_) : world(world_){}

void HUDDebug::display(){
    // left corner
    ofSetColor(255, 255, 255);
    ofDrawRectangle(25, 25, 100, 100);
    ofSetColor(255, 0, 0);
    ofDrawBitmapString(ofToString(ofGetFrameRate(), 1), 50, 50); // TODO load font and change size

    // right corner
    int text_offset = ofGetWidth() - 150;
    
    ofSetColor(255, 255, 255);
    ofDrawRectangle(text_offset - 10, 25, text_offset + 100, 100);
    ofSetColor(255, 0, 0);

    ofVec2f player_center_box = world.player->get_center_box();
    ofVec2f player_center_screen = world.player->get_center_screen();
    auto player_position = "(" + ofToString(player_center_box.x,1) + " ," + ofToString(player_center_box.y,1) + ")";
    ofDrawBitmapString(player_position, text_offset, 50);
    auto player_position_pixel = "(" + ofToString(player_center_screen.x,1) + " ," + ofToString(player_center_screen.y,1) + ")";
    ofDrawBitmapString(player_position_pixel, text_offset, 70);

    int live_mob_count = std::count_if(world.mob_array.begin(), world.mob_array.end(), 
        [](auto mob){ return mob->state != MobState::DEAD; });
    ofDrawBitmapString("Mob count: " + ofToString(live_mob_count), text_offset, 90);
    ofDrawBitmapString("Bullet count: " + ofToString(world.bullet_array.size()), text_offset, 110);

    // ofDrawBitmapString()
}