#include "world.h"
#include "player.h"
#include "boxContactListener.h"

#include "ofMain.h"
#include "Box2D/Box2D.h"

#include "iostream"

World::World(){
    b2Vec2 gravity(0.0f, 0.0f);
    // bool doSleep = true;
    box2d_world = std::make_shared<b2World>(gravity);
    // box2d_world.setGravity(0,0);
    CL = new ContactListener();
    box2d_world->SetContactListener(CL);

    player = std::make_shared<Player>(ofVec2f(20, 10), 0.7, 30, this);

    for (int i = 0; i < MOB_MAX; i++){
        mob_array.push_back(std::make_shared<Mob>(ofVec2f(5, i*5 + 10), 0.5, 10, this));
    }
}

World::~World(){
    delete CL;
    bullet_array.clear();
}

void World::update(){
    // box2d_world.update();
    box2d_world->ClearForces();

    player->update();

    for (auto mob: mob_array){
        mob->update_state();
    }

    for (auto mob: mob_array){
        mob->update();
    }

    for (auto bullet: bullet_array){
        bullet->update();
    }

    box2d_world->Step(1/60., 10, 10);
    
    bullet_cleanup();
}

void World::bullet_cleanup(){
    for (auto i = bullet_array.begin(); i != bullet_array.end(); ){
        if ((*i)->state == BulletState::NOT_EXIST){
            i = bullet_array.erase(i);
        } else{
            ++i;
        }
    }
}

void World::display(){
    for (auto mob: mob_array){
        mob->display();
    }

    for (auto bullet: bullet_array){
        bullet->display();
    }

    player->display();
}



b2Vec2 World::transformeBoxToScreenCoorditane(b2Vec2 coord){
    int h = ofGetWindowHeight();
    int w = ofGetWindowWidth();

    coord.x = coord.x * WORLD_RESOLUTION + w/2;
    coord.y = coord.y * WORLD_RESOLUTION + h/2;
    return coord;
}


b2Vec2 World::transformeScreenToBoxCoorditane(b2Vec2 coord){
    int h = ofGetWindowHeight();
    int w = ofGetWindowWidth();

    coord.x = (coord.x - w/2) / WORLD_RESOLUTION;
    coord.y = (coord.y - h/2) / WORLD_RESOLUTION;
    return coord;
}


ofVec2f World::box2of(b2Vec2 a){
    return ofVec2f(a.x, a.y);
}
b2Vec2 World::of2box(ofVec2f a){
    return b2Vec2(a.x, a.y);
}