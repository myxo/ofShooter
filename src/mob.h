#pragma once

#include "movingEntity.h"
#include "world.h"
#include "sprite.h"

#include "ofMain.h"
// #include "ofxBox2d.h"
#include "Box2D/Box2D.h"

class World;

enum class MobState { 
    MAY_ATTACK, 
    ATTACKING, 
    REST, 
    FROSEN, 
    DEAD 
};


class Mob : public movingEntity{
public:
    const int ATTACK_TIME = 500, REST_TIME = 1000;


    int     damage = 5;
    float   speed_max = 1;
    int     attack_time_start, rest_time_start;
    // World   *world_ptr;
    

    MobState state;

public:
    Mob(ofVec2f center, double radius, int life, World *world_ptr);

    void update_state();
    void update();
    void display();
    void take_damage(int damage);
    void make_damage();
    void become_dead();
    void collision_event(worldEntity *collision_entity);
    bool is_dead();

private:
    void box_init(ofVec2f center);

    Sprite sprite, dead_sprite;
};




