#pragma once

#include "player.h"
#include "mob.h"
#include "bullet.h"
#include "boxContactListener.h"
#include "bulletFactory.h"
#include "building.h"
#include "level.h"
#include "gameParameter.h"
#include "camera.h"
#include "Box2D/Box2D.h"

#include <cstdint>

#define MOB_MAX 2

class Mob;
class Player;
class Bullet;
class Camera;

// TODO check how to specifie values in enum class.
// Or leave it as it is. It seems to work.
class EntityCategory{
public:
    static const uint8_t BUILDINGS   = 0x0001;
    static const uint8_t PLAYER      = 0x0002;
    static const uint8_t MOB         = 0x0004;
    static const uint8_t DEAD_MOB    = 0x0008;
    static const uint8_t BULLET      = 0x0010;
};

class Wall;
class BulletFactory;
class Building;

class World{
public:
    World();
    ~World();
    void update();
    void display();

    void gun_fire(ofVec2f mouse_screen);
    void bullet_cleanup();


    static ofVec2f box2of(b2Vec2 a);
    static b2Vec2 of2box(ofVec2f a);

    // void display_tile_background(ofImage tile);
// private:
    std::shared_ptr<Player>                 player;
    std::shared_ptr<BulletFactory>          bullet_factory;
    std::shared_ptr<Level>                  level;
    std::shared_ptr<Camera>                 camera;
    std::vector<std::shared_ptr<Mob>>       mob_array;
    std::vector<std::shared_ptr<Bullet>>    bullet_array;
    std::vector<std::shared_ptr<Building>>  building_array;
    GameParameter                           game_parameters;

    std::shared_ptr<b2World>                box2d_world;
    ofImage                                 background_image;

    ContactListener* CL;
    float32 prev_frame_time;
};