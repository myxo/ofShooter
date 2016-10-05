#pragma once

#include "player.h"
#include "mob.h"
#include "bullet.h"
#include "boxContactListener.h"

#include "wall.h"

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

class Wall;

class World{
public:
    World();
    ~World();
    void update();
    void display();

    void gun_fire(ofVec2f mouse_screen);
    void bullet_cleanup();

    b2Vec2 transformeBoxToScreenCoorditane(b2Vec2 coord);
    b2Vec2 transformeScreenToBoxCoorditane(b2Vec2 coord);
    static ofVec2f box2of(b2Vec2 a);
    static b2Vec2 of2box(ofVec2f a);

    // Wall *w;

    void update_window_boundary();
    void display_tile_background(ofImage tile);
    // void generate_tile_background(const char* filename);
// private:
    std::shared_ptr<Player>                 player;
    std::vector<std::shared_ptr<Mob> >      mob_array;
    std::vector<std::shared_ptr<Bullet> >   bullet_array;

    std::shared_ptr<b2World>                box2d_world;
    ofImage                                 background_image;
    ofImage                                 tile;

    ContactListener* CL;
    float32 prev_frame_time;
    int window_start_x = 0, window_start_y = 0; // for screen transition

    const int WINDOW_BOUND_TO_EXTEND_X = 250; // todo. rename + if screen is big, get 1/5 of window_width
    const int WINDOW_BOUND_TO_EXTEND_Y = 200; // todo. -//-
    static const int WORLD_RESOLUTION = 16; // pixels in meter
};