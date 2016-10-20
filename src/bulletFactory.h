#pragma once

#include "world.h"
#include "pistole.h"
#include "bullet.h"

#include <vector>
#include <chrono>

using namespace std;

enum class GunState{
    PISTOLE,
    SHOTGUN
};

class BulletFactory{
public:
    BulletFactory(World *world_ptr_);
    void change_gun(int num);
    bool fire(ofVec2f mouse_screen);

    // TODO rename
    double get_gun_refactoring_ratio();
    
    GunState active_gun;

private:
    const int MAX_WEAPON_NUMBER = 10;

    World *world_ptr;
    vector<chrono::time_point<chrono::steady_clock> > gun_fire_time_array;
    vector<int> gun_refactoring_time;
    
    size_t active_gun_index;
    void create_bullets(ofVec2f mouse_screen);
    void create_pistole_bullets(ofVec2f mouse_screen);
    void create_shotgun_bullets(ofVec2f mouse_screen);
};