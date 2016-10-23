#pragma once

#include "worldEntity.h"
#include "world.h"
#include "level.h"

#include <vector>
#include "ofMain.h"

class Building : public worldEntity{
public:
    vector<ofVec2f> vertex;

    Building(World *world_ptr_);
    ~Building();
    void building_from_file(const char* filename);
    void build_from_level_object(const LevelObject &object);
    void display();

    void collision_event(worldEntity *collision_entity);
private:
    void box_init();
    ofVec2f get_vertex_screen_coord(int i);
    // World *world_ptr;
};