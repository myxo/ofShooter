#include "HUDDebug.h"
#include "mob.h"

#include <algorithm>

HUDDebug::HUDDebug(const World& world_) : world(world_){}

void HUDDebug::display(){
    // left corner
    ofDrawBitmapString(ofToString(ofGetFrameRate(), 1), 50, 50); // TODO load font and change size

    // right corner
    int text_offset = ofGetWidth() - 150;
    ofVec2f player_center = world.player->get_center();
    auto player_position = "(" + ofToString(player_center.x,1) + " ," + ofToString(player_center.y,1) + ")";
    ofDrawBitmapString(player_position, text_offset, 50);

    int live_mob_count = std::count_if(world.mob_array.begin(), world.mob_array.end(), 
        [](auto mob){ return mob->state != MobState::DEAD; });
    ofDrawBitmapString("Mob count: " + ofToString(live_mob_count), text_offset, 70);
    ofDrawBitmapString("Bullet count: " + ofToString(world.bullet_array.size()), text_offset, 90);
}