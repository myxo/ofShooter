#include "bulletFactory.h"

BulletFactory::BulletFactory(World *world_ptr_) : world_ptr(world_ptr_){
    active_gun = GunState::SHOTGUN;
}

void BulletFactory::change_gun(int num){
    switch(num){
        case 1: active_gun = GunState::PISTOLE; break;
        case 2: active_gun = GunState::SHOTGUN; break;
    }
}

void BulletFactory::create_bullets(ofVec2f mouse_screen){
    switch(active_gun){
        case GunState::PISTOLE : create_pistole_bullets(mouse_screen); break;
        case GunState::SHOTGUN : create_shotgun_bullets(mouse_screen); break;
    }

    // world_ptr->player->gun_time_stamp = chrono::system_clock::now();
}


void BulletFactory::create_pistole_bullets(ofVec2f mouse_screen){
    ofVec2f mouse_box = world_ptr->box2of(world_ptr->transformeScreenToBoxCoorditane(b2Vec2(mouse_screen.x, mouse_screen.y)));
    ofVec2f player_center = world_ptr->player->get_center_box();
    ofVec2f speed_dir(mouse_box.x - player_center.x, mouse_box.y - player_center.y);
    speed_dir.normalize();
    player_center += (speed_dir * 0.5);
    speed_dir *= world_ptr->get_param_double("pistole_bullet_speed"); // TODO remove magic numbers

    world_ptr->bullet_array.push_back(std::make_shared<Pistole>(player_center, speed_dir, world_ptr));
}


void BulletFactory::create_shotgun_bullets(ofVec2f mouse_screen){
    ofVec2f mouse_box = world_ptr->box2of(world_ptr->transformeScreenToBoxCoorditane(b2Vec2(mouse_screen.x, mouse_screen.y)));
    ofVec2f player_center = world_ptr->player->get_center_box();
    ofVec2f speed_dir(mouse_box.x - player_center.x, mouse_box.y - player_center.y);
    speed_dir.normalize();
    player_center += (speed_dir * 0.5);
    speed_dir *= 65.0; // TODO remove magic numbers

    for (float i = -10; i < 10; i += 2){ // TODO do it in the right way
        ofVec2f new_dir = speed_dir.getRotated(i + ofRandom (-1, 1));
        world_ptr->bullet_array.push_back(std::make_shared<Pistole>(player_center, new_dir, world_ptr));
    }
}