#pragma once

#include <chrono>

#include "movingEntity.h"
#include "world.h"
#include "sprite.h"
#include "level.h"

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
    Mob(ofVec2f center, World *world_ptr);
    Mob(LevelObject &lObject, World *world_ptr);
    ~Mob();

    void update_state();
    void update();
    void display();
    void take_damage(int damage);
    void make_damage();
    void become_dead();
    void collision_event(worldEntity *collision_entity);
    bool is_dead();

    int damage;
    double speed, max_speed;
    MobState state;

private:
    void mob_init(ofVec2f center, World *world_ptr);
    void box_init(ofVec2f center);

    std::chrono::time_point<std::chrono::steady_clock> attack_time;
    int resting_time;
    double attack_radius;
    Sprite sprite, dead_sprite;
};




