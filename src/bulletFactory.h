#pragma once

#include "world.h"
#include "pistole.h"
#include "bullet.h"

enum class GunState{
    PISTOLE,
    SHOTGUN
};

class BulletFactory{
public:
    BulletFactory(World *world_ptr_);
    void change_gun(int num);
    void create_bullets(ofVec2f mouse_screen);
    
    GunState active_gun;

private:
    World *world_ptr;
    
    void create_pistole_bullets(ofVec2f mouse_screen);
    void create_shotgun_bullets(ofVec2f mouse_screen);
};