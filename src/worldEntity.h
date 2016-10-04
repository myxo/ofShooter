#pragma once

// #include "world.h"

#include "ofMain.h"
#include "Box2D/Box2D.h"

class World;

class worldEntity{
public:
    worldEntity(){
        obj_id = obj_count++;
    }
    
    virtual void collision_event(worldEntity *) = 0;
    
    ofVec2f center, dir;
    int obj_id;

private:
    static size_t obj_count;
    
protected:
    b2Body  *box;
    World *world_ptr;
};
