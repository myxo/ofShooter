#pragma once

#include "movingEntity.h"
#include "world.h"
#include "ofMain.h"
#include "sprite.h"

#include "Box2D/Box2D.h"

class World;

enum class PlayerState{
    MOVING,
    STILL,
    DEAD
}; 

class Player : public movingEntity{
public:
    Player(ofVec2f center, double radius, int life, World *world_ptr);
    void box_init();

    void update();
    void display();

    void change_speed_dir(const unsigned int key_pressed);
    void take_damage(int damage);

    void collision_event(worldEntity *collision_entity);

    ofVec2f get_center();

    void hud_display();

private:
    // World *world_ptr;

    Sprite sprite;
    PlayerState state;
};
