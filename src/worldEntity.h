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

    // virtual ~worldEntity(){}
    
    virtual void collision_event(worldEntity *) = 0;
    
    ofVec2f center, dir;
    int obj_id;

    ofVec2f get_center_box()    const;
    ofVec2f get_center_screen() const;

private:
    static size_t obj_count;
    
protected:
    b2Body  *box;
    World *world_ptr;
};
