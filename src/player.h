#pragma once

#include "movingEntity.h"
#include "world.h"
#include "ofMain.h"
#include "sprite.h"
#include "level.h"

#include "Box2D/Box2D.h"
#include <chrono>

class World;

enum class PlayerState{
    MOVING,
    STILL,
    DEAD
}; 

class Player : public movingEntity{
public:
    Player(ofVec2f center, World *world_ptr);
    Player(LevelObject &lObject, World *world_ptr);
    ~Player();

    void update();
    void display();

    void change_speed_dir(const unsigned int key_pressed);
    void take_damage(int damage);
    void hud_display();

    void collision_event(worldEntity *collision_entity);

private:
    void player_init(ofVec2f center, World *world_ptr);
    void box_init();

    Sprite sprite;
    PlayerState state;
};
