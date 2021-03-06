#pragma once

#include "bullet.h"
#include "world.h"

class Pistole : public movingEntity, public Bullet{
public:
    Pistole(ofVec2f center, ofVec2f speed_dir, World *world_ptr);
    ~Pistole();

    void init_box(ofVec2f center);

    void update();
    void display();
    void make_damage(Mob *mob);
    void collision_event(worldEntity *collision_entity);

public:
    ofVec2f speed_dir;
    int damage;
};