#pragma once

#include "worldEntity.h"

#include "ofMain.h"
#include "Box2D/Box2D.h"

class movingEntity : public worldEntity{
public:
    ofVec2f speed_dir;
    double speed, radius;
    int life;
    const int MAX_LIFE = 30;

    virtual void update(){}
    virtual void display(){}

    ofVec2f get_center_box() const;
    ofVec2f get_center_screen() const;

public:
    b2Body  *box;
};