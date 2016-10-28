#pragma once

#include "ofMain.h"

#include "world.h"

class HUDDebug{
public:
    HUDDebug(const World& world_);
    void display();

private:
    const World& world;
};