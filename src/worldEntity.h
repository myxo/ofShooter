#pragma once

#include "ofMain.h"

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
};
