#pragma once

#include "worldEntity.h"
#include "mob.h"

class Mob;

enum BulletState{
    EXIST,
    NOT_EXIST
};

class Bullet{
public:
    virtual void update()       = 0;
    virtual void display()      = 0;
    virtual void make_damage(Mob *mob)  = 0;
    // void shoot()        = 0;

    BulletState state;

    // bool isExist() = 0;
    // bool isNotExist() = 0;
};