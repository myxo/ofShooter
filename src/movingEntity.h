#pragma once

#include "worldEntity.h"

#include "ofMain.h"
#include "Box2D/Box2D.h"

class movingEntity : public worldEntity{
public:
    ofVec2f speed_dir;
    double speed, radius;
    int life;
    int MAX_LIFE = 30;

    virtual void update(){}
    virtual void display(){}

public:
    
};