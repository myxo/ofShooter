#pragma once

#include "player.h"
#include "mob.h"
#include "bullet.h"
#include "boxContactListener.h"

#include "Box2D/Box2D.h"

#define MOB_MAX 10

class Mob;
class Player;
class Bullet;

enum EntityCategory{
    BUILDINGS   = 0x0001 ,
    PLAYER      = 0x0002 ,
    MOB         = 0x0004 ,
    DEAD_MOB    = 0x0008 ,
    BULLET      = 0x0010 ,
};


class World{
public:
    World();
    ~World();
    void update();
    void display();
    void bullet_cleanup();

    static b2Vec2 transformeBoxToScreenCoorditane(b2Vec2 coord);
    static b2Vec2 transformeScreenToBoxCoorditane(b2Vec2 coord);
    static ofVec2f box2of(b2Vec2 a);
    static b2Vec2 of2box(ofVec2f a);

// private:
    std::shared_ptr<Player>                 player;
    std::vector<std::shared_ptr<Mob> >      mob_array;
    std::vector<std::shared_ptr<Bullet> >   bullet_array;

    std::shared_ptr<b2World>                box2d_world;

    ContactListener* CL;
    float32 prev_frame_time;

    static const int WORLD_RESOLUTION = 16; // pixels in meter
};