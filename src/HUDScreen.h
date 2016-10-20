#pragma once

#include "world.h"
#include "movingEntity.h"

class HUDScreen{
public:
    HUDScreen(const World& world);

    void display();

private:
    const World& world;
    void display_life(movingEntity* object);
    void display_gun_refactoring_time();

    ofTrueTypeFont  gun_message_font;
};